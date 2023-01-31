#ifndef PAPER_H
#define PAPER_H

#include <QGraphicsScene>
#include <QGraphicsSceneDragDropEvent>
#include <QPageSize>
#include <QMimeData>
#include <QGraphicsTextItem>
#include <tools/texttool.h>
#include "components/ruler/ruler.h"
#include "components/pagegrid.h"
#include "components/pageproperties.h"
#include <tools/imagetool.h>
#include <tools/formulatool.h>
#include <QMessageBox>
#include <QMenu>

const QPen gridPen = QPen(QBrush(Qt::black), 0.5);

class Paper : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Paper(QObject *parent = nullptr);
    Paper(const QPageSize& page_size = QPageSize::A4, int res = 300, QObject *parent = nullptr);
    Paper(QRectF rect, QObject *parent):QGraphicsScene(rect, parent){}
    // segf
//    ~Paper();
//{
//        clearPage();
//        delete this;
//    }

//    /** Removes all items from page */
//    void clearPage();

    QRectF getPaperRect() const;
    void setPaperRect(QRectF newRect);

    void applyProperties(const PageProperties& pageProperties);

    int getRes() const;
    void setRes(int newRes);

    double getMarginTop() const;
    void setMarginTop(double newMarginTop);

    double getMarginBottom() const;
    void setMarginBottom(double newMarginBottom);

    double getMarginLeft() const;
    void setMarginLeft(double newMarginLeft);

    double getMarginRight() const;
    void setMarginRight(double newMarginRight);

    const QPageSize &getPageSize() const;
    void setPageSize(const QPageSize &newPageSize);
    void redrawPaper(double newRatioX, double newRatioY);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

    void setGridVisibility(bool isVisible);
    void moveItemWithinBounds(QGraphicsItem *item);
    void resizeItemToFit(QGraphicsItem *item);
    PageGrid *getPageGrid() const;

    int fromMMtoPixel(double mm);
public slots:
    void updateItemGeometry(QGraphicsItem*);
signals:
    void signalPageSizeChanged(QSizeF newSize);
    void itemRemoved();
    void signalSetGridVisibility(bool isVisible);

private:
    QRectF paperRectangle;
    QGraphicsRectItem* rectItem = nullptr;
    QPageSize pageSize;
    PageGrid *pageGrid = nullptr;

    int res = 0;
    double marginTop = 0;
    double marginBottom = 0;
    double marginLeft = 0;
    double marginRight = 0;


    void drawPaper();
    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dropEvent(QGraphicsSceneDragDropEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);


private slots:
    void removeItemFromScene();
};



#endif // PAPER_H
