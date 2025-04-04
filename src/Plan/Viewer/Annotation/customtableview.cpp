#include "customtableview.h"

CustomTableView::CustomTableView(TableType type, QObject *parent) : QStyledItemDelegate(parent), m_type(type)
{

}


void CustomTableView::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const
{   
    QStyledItemDelegate::initStyleOption(option, index);
    //initialises the initStyleOption("option") to the default properties
    //of the item selected at the "index"

    option->displayAlignment = /*Qt::AlignLeft;*/ Qt::AlignVCenter | Qt::AlignLeft; //align items to center



    //    // Retrieve the normal text brush
    //    QBrush normalText = option->palette.brush(QPalette::ColorGroup::Normal,
    //                                              QPalette::ColorRole::Text);

    //    // Set the highlight brush and highlighted text color
    //    option->palette.setBrush(QPalette::ColorGroup::Normal,
    //                             QPalette::ColorRole::Highlight, Qt::gray);
    //    option->palette.setBrush(QPalette::ColorGroup::Normal,
    //                             QPalette::ColorRole::HighlightedText, normalText);

    //option->backgroundBrush = QBrush(Qt::black);

}

void CustomTableView::setCaptureIndex(const QModelIndex &index)
{
    m_captureIndexes.insert(index);

    // Repaint the entire view to update border colors
    if (m_tableView)
        m_tableView->viewport()->update();
}

void CustomTableView::setTableView(QTableView *tableView)
{
    m_tableView = tableView;
}





