/* ============================================================
 *
 * This file is a part of digiKam project
 * http://www.digikam.org
 *
 * Date        : 2010-04-02
 * Description : Database error handler interface
 *
 * Copyright (C) 2009-2010 by Marcel Wiesweg <marcel dot wiesweg at gmx dot de>
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

#ifndef DATABASEERRORHANDLER_H
#define DATABASEERRORHANDLER_H

// Qt includes

#include <QObject>
#include <QMetaType>
#include <QSqlError>

// Local includes

#include "digikam_export.h"

namespace Digikam
{

class DIGIKAM_DATABASECORE_EXPORT DatabaseErrorAnswer
{

public:

    virtual ~DatabaseErrorAnswer();
    virtual void connectionErrorContinueQueries() = 0;
    virtual void connectionErrorAbortQueries() = 0;
};

// -----------------------------------------------------------------

class DIGIKAM_DATABASECORE_EXPORT DatabaseErrorHandler : public QObject
{
    Q_OBJECT

public:

    DatabaseErrorHandler();
    ~DatabaseErrorHandler();

public Q_SLOTS:

    // NOTE: These all need to be slots, possibly called by queued connection
    /** In the situation of a connection error,
     *  all threads will be waiting with their queries
     *  and this method is called.
     *  This method can display an error dialog and try to repair
     *  the connection.
     *  It must then call either connectionErrorContinueQueries()
     *  or connectionErrorAbortQueries().
     *  The method is guaranteed to be invoked in the UI thread.
     */
    virtual void connectionError(DatabaseErrorAnswer* answer, const QSqlError& error, const QString& query) = 0;

    /** In the situation of an error requiring user intervention or information,
     *  all threads will be waiting with their queries
     *  and this method is called.
     *  This method can display an error dialog.
     *  It must then call either connectionErrorContinueQueries()
     *  or connectionErrorAbortQueries().
     *  The method is guaranteed to be invoked in the UI thread.
     */
    virtual void consultUserForError(DatabaseErrorAnswer* answer, const QSqlError& error, const QString& query) = 0;
};

} // namespace Digikam

Q_DECLARE_METATYPE(Digikam::DatabaseErrorAnswer*)

#endif // DATABASEERRORHANDLER_H
