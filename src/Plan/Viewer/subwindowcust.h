#ifndef SUBWINDOWCUST_H
#define SUBWINDOWCUST_H

#include <QObject>
#include <QWidget>
#include <QMdiSubWindow>
#include <QDebug>

class subwindowCust : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit subwindowCust(QMdiSubWindow *parent = nullptr);
    QPoint currentPos;
    bool startlogic=false;
signals:
    void closeeventGet();
    void hideEventGet();
    void resizeEventGet();
public slots:
    virtual void mousePressEvent(QMouseEvent *me) override;
    virtual void mouseReleaseEvent(QMouseEvent *mouseEvent) override;
    virtual void closeEvent(QCloseEvent *event) override;
    virtual void hideEvent(QHideEvent *hideEvent) override;
    virtual void resizeEvent(QResizeEvent *resizeEvent) ;
};

#endif // SUBWINDOWCUST_H
