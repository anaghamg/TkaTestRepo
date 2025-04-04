/*
    File Name       : controlbutton.h
    Project Name    : Reconstruction and UI Software System for "Indigenous Magnetic Resonance Imaging"(IMRI)
    Project Code	: HSG021D
    Created         : 2018/10/01
    Purpose         : As part of Image Viewer section in IMRI GUI.
    Description     : Header file containing declarations for controlbutton class.
    Author(s)       : Ranjith KO
    Version Number  : v1.0
    Revisions       : 0.0
    Remarks         : Nil
    Copyright       : Copyright CDAC Thiruvanathapuram
*/
#ifndef CONTROLBUTTON_H
#define CONTROLBUTTON_H
#include "aspectratiopixmaplabel.h"
#include <QObject>
#include <QWidget>
#include <QString>
#include <QLabel>
#include <QPushButton>

class ControlButton: public QPushButton
{
    Q_OBJECT
public:
    ControlButton(QWidget* parent = nullptr);
    void SetThumbnail(QString icon);
signals:
    void Selected();
private:
    AspectRatioPixmapLabel *thumbnail;
};

#endif // CONTROLBUTTON_H
