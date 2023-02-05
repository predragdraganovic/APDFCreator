#include "draggabletool.h"

// Creates the graphical representation of all the tools. They are consisted
// of 2 labels where one of them represents the tool icon and the other
// represents the tool name.

DraggableTool::DraggableTool(const QString &fileName, const QString &toolName, QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    toolIcon = new QLabel(this);
    QPixmap pix;
    if (pix.load(fileName))
    {

        pix = pix.scaled(toolIcon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        toolIcon->setPixmap(pix);
    }
    toolIcon->setFixedWidth(pix.width());
    toolIcon->setAlignment(Qt::AlignRight);
    layout->addWidget(toolIcon);
    toolLabel = new QLabel(toolName.toLocal8Bit().constData());

    layout->addWidget(toolLabel);
}

// Creates a new draggable object and sets the proper mimeData so
// scene would know how to make an object.

void DraggableTool::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QMimeData *mimeData = new QMimeData;
        mimeData->setText(toolLabel->text());
        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(this->grab());
        drag->exec();

        delete drag;
    }
}
