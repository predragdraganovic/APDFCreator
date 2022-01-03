#include "documenttoolbar.h"

void DocumentToolbar::on_toggleGridAction_triggered(){
    emit signalToggleGridVisibility();
}
void DocumentToolbar::on_insertNewPage_triggered(){
    emit signalInsertPage();
}
void DocumentToolbar::on_deletePage_triggered(){
    emit signalDeletePage();
}

DocumentToolbar::DocumentToolbar()
{
    toggleGridAction = initAction("toggleGridAction", "Toggle grid", ":/icons/toogle_grid.png", "Toggles grid visibility");
    insertNewPage = initAction("insertNewPage", "Insert new Page", ":/icons/insert-page-48.png", "Inserts new page after current");
    deletePageAction = initAction("deletePageAction", "Delete page", ":/icons/delete-file-48.png", "Deletes current page");

    connect(toggleGridAction, &QAction::triggered, this, &DocumentToolbar::on_toggleGridAction_triggered);
    connect(insertNewPage, &QAction::triggered, this, &DocumentToolbar::on_insertNewPage_triggered);
    connect(deletePageAction, &QAction::triggered, this, &DocumentToolbar::on_deletePage_triggered);
}


QAction* DocumentToolbar::initAction(QString objectName, QString text, QString iconPath, QString tooltipText){
    QAction *action = new QAction(QIcon(iconPath), text);
    action->setToolTip(tooltipText);
    this->addAction(action);
    action->setObjectName(objectName);
    return action;
}