void CustomTableView::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
                 QVariant textData = index.data(Qt::DisplayRole);




       painter->setRenderHint(QPainter::Antialiasing, true);


       if (m_type == TypeA) {



          //  Check if it's a blank row by seeing if it contains an image in DecorationRole
               QVariant decorationData = index.data(Qt::DecorationRole);

               // If it contains an image, draw it centered and skip circle drawing
               if (decorationData.isValid()) {
                   return; // Exit after drawing the image
               }





       // painter->save();

      //  painter->restore();
       if (index.row() != 0 && index.row() != index.model()->rowCount() - 1) {



               QImage image(":/res/icons/blankrowimage_1.PNG");

                                 if (image.isNull()) {
                                         qDebug() << "Image failed to load!";
                                         return; // Exit if the image is null
                                     }

                                 QRect imgrect = option.rect;
                                 imgrect = imgrect.adjusted(0,-5, 0,6);

                                 int desiredHeight =50; // Set your desired height
                                 int scaledWidth = 30;

                                 QRect centeredRect(
                                         imgrect.left() +5,
                                         imgrect.top() + (imgrect.height() - desiredHeight) / 2,
                                         scaledWidth,
                                         desiredHeight
                                     );



                                     painter->drawImage(centeredRect, image);
                                     }

        int desiredDiameter = 22; // Set to your desired size

        // Define the position and size for the ellipse
        QRect ellipseRect(
                    option.rect.left() + 10,  // 10 pixels from the left
                    option.rect.top() + (option.rect.height() - desiredDiameter) / 2, // Vertically centered
                    desiredDiameter, // Width of the ellipse (diameter)
                    desiredDiameter  // Height of the ellipse (diameter)
                    );



        QColor fillColor = QColor("#333333");
        QColor borderColor = Qt::white;

        // Example logic for fill color (your existing logic)
        if (m_captureIndexes.contains(index)) {
            fillColor = QColor("#10B981");
           // fillColor =Qt::white;
            borderColor = QColor("#10B981");
        } else if (option.state & QStyle::State_Selected) {
            // fillColor = QColor("#10B981");
             fillColor =Qt::white;
           // borderColor = QColor("#10B981");

        }


        painter->setBrush(fillColor);
        painter->setPen(QPen(borderColor, 1.5));
        painter->drawEllipse(ellipseRect);






       //   painter->restore();

        // If captured, draw a white checkmark inside the blue circle
        if (m_captureIndexes.contains(index))
        {
            // Draw checkmark
            painter->setPen(QPen(Qt::white, 2));  // Set pen for checkmark with 1-pixel white lines
            //1 px not visible clearly

            // Define the checkmark geometry based on the circle size
            QPointF startPoint(ellipseRect.left() + ellipseRect.width() * 0.25, ellipseRect.center().y());
            QPointF midPoint(ellipseRect.center().x(), ellipseRect.bottom() - ellipseRect.height() * 0.25);
            QPointF endPoint(ellipseRect.right() - ellipseRect.width() * 0.25, ellipseRect.top() + ellipseRect.height() * 0.25);

            // Draw the two segments of the checkmark
            painter->drawLine(startPoint, midPoint);  // First half of the checkmark
            painter->drawLine(midPoint, endPoint);    // Second half of the checkmark
            //  painter->restore();
        }




        // Set up for rectangle drawing
        int rectWidth = 320; // Width of the rectangle
        int rectHeight = 40; // Height of the rectangle
       //QRect rect(option.rect.left() + 50, option.rect.top() + (option.rect.height() - rectHeight) / 2, rectWidth, rectHeight); // Positioning next to ellipse
       QRect rect(option.rect.left() + 50, option.rect.top(), rectWidth, rectHeight); // Positioning next to ellipse

        // Define border radius
        int borderRadius = 8;
        QPainterPath path;
        path.addRoundedRect(rect, borderRadius, borderRadius);

        // Draw the background color for the rectangle
        if (option.showDecorationSelected && (option.state & QStyle::State_Selected)) {
            painter->fillPath(path, QColor("#00B2A9")); // Custom selection color
            painter->setPen(QColor("#1A1A1A")); // Set text color to black for selected item
        } else {
            QVariant value = index.data(Qt::BackgroundRole);
            if (value.isValid() && qvariant_cast<QColor>(value).isValid()) {
                painter->fillPath(path, qvariant_cast<QColor>(value));
            } else {
                // Default background color for the rectangle
                QColor customBackgroundColor = QColor("#000000");
                painter->fillPath(path, customBackgroundColor);
                painter->setPen(Qt::white); // Set text color to white for non-selected item
            }
        }



        // Draw the text centered in the rectangle
        QRect textRect = rect.adjusted(10, 5,-5, -5); // Adjust text rectangle to fit inside the rectangle
        painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, textData.toString());







   } else if (m_type == TypeB) {


            //  Check if it's a blank row by seeing if it contains an image in DecorationRole
            QVariant decorationData = index.data(Qt::DecorationRole);

            // If it contains an image, draw it centered and skip circle drawing
            if (decorationData.isValid()) {

                QImage image = decorationData.value<QImage>();
                if (image.isNull()) {
                    qDebug() << "Image failed to load!";
                    return; // Exit if the image is null
                }

                QRect rect = option.rect;
                rect = rect.adjusted(0,-10, 0,10);

                int desiredHeight = 30; // Set your desired height
                int scaledWidth = 30;

                QRect centeredRect(
                            rect.left() +5,
                            rect.top()+10,
                            scaledWidth,
                            desiredHeight
                            );



                painter->drawImage(centeredRect, image);




                return; // Exit after drawing the image
            }





            painter->save();

            //  painter->restore();


            int desiredDiameter = 22; // Set to your desired size

            // Define the position and size for the ellipse
            QRect ellipseRect(
                        option.rect.left() + 10,  // 10 pixels from the left
                        option.rect.top() + (option.rect.height() - desiredDiameter) / 2, // Vertically centered
                        desiredDiameter, // Width of the ellipse (diameter)
                        desiredDiameter  // Height of the ellipse (diameter)
                        );



            QColor fillColor = QColor("#333333");
            QColor borderColor = Qt::white;

            // Example logic for fill color (your existing logic)
            if (m_captureIndexes.contains(index)) {
                fillColor = QColor("#10B981");
                // fillColor =Qt::white;
                borderColor = QColor("#10B981");
            } else if (option.state & QStyle::State_Selected) {
                // fillColor = QColor("#10B981");
                fillColor =Qt::white;
                // borderColor = QColor("#10B981");

            }

            painter->setBrush(fillColor);
            painter->setPen(QPen(borderColor, 1.5));
            painter->drawEllipse(ellipseRect);


            painter->restore();

            // If captured, draw a white checkmark inside the blue circle
            if (m_captureIndexes.contains(index))
            {
                // Draw checkmark
                painter->setPen(QPen(Qt::white, 2));  // Set pen for checkmark with 1-pixel white lines
                //1 px not visible clearly

                // Define the checkmark geometry based on the circle size
                QPointF startPoint(ellipseRect.left() + ellipseRect.width() * 0.25, ellipseRect.center().y());
                QPointF midPoint(ellipseRect.center().x(), ellipseRect.bottom() - ellipseRect.height() * 0.25);
                QPointF endPoint(ellipseRect.right() - ellipseRect.width() * 0.25, ellipseRect.top() + ellipseRect.height() * 0.25);

                // Draw the two segments of the checkmark
                painter->drawLine(startPoint, midPoint);  // First half of the checkmark
                painter->drawLine(midPoint, endPoint);    // Second half of the checkmark
                //  painter->restore();
            }




            // Set up for rectangle drawing
            int rectWidth = 320; // Width of the rectangle
            int rectHeight = 35; // Height of the rectangle
            //QRect rect(option.rect.left() + 50, option.rect.top() + (option.rect.height() - rectHeight) / 2, rectWidth, rectHeight); // Positioning next to ellipse
            QRect rect(option.rect.left() + 50, option.rect.top(), rectWidth, rectHeight); // Positioning next to ellipse

            // Define border radius
            int borderRadius = 8;
            QPainterPath path;
            path.addRoundedRect(rect, borderRadius, borderRadius);

            // Draw the background color for the rectangle
            if (option.showDecorationSelected && (option.state & QStyle::State_Selected)) {
                painter->fillPath(path, QColor("#00B2A9")); // Custom selection color
                painter->setPen(QColor("#1A1A1A")); // Set text color to black for selected item
            } else {
                QVariant value = index.data(Qt::BackgroundRole);
                if (value.isValid() && qvariant_cast<QColor>(value).isValid()) {
                    painter->fillPath(path, qvariant_cast<QColor>(value));
                } else {
                    // Default background color for the rectangle
                    QColor customBackgroundColor = QColor("#000000");
                    painter->fillPath(path, customBackgroundColor);
                    painter->setPen(Qt::white); // Set text color to white for non-selected item
                }
            }



            // Draw the text centered in the rectangle
            QRect textRect = rect.adjusted(10, 5, -5, -5); // Adjust text rectangle to fit inside the rectangle
            painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, textData.toString());




       }





}








QWidget *CustomTableView::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug()<<"createEditor";
    // Example: Create a custom editor
    // You can use a different widget if needed
    QLineEdit *editor = new QLineEdit(parent);
    return editor;
}

void CustomTableView::setEditorData(QWidget *editor, const QModelIndex &index) const //override
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    lineEdit->setText(index.model()->data(index, Qt::EditRole).toString());
    qDebug()<<"setEditorData";
}

void CustomTableView::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    model->setData(index, lineEdit->text(), Qt::EditRole);
    qDebug()<<"setModelData";
}
