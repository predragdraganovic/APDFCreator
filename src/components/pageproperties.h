#ifndef PAGEPROPERTIES_H
#define PAGEPROPERTIES_H

#include <QPageSize>

/** Document propagates properties of each page.
 */
class PageProperties
{
public:
    PageProperties(QPageSize pageSize, int dpi, double marginTop,
                   double marginBottom, double marginLeft, double marginRight):
        pageSize(pageSize),
        dpi(dpi),
        marginBottom(marginBottom),
        marginTop(marginTop),
        marginLeft(marginLeft),
        marginRight(marginRight)
    {}

    void setPageSize(QPageSize pageSize){this->pageSize = pageSize;}
    void setDpi(int dpi){this->dpi = dpi;}
    void setMarginTop(double marginTop){this->marginTop = marginTop;}
    void setMarginBottom(double marginBottom){this->marginBottom = marginBottom;}
    void setMarginLeft(double marginLeft){this->marginLeft = marginLeft;}
    void setMarginRight(double marginRight){this->marginRight = marginRight;}

    const QPageSize getPageSize() const {return this->pageSize;}
    const int getDpi() const {return this->dpi;}
    const double getMarginTop() const {return this->marginTop;}
    const double getMarginBottom() const {return this->marginBottom;}
    const double getMarginLeft() const {return this->marginLeft;}
    const double getMarginRight() const {return this->marginRight;}


private:
    QPageSize pageSize;
    int dpi;

    double marginTop;
    double marginBottom;
    double marginLeft;
    double marginRight;

};

#endif // PAGEPROPERTIES_H
