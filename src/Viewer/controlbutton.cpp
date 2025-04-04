/*
    File Name       : controlbutton.cpp
    Project Name    : Reconstruction and UI Software System for "Indigenous Magnetic Resonance Imaging"(IMRI)
    Project Code	: HSG021D
    Created         : 2018/10/01
    Purpose         : As part of Image Viewer section in IMRI GUI.
    Description     : Header file containing declarations for controlbutton class.
    Author(s)       : Ranjith KO
    Version Number  : v1.0
    Revisions       : 0.0
    Remarks         :
    Copyright       : Copyright CDAC Thiruvanathapuram
    Modified        : Deepak M
*/

#include "controlbutton.h"
#include <QDir>
#include <QVBoxLayout>

ControlButton::ControlButton(QWidget* parent)
    : QPushButton(parent)
{

    thumbnail = new AspectRatioPixmapLabel;
    auto *lyt = new QVBoxLayout;
     lyt->setContentsMargins(7,7,7,7);
     lyt->setMargin(5);
     lyt->setSpacing(0);
     lyt->setAlignment(Qt::AlignLeft |  Qt::AlignVCenter);
     lyt->addWidget(thumbnail, 10, Qt::AlignHCenter|  Qt::AlignVCenter);
     this->setSizePolicy(QSizePolicy ::Preferred , QSizePolicy ::Preferred);
     this->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #55497b, stop: 0.7 #4c426f, stop: 1.0 #443a62);"
                        "min-width: 25px; border:none; border-style:none");

     thumbnail->setStyleSheet("padding: 0px");
     QSizePolicy sp_retain = this->sizePolicy();
     sp_retain.setRetainSizeWhenHidden(true);
     this->setSizePolicy(sp_retain);
     this->setLayout(lyt);
}
void ControlButton::SetThumbnail(QString icon)
{
   QPixmap pix1;
   pix1.load(icon);
   thumbnail->setPixmap(pix1);
   connect(thumbnail, &AspectRatioPixmapLabel::clicked, [=](){emit Selected();});
   connect(this, &QPushButton::clicked, [=](){emit Selected();});
}
