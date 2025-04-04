#include "customthumbnailview.h"

CustomThumbnailView::CustomThumbnailView(QObject *parent) : QStyledItemDelegate(parent)
{

}

void CustomThumbnailView::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const
{
    QStyledItemDelegate::initStyleOption(option, index);

    //option->displayAlignment = Qt::AlignCenter; //align items to center
    option->displayAlignment = /*Qt::AlignLeft;*/ Qt::AlignVCenter | Qt::AlignLeft; //align items to center

}

//void CustomThumbnailView::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{

//    painter->setRenderHint(QPainter::Antialiasing, true);//parvathy

//    /*
//    //---------------- works ---------------//
//    //    // Draw the default background and other items first
//    //    QStyledItemDelegate::paint(painter, option, index);
//    //    painter->save();

//    //    const int cellSpacing = 25;
//    //    QRect rect = option.rect.adjusted(cellSpacing/2, cellSpacing/2,-cellSpacing/2,-cellSpacing/2);

//    //    QColor borderColor;
//    //    if (m_captureIndexes.contains(index))
//    //    {
//    //        borderColor = Qt::green;  // Capture color
//    //    }
//    //    else if (option.state & QStyle::State_Selected)
//    //    {
//    //        borderColor = Qt::blue;   // Selected color
//    //    }
//    //    else
//    //    {
//    //        borderColor = Qt::white;  // Default color
//    //    }

//    //    painter->setPen(QPen(borderColor, 0.5));  // Border width of 2 pixels

//    //    //set border radius of cell
//    //    const int cellRadius = 16; //16px
//    //    painter->drawRoundedRect(rect, cellRadius, cellRadius);
//    //    painter->restore();


//    //2. normal cell around the table //do not delete
//    // Get the cell rectangle
//    //    QRect cellRect = option.rect;

//    //    // Draw the border
//    //    const int borderWidth = 1;          // Border width
//    //    const int borderRadius = 16;        // Rounded corners radius

//    //    // Set the border color based on selection or other states
//    //    QColor borderColor = (option.state & QStyle::State_Selected) ? Qt::blue : Qt::white;

//    //    painter->setPen(QPen(borderColor, borderWidth));
//    //    painter->drawRoundedRect(cellRect.adjusted(borderWidth / 2, borderWidth / 2, -borderWidth / 2, -borderWidth / 2), borderRadius, borderRadius);

//    //    painter->restore();

//    */


//    // Draw the default background and other items first
//    QStyledItemDelegate::paint(painter, option, index);
//    painter->save();

//    // Get the cell rectangle
//    QRect cellRect = option.rect;

//    cellRect.setWidth(130);   // Set a new width
//    cellRect.setHeight(130);
//    cellRect.adjust(-20, -10 ,0,0);

//    // Draw the border
//    const int borderWidth = 2;          // Border width
//    const int borderRadius = 16;        // Rounded corners radius

//    // Set the border color based on selection or other states
//    //QColor borderColor = (option.state & QStyle::State_Selected) ? Qt::blue : Qt::white;
//    //QColor borderColor = (option.state & QStyle::State_Selected) ? QColor("#42CE17") : Qt::white;

//    //anagha
//    QColor borderColor;
//    if (m_captureIndexes.contains(index))
//    {
//        borderColor = QColor("#42CE17") ; // Capture color
//    }
//    else if (option.state & QStyle::State_Selected)
//    {
//        borderColor = QColor("#10B981") ;   // Selected color background: #10B981;

//    }
//    else
//    {
//        borderColor = Qt::white;  // Default color
//    }

//    painter->setPen(QPen(borderColor, borderWidth));
//    painter->drawRoundedRect(cellRect.adjusted(borderWidth / 2, borderWidth / 2, -borderWidth / 2, -borderWidth / 2), borderRadius, borderRadius);

//    painter->restore();
//}


void CustomThumbnailView::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->setRenderHint(QPainter::Antialiasing, true);

    //to remove box in u/d icons
