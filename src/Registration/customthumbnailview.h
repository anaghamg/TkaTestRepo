#ifndef CUSTOMTHUMBNAILVIEW_H
#define CUSTOMTHUMBNAILVIEW_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QDebug>
#include <QTableView>
#include <QPushButton>
#include <QPainter>
#include <QStylePainter>
#include <QLineEdit>
#include <QLinearGradient>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QEvent>
#include <QMouseEvent>
#include <QListView>

class CustomThumbnailView : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CustomThumbnailView(QObject *parent = nullptr);





    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const override;

    // Override paint method to customize item rendering
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    //    QSize      sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override ;




    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);



    void setCaptureIndex(const QModelIndex &index);
    void setTableView(QListView *tableView);

    //QModelIndex m_captureIndex;
    QListView *m_tableView = nullptr;
    QSet<QModelIndex> m_captureIndexes;  // Store captured item indexes


        void setTotalItems(int totalItems);

        //int m_currentPage;
           int m_totalItems;
           //const int m_itemsPerPage = 4;


signals:
          // void              dataChanged(int, int);  // Update the view

public slots:

private:
    //QModelIndex m_customIndex;  // Index for which custom color is applied
    //bool m_applyCustomColor = false;  // Flag to apply custom color


};

#endif // CUSTOMTHUMBNAILVIEW_H
