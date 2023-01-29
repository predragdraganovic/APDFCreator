#include "ruler.h"
#include <utility>

Ruler::Ruler(RulerOrientation orientation, QPageSize pageSize, int res)
{
    this->pageSize    = std::move(pageSize);
    this->res         = res;
    this->pagePixel   = QPageSize::sizePixels(this->pageSize.id(), res);
    this->orientation = orientation;

    if (orientation == RulerOrientation::HORIZONTAL)
    {
        rulerRectangle = QRectF(0, 0, pagePixel.width(), 10);
    }
    else
    {
        rulerRectangle = QRectF(0, 0, 10, pagePixel.height());
    }

    this->setSceneRect(rulerRectangle);

    // TODO: init slidera u zavisnosti od toga koji je ruler
}
