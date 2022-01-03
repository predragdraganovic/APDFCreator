#include "paper.h"
#include "tools/draggabletool.h"
#include "qgraphicsview.h"

#include <iostream>
// Paper constructor.
// Here we are setting the DPI resolution which we will be using for the paper and rendering
// We then calculate the paper size in pixels using the measurements stored in QPageSize enums
// After we do the calculations, we draw a rectangle on screen using the provided measurements and set it
// as the scene rectangle.


Paper::Paper(QPageSize page_size, int res, QObject *parent) : QGraphicsScene(parent)
{

    setRes(res);
    setPageSize(page_size);
    QSize pagePixel = QPageSize::sizePixels(page_size.id(), res);
    paperRectangle = QRectF(0,0,pagePixel.width(),pagePixel.height());
    Paper(paperRectangle, parent);
    drawPaper();
    this->setSceneRect(paperRectangle);
    marginBottom = 0.0;
    marginTop = 0.0;
    marginLeft = 0.0;
    marginRight = 0.0;
    this->pageGrid = new PageGrid(pageSize);
    this->addItem(this->pageGrid);
    connect(this, &Paper::signalSetGridVisibility, this->pageGrid, &PageGrid::slotToggleGridVisibility);
    connect(this, &Paper::signalPageSizeChanged, this->pageGrid, &PageGrid::slotPageSizeUpdate);
}

void Paper::setGridVisibility(bool isVisible){
    this->pageGrid->setVisible(isVisible);
    emit signalSetGridVisibility(isVisible);
}

QRectF Paper::getPaperRect() const
{
    return paperRectangle;
}

//void Paper::clearPage(){
//    for(auto item: items()){
//        if (item->type() != QGraphicsRectItem::Type){
//            removeItem(item);
//            delete item;
//        }
//    }
//}

void Paper::setPaperRect(QRectF newRect)
{
    paperRectangle=newRect;
}
// TODO: testirati refresh
void Paper::applyProperties(PageProperties pageProperties)
{
    setMarginBottom(pageProperties.getMarginBottom());
    setMarginTop(pageProperties.getMarginTop());
    setMarginRight(pageProperties.getMarginRight());
    setMarginLeft(pageProperties.getMarginLeft());

    QSizeF oldPixelSize = QPageSize::sizePixels(pageSize.id(),300);
    setPageSize(pageProperties.getPageSize());
    setRes(pageProperties.getDpi());

    QSizeF pixelSize = QPageSize::sizePixels(pageSize.id(),300);
    double newRatioX = pixelSize.width()/oldPixelSize.width();
    double newRatioY = pixelSize.height()/oldPixelSize.height();

    setSceneRect(QRectF(0,0,pixelSize.width(), pixelSize.height()));
    setPaperRect(QRectF(0,0,pixelSize.width(), pixelSize.height()));
    emit signalPageSizeChanged(pixelSize);
    redrawPaper(newRatioX,newRatioY);
}

void Paper::drawPaper(){
    rectItem=this->addRect(paperRectangle, QPen(),QBrush(Qt::white));
}


void Paper::redrawPaper(double newRatioX, double newRatioY)
{
    this->removeItem(rectItem);
    QList<QGraphicsItem *> currentTools;
    for(auto item : items()){
            if(item->type() == TextTool::Type)
            {
                TextTool *currentTool = (TextTool*)item;
                QFont newFont = currentTool->getTextDocument()->defaultFont();
                newFont.setPointSize(newFont.pointSizeF() * newRatioY);
                currentTool->getTextDocument()->setDefaultFont(newFont);
                currentTool->setFont(newFont);

            }
            if (item->type()  == ImageTool::Type)
            {
                double newScale=(newRatioX>newRatioY) ? newRatioY : newRatioX;
                ImageTool *currentTool = (ImageTool*)item;
                int newWidth=currentTool->pixmap().width()*newScale;
                int newHeight=currentTool->pixmap().height()*newScale;
                currentTool->setPixmap(currentTool->getOriginalPixmap().scaled(newWidth,newHeight));
            }
            if (item->type()  == FormulaTool::Type)
            {
                FormulaTool *currentTool = (FormulaTool*)item;
                currentTool->setLatexRes(currentTool->getLatexRes()*newRatioY);
                currentTool->setPixmap(currentTool->updateImage(currentTool->getLatexRes(),currentTool->getLatexString()));
            }

            QPointF viewP = QPointF(item->pos().x()*newRatioX,item->pos().y()*newRatioY);
            item->setPos(viewP);
            currentTools.append(item);
            this->removeItem(item);
    }
    rectItem=this->addRect(paperRectangle, QPen(),QBrush(Qt::white));
    for(auto tool : currentTools)
    {
        this->addItem(tool);
    }
}

void Paper::dragMoveEvent(QGraphicsSceneDragDropEvent *event){
    event->acceptProposedAction();
}

int Paper::getRes() const
{
    return res;
}

void Paper::setRes(int newRes)
{
    res = newRes;
}

double Paper::getMarginTop() const
{
    return marginTop;
}

void Paper::setMarginTop(double newMarginTop)
{
    marginTop = newMarginTop;
}

double Paper::getMarginBottom() const
{
    return marginBottom;
}

void Paper::setMarginBottom(double newMarginBottom)
{
    marginBottom = newMarginBottom;
}

double Paper::getMarginLeft() const
{
    return marginLeft;
}

void Paper::setMarginLeft(double newMarginLeft)
{
    marginLeft = newMarginLeft;
}

double Paper::getMarginRight() const
{
    return marginRight;
}

void Paper::setMarginRight(double newMarginRight)
{
    marginRight = newMarginRight;
}

const QPageSize &Paper::getPageSize() const
{
    return pageSize;
}