//    // Retrieve the item data
//    QVariant data = index.data(Qt::UserRole + 2);

//    // Check if the item is "U" or "D"
//    if (data.toString() == "U" || data.toString() == "D") {

//        qDebug()<<"data == U";

//        // Call the base class to handle default painting for U/D items
//        QStyledItemDelegate::paint(painter, option, index);
//        return;
//    }


//    // Prevent the default selection background from overlaying the image
//    if (option.state & QStyle::State_Selected) {

//        //qDebug()<<"state selected";

//        // We are overriding the default selection painting
//        // Draw a transparent rectangle to prevent the image from being covered
//        QColor transparentColor(255, 197, 255, 0);  // Fully transparent color
//        painter->fillRect(option.rect, transparentColor);
//    }


    QVariant data = index.data(Qt::UserRole + 2);


    if (data.toString() == "") {
        // If the condition is met, skip border drawing
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }
    else
    {


    // Draw the default background and other items first
    QStyledItemDelegate::paint(painter, option, index);
    painter->save();

    QRect cellRect = option.rect;
    cellRect.setWidth(115);
    cellRect.setHeight(115);
    //cellRect.adjust(-20, -10, 0, 0);  // Adjust for padding
   // cellRect.adjust(-20, -18, 0, -5); //make it centered
    cellRect.adjust(-1, -1,-2, -2);

    const int borderWidth = 2;
    const int borderRadius = 16;




    // Determine the border color based on the state
    QColor borderColor;
    if (m_captureIndexes.contains(index)) {

        borderColor = QColor("#42CE17");  // Capture color (Green)
    } else if (option.state & QStyle::State_Selected) {
        borderColor = QColor("#10B981");  // Selected color (Blue)

    } else {
        borderColor = Qt::white;  // Default color (White)
    }

    painter->setPen(QPen(borderColor, borderWidth));
    painter->drawRoundedRect(cellRect.adjusted(borderWidth / 2, borderWidth / 2, -borderWidth / 2, -borderWidth / 2), borderRadius, borderRadius);

    painter->restore();
}

}



void CustomThumbnailView::setTotalItems(int totalItems)
{
    m_totalItems = totalItems;
}

bool CustomThumbnailView::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonPress)
    {/*
            const QMouseEvent *mouseEvent = static_cast<const QMouseEvent *>(event);
            QRect chevronDownRect = option.rect.adjusted(...);  // Set the chevron rect area

            if (chevronDownRect.contains(mouseEvent->pos()))
            {
                // Go to next page
                m_currentPage++;
                emit dataChanged(index, index);  // Update the view
                return true;
            }
            else if (chevronUpRect.contains(mouseEvent->pos()) && m_currentPage > 0)
            {
                // Go to previous page
                m_currentPage--;
                emit dataChanged(index, index);
                return true;
            }*/
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

//void CustomThumbnailView::setCaptureIndex(const QModelIndex &index)
//{
//    m_captureIndexes.insert(index);
//    //qDebug()<<"m_captureIndexes"<<index;

//    // Repaint the entire view to update border colors
//   if (m_tableView)
//       // Force updating the specific index where the capture occurred
//             emit m_tableView->model()->dataChanged(index, index);
//        m_tableView->viewport()->update();
//}

void CustomThumbnailView::setCaptureIndex(const QModelIndex &index)
{
    qDebug() << "setCaptureIndex called with index:" << index;

    if (!m_tableView) {
        qDebug() << "m_tableView is null!";
        return;
    }

    if (!index.isValid()) {
        qDebug() << "Invalid index!";
        return;
    }

    m_captureIndexes.insert(index);
    qDebug() << "Captured index successfully";

    // Trigger the UI update
    emit m_tableView->model()->dataChanged(index, index);
    m_tableView->viewport()->update();
}

void CustomThumbnailView::setTableView(QListView *tableView)
{
    m_tableView = tableView;
}
