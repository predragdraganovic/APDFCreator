#ifndef PAGEGRID_H
#define PAGEGRID_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPageSize>

class PageGrid : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum{
        Type = UserType+4
    };

    PageGrid(QPageSize pageSize){
        pagePixel = QPageSize::sizePixels(pageSize.id(), 300);
        setVisible(false);
    }

    QRectF boundingRect() const override{
        return QRectF(0,0,pagePixel.width(), pagePixel.height());
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override{
        painter->setPen(QPen(QBrush(Qt::black), 1));

        int stepSize = pagePixel.width()/21;
        for(int i = 0; i< pagePixel.width(); i+=stepSize){
            painter->drawLine(i, 0, i, pagePixel.height());
        }
        for(int i = 0; i< pagePixel.height(); i+=stepSize){
            painter->drawLine(0, i, pagePixel.width(), i);
        }
    }
    int type() const override{
        return Type;
    }
public slots:
    void slotToggleGridVisibility(){setVisible(!isVisible());}
    void slotPageSizeUpdate(QSizeF newSize){ pagePixel = newSize; }

private:

    QSizeF pagePixel;
};

#endif // PAGEGRID_H
