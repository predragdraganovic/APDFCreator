#ifndef SLIDER_H
#define SLIDER_H

#include <QGraphicsRectItem>

class Slider: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    enum SliderType {SLIDER_TOP, SLIDER_BOTTOM, SLIDER_LEFT, SLIDER_RIGHT};
    Q_ENUM(SliderType)

    explicit Slider(SliderType sliderType);

    // TODO: dodati po kojoj koordinati se gleda/pomera u zavisnosti od toga koji je
    // slider, treba mu samo pocetak sa koje strane ide, sta se uvecava i pomeranje
    // da se overideuje da ide samo po jednoj osi.

};

#endif // SLIDER_H
