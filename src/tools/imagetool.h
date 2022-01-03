#ifndef IMAGETOOL_H
#define IMAGETOOL_H

#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QSlider>

class ImageTool : public QGraphicsPixmapItem
{
public:
    ImageTool();

    void setImage();
    QVBoxLayout *getToolOptions() const;
    qreal getImage_scale() const;
    void setImage_scale(qreal newImage_scale);

    int getOriginalWidth() const;
    void setOriginalWidth(int newOriginalWidth);

    int getOriginalHeight() const;
    void setOriginalHeight(int newOriginalHeight);

    const QPixmap &getOriginalPixmap() const;

    void setOriginalPixmap(const QPixmap &newOriginalPixmap);
    void setScaledPixmap(qreal scale);

private:
    qreal image_scale = 1;
    int originalWidth;
    int originalHeight;
    QPixmap originalPixmap;
};

#endif // IMAGETOOL_H
