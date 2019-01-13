/* ============================================================
 *
 * This file is a part of digiKam project
 * http://www.digikam.org
 *
 * Date        : 2018-07-30
 * Description : image editor plugin to add border
 *
 * Copyright (C) 2018-2019 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#include "bordertoolplugin.h"

// Qt includes

#include <QPointer>

// KDE includes

#include <klocalizedstring.h>

// Local includes

#include "editorwindow.h"
#include "bordertool.h"

namespace Digikam
{

BorderToolPlugin::BorderToolPlugin(QObject* const parent)
    : DPluginEditor(parent)
{
}

BorderToolPlugin::~BorderToolPlugin()
{
}

QString BorderToolPlugin::name() const
{
    return i18n("Add Border");
}

QString BorderToolPlugin::iid() const
{
    return QLatin1String(DPLUGIN_IID);
}

QIcon BorderToolPlugin::icon() const
{
    return QIcon::fromTheme(QLatin1String("bordertool"));
}

QString BorderToolPlugin::description() const
{
    return i18n("A tool to add a border around images");
}

QString BorderToolPlugin::details() const
{
    return i18n("<p>This Image Editor tool can add decorative border around image.</p>");
}

QList<DPluginAuthor> BorderToolPlugin::authors() const
{
    return QList<DPluginAuthor>()
            << DPluginAuthor(QLatin1String("Marcel Wiesweg"),
                             QLatin1String("marcel dot wiesweg at gmx dot de"),
                             QLatin1String("(C) 2006-2012"))
            << DPluginAuthor(QLatin1String("Gilles Caulier"),
                             QLatin1String("caulier dot gilles at gmail dot com"),
                             QLatin1String("(C) 2005-2019"))
            ;
}

void BorderToolPlugin::setup(QObject* const parent)
{
    DPluginAction* const ac = new DPluginAction(parent);
    ac->setIcon(icon());
    ac->setText(i18nc("@action", "Add Border..."));
    ac->setObjectName(QLatin1String("editorwindow_decorate_border"));
    ac->setActionCategory(DPluginAction::EditorDecorate);

    connect(ac, SIGNAL(triggered(bool)),
            this, SLOT(slotBorder()));

    addAction(ac);
}

void BorderToolPlugin::slotBorder()
{
    EditorWindow* const editor = dynamic_cast<EditorWindow*>(sender()->parent());

    if (editor)
    {
        BorderTool* const tool = new BorderTool(editor);
        tool->setPlugin(this);
        editor->loadTool(tool);
    }
}

} // namespace Digikam
