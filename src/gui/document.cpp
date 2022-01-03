#include "document.h"
#include <iostream>
Document::Document(QObject *parent)
{
    this->currentPage = 0;
    this->isVisibleGrid = false;
    this->papers.append(getNewPage());
    this->papers[0]->setGridVisibility(this->isVisibleGrid);
}

/** position must be valid. if the position exceedes length returns the last page,
 *  or first if position is negative */
Paper* Document::getPaperAt(int position){
    if(position >= this->papers.length()){
        return this->papers[this->papers.length()-1];
    }
    if(position < 0){
        return this->papers[0];
    }
    return this->papers[position];
}

/** position must be valid*/
Paper* Document::getCurrentPage(){
    return this->papers[this->currentPage];
}

void Document::appendPage(QPageSize page_size, int res, QObject *parent){
    this->papers.append(new Paper(page_size, res, parent));
    this->papers.last()->setGridVisibility(this->isVisibleGrid);
    emit documentLengthChanged(this->papers.length());
}

Paper* Document::getLastPage(){
    return this->papers.last();
}

/** Adds new page after current one, switches to it */
void Document::addPage(){
    this->papers.insert(this->currentPage+1, new Paper(QPageSize::A4, 300,nullptr));
    this->papers[this->currentPage+1]->setGridVisibility(this->isVisibleGrid);
    emit documentLengthChanged(this->papers.length());
    updatePageChanged(this->currentPage+1);
}

void Document::nextPage(){
    updatePageChanged(this->currentPage+1);
}

void Document::prevPage(){
    updatePageChanged(this->currentPage-1);
}

void Document::deleteCurrentPage(){
    delete (Paper *)(this->papers[this->currentPage]);

    this->papers.removeAt(this->currentPage);
    if(this->papers.length()==0){
        this->papers.append(getNewPage());
        this->papers[0]->setGridVisibility(this->isVisibleGrid);
    }
    updatePageChanged(this->currentPage-1);
    emit documentLengthChanged(this->papers.length());
}

/** gets page number starting from 1*/
void Document::setCurrentPage(int number){
    if(this->papers.length() > number && number > 0){
        updatePageChanged(number-1);
    }
}

void Document::slotToggleGridVisibility(){
    this->isVisibleGrid = !this->isVisibleGrid;
    for(int i = 0; i < this->papers.length(); i++){
        if(this->papers[i] != nullptr){
            this->papers[i]->setGridVisibility(this->isVisibleGrid);
        }
    }
}

void Document::slotUpdateItemGeometry(QGraphicsItem *item)
{
    emit signalUpdateItemGeometry(item);
}

/** parameter current page is index */
void Document::updatePageChanged(int currentPage){
    if(currentPage >= 0 && currentPage <= this->papers.length()-1){
        this->currentPage = currentPage;
    }
    emit currentPageChanged(this->currentPage+1);
}

/**
 * TODO: trebalo bi da se na osnovu glavnih podesavanja dokumenta, tj papira kreira i svaki drugi isti
*/
Paper* Document::getNewPage(){
    Paper* newPage = new Paper(QPageSize::A4, 300, nullptr);
    connect(newPage, SIGNAL(focusItemChanged(QGraphicsItem*,QGraphicsItem*,Qt::FocusReason)), this, SLOT(slotFocusItemChanged(QGraphicsItem*,QGraphicsItem*,Qt::FocusReason)));
    connect(newPage, &Paper::itemRemoved, this, &Document::slotItemRemoved);
    connect(this, SIGNAL(signalUpdateItemGeometry(QGraphicsItem*)),newPage,SLOT(updateItemGeometry(QGraphicsItem*)));
    return newPage;
}

void Document::applyProperties(PageProperties properties, SettingsScopeCombo::SetupScope propertiesScope){

    if(propertiesScope == SettingsScopeCombo::SetupScope::THIS_PAGE){
        getCurrentPage()->applyProperties(properties);
    }
    else{
        int i = 0;
        if(propertiesScope == SettingsScopeCombo::SetupScope::THIS_POINT_FORWARD){
            i = currentPage;
        }
        for(int j = i; j < this->papers.length(); j++){
            getPaperAt(j)->applyProperties(properties);
        }
    }
    emit currentPagePropertiesChanged();
}

void Document::clearAllPages(){
    for(auto page: papers){
        delete page;
    }
    papers.clear();
}

void Document::createNewDocument(){
    clearAllPages();
    currentPage = 0;
    appendPage(QPageSize::A4,300,nullptr);
    nextPage();
}