void Paper::setPageSize(const QPageSize &newPageSize)
{
    pageSize = newPageSize;
}

// Reacts on dropping tools onto the scene. It checks the type of tool and adds
// the appropriate item to the scene.

void Paper::dropEvent(QGraphicsSceneDragDropEvent *event){
    event->acceptProposedAction();
    QGraphicsItem* itemToAdd = nullptr;

    if(event->mimeData()->text() == "Paragraph"){
        TextTool *paragraph = new TextTool(12);
        itemToAdd = paragraph;
    }
    else if(event->mimeData()->text() == "Header"){
        TextTool *header = new TextTool(32);
        itemToAdd = header;
    }
    else if(event->mimeData()->text() == "Image"){
        ImageTool *image = new ImageTool();
        image->setImage();
        itemToAdd = image;

    }
    else if (event->mimeData()->text() == "Formula"){
        FormulaTool *ft = new FormulaTool();
        if (!ft->pixmap().isNull()){
            itemToAdd = ft;
        }
        else {
            QMessageBox err = QMessageBox(QMessageBox::Critical,"Error!","Unable to create formula");
            err.exec();
        }

    }
    if(itemToAdd == nullptr)
        return;
    itemToAdd->setPos(event->scenePos());
    resizeItemToFit(itemToAdd);
    moveItemWithinBounds(itemToAdd);
    this->addItem(itemToAdd);


}

void Paper::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem* itemToMove = nullptr;

    itemToMove = itemAt(event->scenePos(), QTransform());
    if(itemToMove == nullptr or itemToMove->type()==QGraphicsRectItem::Type){
        QGraphicsScene::mouseReleaseEvent(event);
    }
    resizeItemToFit(itemToMove);
    moveItemWithinBounds(itemToMove);


    QGraphicsScene::mouseReleaseEvent(event);
}

void Paper::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
    QPointF* pos = new QPointF(event->scenePos());

    QGraphicsItem* itemToRemove = itemAt(*pos, QTransform());
    if(!itemToRemove or itemToRemove->type()==QGraphicsRectItem::Type or itemToRemove->type() == PageGrid::Type)
        return;

    QMenu* menu = new QMenu;
    QAction* remove = new QAction("Remove",this);

    remove->setData(QVariant::fromValue((void*)pos));

    connect(remove,SIGNAL(triggered()),this,SLOT(removeItemFromScene()));
    menu->addAction(remove);
    menu->exec(event->screenPos());

    delete menu;
    delete remove;
    delete pos;

}

void Paper::removeItemFromScene()
{
    QAction* act = qobject_cast<QAction*>(sender());
    QVariant v = act->data();
    QPointF* pos = (QPointF*)v.value<void*>();

    QGraphicsItem* item = itemAt(*pos,QTransform());

    delete item;

    emit itemRemoved();
}


void Paper::moveItemWithinBounds(QGraphicsItem* item){
    if(item==nullptr or item->type() == PageGrid::Type)
        return;
    qreal newX = item->scenePos().x(), newY=item->scenePos().y();

    if(newX < sceneRect().x() + fromMMtoPixel(marginLeft))
        newX = sceneRect().x() + fromMMtoPixel(marginLeft);
    else if (newX > sceneRect().width() - fromMMtoPixel(marginRight))
        newX = sceneRect().width() - item->boundingRect().width() - fromMMtoPixel(marginRight);
    if(newY <sceneRect().y()+fromMMtoPixel(marginTop))
        newY = sceneRect().y() + fromMMtoPixel(marginTop);
    else if(newY > sceneRect().height()-fromMMtoPixel(marginBottom))
        newY = sceneRect().height() - item->boundingRect().height() - fromMMtoPixel(marginBottom);

    if(newX+item->boundingRect().width() > sceneRect().width() - fromMMtoPixel(marginRight) )
        newX-= (newX+item->boundingRect().width()) - (sceneRect().width() - fromMMtoPixel(marginRight));
    if(newY+item->boundingRect().height() > sceneRect().height() - fromMMtoPixel(marginBottom))
        newY-= (newY+item->boundingRect().height()) - (sceneRect().height() - fromMMtoPixel(marginBottom));
    item->setPos(newX,newY);
}

void Paper::resizeItemToFit(QGraphicsItem *item)
{
    if(item == nullptr)
        return;
    if(item->type() == TextTool::Type){
        TextTool* textItem = (TextTool*)item;

        QFont newFont = textItem->getTextDocument()->defaultFont();
        int pointSize = qRound(newFont.pointSize() / (300/72.0)) ;

        if(textItem->boundingRect().width() > sceneRect().width()){

            qreal fontWidth;
            QFontMetrics fm(newFont);
            fontWidth = fm.size(Qt::TextSingleLine,textItem->getTextData()).width();

            while(fontWidth > sceneRect().width()){
                pointSize-=2;
                newFont.setPointSize(pointSize * (300/72.0));
                QFontMetrics temp(newFont);
                fontWidth = temp.size(Qt::TextSingleLine,textItem->getTextData()).width();
            }

            textItem->getTextDocument()->setDefaultFont(newFont);
        }

    }
    else if(item->type() == ImageTool::Type){
        ImageTool* imageItem = (ImageTool*)item;
        qreal current_scale = imageItem->getImage_scale();
        while(imageItem->pixmap().width()>sceneRect().width() or imageItem->pixmap().height()>sceneRect().height()){
            current_scale-=0.1;
            imageItem->setScaledPixmap(current_scale);
        }
    }


}

void Paper::updateItemGeometry(QGraphicsItem *item)
{
    resizeItemToFit(item);
    moveItemWithinBounds(item);
}

PageGrid *Paper::getPageGrid() const
{
    return pageGrid;
}

int Paper::fromMMtoPixel(double mm ){
    return qRound(mm * (res/25.4));
}



