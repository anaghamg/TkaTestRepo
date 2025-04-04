#ifndef CUSTOMTABLEVIEW_H
#define CUSTOMTABLEVIEW_H

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

class CustomTableView : public QStyledItemDelegate
{
    Q_OBJECT
public:
     enum TableType { TypeA, TypeB };
    explicit CustomTableView(TableType type,QObject *parent = nullptr);




    //not using right now

    // Override createEditor to customize the editor for item editing
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    // Override setEditorData if needed
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    // Override setModelData if needed
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;



    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const override;

    // Override paint method to customize item rendering
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;


    void drawLeadingLines(QPainter *painter,const QStyleOptionViewItem &option,
                          const QRect &circleRect, const QRect &nextCircleRect,const QModelIndex &index) const;



    void setCaptureIndex(const QModelIndex &index);
    void setTableView(QTableView *tableView);



    QModelIndex m_captureIndex;
    QTableView *m_tableView = nullptr;
    QSet<QModelIndex> m_captureIndexes;  // Store captured item indexes





signals:
    // void requestUpdate();  // Signal to notify about changes

private:
    QModelIndex m_customIndex;  // Index for which custom color is applied
    bool m_applyCustomColor = false;  // Flag to apply custom color
    TableType m_type;

public slots:
};

#endif // CUSTOMTABLEVIEW_H
