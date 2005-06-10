/* ============================================================
 * Author: Renchi Raju <renchi@pooh.tam.uiuc.edu>
 * Date  : 2005-04-21
 * Copyright 2005 by Renchi Raju
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
 * ============================================================ */

#ifndef ALBUMINFO_H
#define ALBUMINFO_H

/** @file albuminfo.h */

#include <qstring.h>
#include <qvaluelist.h>
#include <qdatetime.h>
#include <kurl.h>

/**
 * \class AlbumInfo
 * A container class for transporting album information
 * from the database to AlbumManager
 */
class AlbumInfo
{
public:

    typedef QValueList<AlbumInfo> List;

    int      id;
    QString  url;
    QString  caption;
    QString  collection;
    QDate    date;
    QString  icon;

    /**
     * needed for sorting
     */
    bool operator<(const AlbumInfo& info)
    {
        return url < info.url;
    }
};

/**
 * \class TagInfo
 * A container class for transporting tag information
 * from the database to AlbumManager
 */
class TagInfo
{
public:

    typedef QValueList<TagInfo> List;

    int      id;
    int      pid;
    QString  name;
    QString  icon;

    /**
     * needed for sorting
     */
    bool operator<(const TagInfo& info)
    {
        //TODO: would this cause failure?
        return pid < info.pid;
    }
};

/**
 * \class SearchInfo
 * A container class for transporting search information
 * from the database to AlbumManager
 */
class SearchInfo
{
public:

    typedef QValueList<SearchInfo> List;

    int      id;
    QString  name;
    KURL     url;

    /**
     * needed for sorting
     */
    bool operator<(const SearchInfo& info)
    {
        return id < info.id;
    }
};

#endif /* ALBUMINFO_H */
