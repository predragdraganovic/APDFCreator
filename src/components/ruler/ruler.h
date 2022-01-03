#ifndef RULER_H
#define RULER_H

#include <QGraphicsScene>
#include <QRectF>
#include <QPageSize>
#include <QSize>
#include <QPen>
#include <QColor>
#include <QDrag>
#include "slider.h"

const QPen cmPen = QPen(QColor(110, 110, 110));
const QPen mmPen = QPen(QColor(179, 179, 179));
const QColor sliderColor = QColor(150, 36, 36, 150);
const QBrush sliderBrush = QBrush(sliderColor);

const int sliderWidth = 7;
const int sliderHeight = 20;


class Ruler : public QGraphicsScene
{
public:
    enum RulerOrientation {VERTICAL, HORIZONTAL};
    Q_ENUM(RulerOrientation)

    Ruler(RulerOrientation orientation, QPageSize pageSize = QPageSize::A4, int res = 300);

private:
    /** size of the paper */
    QPageSize pageSize;
    QSize pagePixel;
    QRectF rulerRectangle;

    RulerOrientation orientation;

    /** Top or left */
    Slider *fstSlider;

    /** Bottom or right */
    Slider *sndSlider;

    int res;
    double marginTop;
    double marginBottom;
    double marginLeft;
    double marginRight;


//protected:

//    void paintEvent(QPaintEvent *event) override{
//        QSlider::paintEvent(event); // ovo je zaduzeno za crtanje rect koji moze da se pomera
//        QPainter p(this);
//        for(int i = 0; i < pagePixel.width(); i+=2){
//            if(i%10 == 0){
//                p.setPen(cmPen);
//                p.drawLine(i, 0, i, 40);
//            }
//            else{
//                p.setPen(mmPen);
//                p.drawLine(i, 10, i, 30);
//            }
//        }
//    }




};

#endif // RULER_H
