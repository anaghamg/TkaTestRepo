/*
    File Name       : AspectRatioPixmapLabel.cpp
    Project Name    : Reconstruction and UI Software System for "Indigenous Magnetic Resonance Imaging"(IMRI)
    Project Code	: HSG021D
    Created         : 2018/10/01
    Purpose         : As part of Image Viewer section in IMRI GUI.
    Description     : Header file containing implementation for AspectRatioPixmapLabel class.
    Author(s)       : Ranjith KO
    Version Number  : v1.0
    Revisions       : 0.0
    Remarks         : Nil
    Copyright       : Copyright CDAC Thiruvanathapuram
    Modified        : Deepak M
*/
#include "aspectratiopixmaplabel.h"

#include <QDebug>
#include <QMouseEvent>
#include <QResizeEvent>



AspectRatioPixmapLabel::AspectRatioPixmapLabel(QWidget* parent) :
    QLabel(parent)
{
    setScaledContents(false);

    QSizePolicy sp(QSizePolicy::Maximum, QSizePolicy::Fixed);
    sp.setHeightForWidth(true);
    setSizePolicy(sp);
    updateGeometry();
}


void AspectRatioPixmapLabel::setPixmap(const QPixmap& pixmap)
{
#ifdef DEBUG_LAYOUT
    qDebug() << Q_FUNC_INFO;
#endif
    m_pixmap = pixmap;
    QLabel::setPixmap(scaledPixmap());
    updateGeometry();
}


int AspectRatioPixmapLabel::heightForWidth(int width) const
{
    // Step 1: calculate an answer that's right for our image's aspect ratio
    int h = m_pixmap.isNull()
            ? 0  // a bit arbitrary! width()? 0? 1?
            : ((qreal)m_pixmap.height() * width) / m_pixmap.width();

    // Step 2: never give an answer that is greater than our maximum height,
    // or the framework may allocate too much space for it (and then display
    // us at our correct maximum size, but with giant gaps in the layout).
    h = qMin(h, m_pixmap.height());  // height() is 0 for a null pixmap anyway; see qpixmap.cpp

#ifdef DEBUG_LAYOUT
    qDebug() << Q_FUNC_INFO << "width" << width << "-> height" << h;
#endif
    return h;
}


QSize AspectRatioPixmapLabel::sizeHint() const
{
    QSize hint = m_pixmap.size();
    // hint.rheight() = -1;
#ifdef DEBUG_LAYOUT
    qDebug() << Q_FUNC_INFO << "pixmap size" << m_pixmap.size()
             << "size hint" << hint;
#endif
    return hint;

    // PROBLEM with AspectRatioPixmapLabel
    // If you have a 1920 x 1080 pixmap, then if you don't override sizeHint
    // you get something like a 640x380 default size. If you want the pixmap
    // to expand horizontally, you need to give a sizeHint.
    // However, if you give a sizeHint that's 1920 x 1080, the layout may
    // reduce the horizontal direction, but won't reduce the vertical
    // direction. Then, the *actual* image size is appropriately reduced
    // vertically by the resizeEvent() code, so you get a pixmap with
    // big top-and-bottom borders, because the displayed size is less than
    // the sizeHint.

    // Can you just return a width hint?
    // Well, you can, and that give the opposite problem - a right-hand border
    // with an image that's insufficiently sized.

    // This gets better if you enforce a size policy with
    // setHeightForWidth(true) set.

    // The problem may now be in VerticalScrollArea, having its vertical size
    // too large; not sure.
}


QSize AspectRatioPixmapLabel::minimumSizeHint() const
{
    return QSize(0, 0);
}


QPixmap AspectRatioPixmapLabel::scaledPixmap() const
{
#ifdef DEBUG_LAYOUT
    qDebug() << Q_FUNC_INFO << "this->size()" << this->size();
#endif
    return m_pixmap.scaled(this->size(),
                      Qt::KeepAspectRatio, Qt::SmoothTransformation);
}


void AspectRatioPixmapLabel::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    if (!m_pixmap.isNull()) {
        QLabel::setPixmap(scaledPixmap());
    this->setAlignment(Qt::AlignCenter);
#ifdef GUI_USE_RESIZE_FOR_HEIGHT
        updateGeometry();  // WATCH OUT: any potential for infinite recursion?
#ifdef DEBUG_LAYOUT
        qDebug() << Q_FUNC_INFO << "calling updateGeometry()";
#endif
#endif
    }
}


void AspectRatioPixmapLabel::mousePressEvent(QMouseEvent* event)
{
    Q_UNUSED(event);
    emit clicked();
}


void AspectRatioPixmapLabel::clear()
{
    // qDebug() << Q_FUNC_INFO;
    // If you set (1) a giant pixmap and then (2) a null pixmap, you can have
    // your size remain at the giant size.
    QPixmap blank(1, 1);
//    blank.fill(uiconst::BLACK_TRANSPARENT);
    setPixmap(blank);
}
