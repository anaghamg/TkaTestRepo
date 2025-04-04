#include "subwindowcust.h"

subwindowCust::subwindowCust(QMdiSubWindow *parent) : QMdiSubWindow(parent)
{

}

void subwindowCust::mousePressEvent(QMouseEvent *me)
{
QMdiSubWindow::mousePressEvent(me);
}

void subwindowCust::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
    QMdiSubWindow::mouseReleaseEvent(mouseEvent);
}

void subwindowCust::closeEvent(QCloseEvent *event)
{
    QMdiSubWindow::closeEvent(event);
    emit closeeventGet();
}

void subwindowCust::hideEvent(QHideEvent *hideEvent)
{
    QMdiSubWindow::hideEvent(hideEvent);
    emit hideEventGet();
}

void subwindowCust::resizeEvent(QResizeEvent *resizeEvent)
{
    QMdiSubWindow::resizeEvent(resizeEvent);
    emit resizeEventGet();
}
