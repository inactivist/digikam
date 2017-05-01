/* ============================================================
 *
 * This file is a part of digiKam project
 * http://www.digikam.org
 *
 * Date        : 2006-04-04
 * Description : a tool to generate HTML image galleries
 *
 * Copyright (C) 2006-2010 by Aurelien Gateau <aurelien dot gateau at free dot fr>
 * Copyright (C) 2012-2017 by Gilles Caulier <caulier dot gilles at gmail dot com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#ifndef XML_UTILS_H
#define XML_UTILS_H

// Qt includes

#include <QString>
#include <QMap>

// libxml includes

#include <libxml/xmlwriter.h>

namespace Digikam
{

/**
 * A simple wrapper for a C structure pointed to by @Ptr, which must be freed
 * with @freeFcn
 */
template <class Ptr, void(*freeFcn)(Ptr)>

class CWrapper
{
public:

    CWrapper(Ptr ptr)
        : mPtr(ptr)
    {
    }

    CWrapper()
        : mPtr(0)
    {
    }

    ~CWrapper()
    {
        freeFcn(mPtr);
    }

    operator Ptr() const
    {
        return mPtr;
    }

    bool operator!() const
    {
        return !mPtr;
    }

    void assign(Ptr ptr)
    {
        if (mPtr)
        {
            freeFcn(mPtr);
        }

        mPtr = ptr;
    }

private:

    Ptr mPtr;
};

/**
 * Simple wrapper around xmlTextWriter
 */
class XMLWriter
{
public:

    bool open(const QString& name);
    operator xmlTextWriterPtr() const;

    void writeElement(const char* element, const QString& value);
    void writeElement(const char* element, int value);

private:

    CWrapper<xmlTextWriterPtr, xmlFreeTextWriter> mWriter;
};

/**
 * A list of attributes for an XML element. To be used with @ref XMLElement
 */
class XMLAttributeList
{
public:

    void write(XMLWriter& writer) const;
    void append(const QString& key, const QString& value);
    void append(const QString& key, int value);

private:

    typedef QMap<QString, QString> Map;

    Map mMap;
};

/**
 * A class to generate an XML element
 */
class XMLElement
{
public:

    explicit XMLElement(XMLWriter& writer, const QString& element, const XMLAttributeList* attributeList=0);
    ~XMLElement();

private:

    XMLWriter& mWriter;
};

} // namespace Digikam

#endif // XML_UTILS_H
