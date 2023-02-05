#include "imagetool.h"

ImageTool::ImageTool()
{
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
}

void ImageTool::setImage()
{
    QString fileName =
        QFileDialog::getOpenFileName(nullptr, "Add an image", "", "Image files (*.jpg *.jpeg *.png *.bmp)");
    QImage image = QImage(fileName);
    this->setPixmap(QPixmap::fromImage(image));
    originalWidth  = pixmap().width();
    originalHeight = pixmap().height();
    originalPixmap = pixmap();
}

QVBoxLayout *ImageTool::getToolOptions() const
{
    QVBoxLayout *optsLayout = new QVBoxLayout;

    QLabel *imageScaleLabel   = new QLabel("Image scale:");
    QSlider *imageScaleSlider = new QSlider(Qt::Horizontal);
    imageScaleSlider->setObjectName("scaleSelector");
    imageScaleSlider->setRange(10, 200);
    imageScaleSlider->setSingleStep(10);
    imageScaleSlider->setValue(qRound(image_scale * 100));
    imageScaleSlider->setFixedWidth(130);

    optsLayout->addWidget(imageScaleLabel);
    optsLayout->addWidget(imageScaleSlider);

    return optsLayout;
}

qreal ImageTool::getImage_scale() const { return image_scale; }

void ImageTool::setImage_scale(qreal newImage_scale) { image_scale = newImage_scale; }

int ImageTool::getOriginalWidth() const { return originalWidth; }

void ImageTool::setOriginalWidth(int newOriginalWidth) { originalWidth = newOriginalWidth; }

int ImageTool::getOriginalHeight() const { return originalHeight; }

void ImageTool::setOriginalHeight(int newOriginalHeight) { originalHeight = newOriginalHeight; }

const QPixmap &ImageTool::getOriginalPixmap() const { return originalPixmap; }

void ImageTool::setOriginalPixmap(const QPixmap &newOriginalPixmap) { originalPixmap = newOriginalPixmap; }

void ImageTool::setScaledPixmap(qreal scale)
{
    image_scale   = scale;
    int newWidth  = originalWidth * scale;
    int newHeight = originalHeight * scale;
    setPixmap(originalPixmap.scaled(newWidth, newHeight));
}
