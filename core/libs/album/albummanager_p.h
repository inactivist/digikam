/* ============================================================
 *
 * This file is a part of digiKam project
 * http://www.digikam.org
 *
 * Date        : 2004-06-15
 * Description : Albums manager interface.
 *
 * Copyright (C) 2006-2018 by Gilles Caulier <caulier dot gilles at gmail dot com>
 * Copyright (C) 2006-2011 by Marcel Wiesweg <marcel dot wiesweg at gmx dot de>
 * Copyright (C) 2015      by Mohamed_Anwer <m_dot_anwer at gmx dot com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#ifndef DIGIKAM_ALBUM_MANAGER_P_H
#define DIGIKAM_ALBUM_MANAGER_P_H

#include "albummanager.h"

// C ANSI includes

extern "C"
{
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
}

// C++ includes

#include <cerrno>
#include <clocale>
#include <cstdio>
#include <cstdlib>

// Qt includes

#include <QApplication>
#include <QByteArray>
#include <QDir>
#include <QFile>
#include <QGroupBox>
#include <QHash>
#include <QLabel>
#include <QList>
#include <QMultiHash>
#include <QRadioButton>
#include <QTextCodec>
#include <QTimer>
#include <QComboBox>
#include <QIcon>
#include <QPointer>
#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSet>

// KDE includes

#include <klocalizedstring.h>

// Local includes

#include "digikam_debug.h"
#include "coredb.h"
#include "album.h"
#include "albumpointer.h"
#include "applicationsettings.h"
#include "metadatasettings.h"
#include "metadatasynchronizer.h"
#include "albumwatch.h"
#include "imageattributeswatch.h"
#include "collectionlocation.h"
#include "collectionmanager.h"
#include "digikam_config.h"
#include "coredbaccess.h"
#include "coredboperationgroup.h"
#include "dbengineguierrorhandler.h"
#include "dbengineparameters.h"
#include "databaseserverstarter.h"
#include "coredbthumbinfoprovider.h"
#include "coredburl.h"
#include "coredbsearchxml.h"
#include "coredbwatch.h"
#include "dio.h"
#include "facetags.h"
#include "facetagseditor.h"
#include "imagelister.h"
#include "scancontroller.h"
#include "setupcollections.h"
#include "setup.h"
#include "tagscache.h"
#include "thumbsdbaccess.h"
#include "thumbnailloadthread.h"
#include "dnotificationwrapper.h"
#include "dbjobinfo.h"
#include "dbjobsmanager.h"
#include "dbjobsthread.h"
#include "similaritydb.h"
#include "similaritydbaccess.h"

namespace Digikam
{

class Q_DECL_HIDDEN PAlbumPath
{
public:

    PAlbumPath()
        : albumRootId(-1)
    {
    }

    PAlbumPath(int albumRootId, const QString& albumPath)
        : albumRootId(albumRootId),
          albumPath(albumPath)
    {
    }

    explicit PAlbumPath(PAlbum* const album)
    {
        if (album->isRoot())
        {
            albumRootId = -1;
        }
        else
        {
            albumRootId = album->albumRootId();
            albumPath   = album->albumPath();
        }
    }

    bool operator==(const PAlbumPath& other) const
    {
        return (other.albumRootId == albumRootId &&
                other.albumPath   == albumPath);
    }

public:

    int     albumRootId;
    QString albumPath;
};

// -----------------------------------------------------------------------------------

uint qHash(const PAlbumPath& id)
{
    return ( ::qHash(id.albumRootId) ^ ::qHash(id.albumPath) );
}

// -----------------------------------------------------------------------------------

class Q_DECL_HIDDEN AlbumManager::Private
{
public:

    explicit Private()
      : changed(false),
        hasPriorizedDbPath(false),
        dbFakeConnection(false),
        showOnlyAvailableAlbums(false),
        albumListJob(0),
        dateListJob(0),
        tagListJob(0),
        personListJob(0),
        albumWatch(0),
        rootPAlbum(0),
        rootTAlbum(0),
        rootDAlbum(0),
        rootSAlbum(0),
        currentlyMovingAlbum(0),
        changingDB(false),
        scanPAlbumsTimer(0),
        scanTAlbumsTimer(0),
        scanSAlbumsTimer(0),
        scanDAlbumsTimer(0),
        updatePAlbumsTimer(0),
        albumItemCountTimer(0),
        tagItemCountTimer(0)
    {
    }

    bool                        changed;
    bool                        hasPriorizedDbPath;

    bool                        dbFakeConnection;

    bool                        showOnlyAvailableAlbums;

    AlbumsDBJobsThread*         albumListJob;
    DatesDBJobsThread*          dateListJob;
    TagsDBJobsThread*           tagListJob;
    TagsDBJobsThread*           personListJob;


    AlbumWatch*                 albumWatch;

    PAlbum*                     rootPAlbum;
    TAlbum*                     rootTAlbum;
    DAlbum*                     rootDAlbum;
    SAlbum*                     rootSAlbum;

    QHash<int, Album*>          allAlbumsIdHash;
    QHash<PAlbumPath, PAlbum*>  albumPathHash;
    QHash<int, PAlbum*>         albumRootAlbumHash;
    Album*                      currentlyMovingAlbum;

    QMultiHash<Album*, Album**> guardedPointers;

    /** For multiple selection support **/
    QList<Album*>               currentAlbums;

    bool                        changingDB;
    QTimer*                     scanPAlbumsTimer;
    QTimer*                     scanTAlbumsTimer;
    QTimer*                     scanSAlbumsTimer;
    QTimer*                     scanDAlbumsTimer;
    QTimer*                     updatePAlbumsTimer;
    QTimer*                     albumItemCountTimer;
    QTimer*                     tagItemCountTimer;
    QSet<int>                   changedPAlbums;

    QMap<int, int>              pAlbumsCount;
    QMap<int, int>              tAlbumsCount;
    QMap<YearMonth, int>        dAlbumsCount;
    QMap<int, int>              fAlbumsCount;

public:

    QString labelForAlbumRootAlbum(const CollectionLocation& location)
    {
        QString label = location.label();

        if (label.isEmpty())
        {
            label = location.albumRootPath();
        }

        return label;
    }
};

// -----------------------------------------------------------------------------------

class Q_DECL_HIDDEN ChangingDB
{
public:

    explicit ChangingDB(AlbumManager::Private* const d)
        : d(d)
    {
        d->changingDB = true;
    }

    ~ChangingDB()
    {
        d->changingDB = false;
    }

    AlbumManager::Private* const d;
};

// -----------------------------------------------------------------------------------

class Q_DECL_HIDDEN AlbumManagerCreator
{
public:

    AlbumManager object;
};

Q_GLOBAL_STATIC(AlbumManagerCreator, creator)

} // namespace Digikam

#endif // DIGIKAM_ALBUM_MANAGER_P_H