/* ============================================================
 * Author: Gilles Caulier <caulier dot gilles at free.fr>
 * Date  : 2004-07-09
 * Description : Blur image filter for ImageEditor
 * 
 * Copyright 2004-2005 by Gilles Caulier
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

#ifndef IMAGEEFFECT_BLUR_H
#define IMAGEEFFECT_BLUR_H

// KDE include.

#include <kdialogbase.h>

class QTimer;

class KIntNumInput;

namespace Digikam
{
class ImagePannelWidget;
class GaussianBlur;
}

class ImageEffect_Blur : public KDialogBase
{
    Q_OBJECT

public:

    ImageEffect_Blur(QWidget *parent);
    ~ImageEffect_Blur();

private:

    enum RunningMode
    {
    NoneRendering=0,
    PreviewRendering,
    FinalRendering
    };
    
    int           m_currentRenderingMode;
    
    QWidget      *m_parent;
    
    QTimer       *m_timer;
            
    KIntNumInput *m_radiusInput;
    
    Digikam::GaussianBlur      *m_threadedFilter;
    
    Digikam::ImagePannelWidget *m_imagePreviewWidget;
    
private slots:

    void slotEffect();
    void slotOk();
    void slotTimer();
    void slotCancel();
    void slotUser1();
    void slotFocusChanged(void);    
    
protected:

    void closeEvent(QCloseEvent *e);
    void customEvent(QCustomEvent *event);
    void abortPreview(void);
};

#endif /* IMAGEEFFECT_BLUR_H */
