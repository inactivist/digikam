/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2011-05-23
 * Description : a tool to create panorama by fusion of several images.
 * Acknowledge : based on the expoblending tool
 *
 * Copyright (C) 2011-2016 by Benjamin Girault <benjamin dot girault at gmail dot com>
 * Copyright (C) 2009-2019 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef DIGIKAM_PANO_INTRO_PAGE_H
#define DIGIKAM_PANO_INTRO_PAGE_H

// Qt includes

#include <QAbstractButton>

// Local includes

#include "dwizardpage.h"
#include "panomanager.h"

using namespace Digikam;

namespace GenericDigikamPanoramaPlugin
{

class PanoManager;

class PanoIntroPage : public DWizardPage
{
    Q_OBJECT

public:

    explicit PanoIntroPage(PanoManager* const mngr, QWizard* const dlg);
    ~PanoIntroPage();

    bool binariesFound();

private Q_SLOTS:

    void slotToggleGPano(int state);
    void slotChangeFileFormat(QAbstractButton* button);
    void slotBinariesChanged(bool found);

    // TODO HDR
//     void slotShowFileFormat(int state);

private:

    void initializePage();

private:

    class Private;
    Private* const d;
};

} // namespace GenericDigikamPanoramaPlugin

#endif // DIGIKAM_PANO_INTRO_PAGE_H
