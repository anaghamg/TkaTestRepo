/*
    File Name       : AspectRatioPixmapLabel.h
    Project Name    : Reconstruction and UI Software System for "Indigenous Magnetic Resonance Imaging"(IMRI)
    Project Code	: HSG021D
    Created         : 2018/10/01
    Purpose         : As part of Image Viewer section in IMRI GUI.
    Description     : Header file containing declarations for AspectRatioPixmapLabel class.
    Author(s)       : Ranjith KO
    Version Number  : v1.0
    Revisions       : 0.0
    Remarks         : Nil
    Copyright       : Copyright CDAC Thiruvanathapuram
*/
#ifndef ASPECTRATIOPIXMAPLABEL_H
#define ASPECTRATIOPIXMAPLABEL_H

#include <QObject>
#include <QWidget>

#include <QLabel>
#include <QPixmap>
class QMouseEvent;
class QResizeEvent;


class AspectRatioPixmapLabel : public QLabel
{
    // Image that retains its aspect ratio, for displaying photos.
    // - Displays image UP TO its original size.
    // - Clickable, in a simple way (as per https://wiki.qt.io/Clickable_QLabel)
    //   - this form of clicking responds immediately, not as you release the
    //   mouse click (cf. QAbstractButton); however, there is no visual display
    //   that responds to the start of the click, so maybe that is reasonable.
    //   For another way of responding to clicks, see ClickableLabel.

    Q_OBJECT
public:
    explicit AspectRatioPixmapLabel(QWidget* parent = nullptr);
    virtual int heightForWidth(int width) const override;
    virtual QSize sizeHint() const override;
    virtual QSize minimumSizeHint() const override;
    QPixmap scaledPixmap() const;
    void clear();
protected:
    virtual void mousePressEvent(QMouseEvent* event) override;
signals:
    void clicked();
public slots:
    virtual void setPixmap(const QPixmap& pixmap);  // WON'T OVERRIDE.
    // - SO QLabel PROPERTY ACCESSORS ARE NOT VIRTUAL.
    // - AND YOU MUST BEWARE WHAT POINTER TYPE YOU ACCESS THIS THROUGH!
    virtual void resizeEvent(QResizeEvent* event) override;
private:
    QPixmap m_pixmap;
};

#endif // ASPECTRATIOPIXMAPLABEL_H
