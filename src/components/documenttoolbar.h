#ifndef DOCUMENTTOOLBAR_H
#define DOCUMENTTOOLBAR_H

#include <QToolBar>
#include <QAction>
#include <iostream>
#include <QActionGroup>

// let the compiler know such class will be defined
class Document;

class DocumentToolbar : public QToolBar
{
    Q_OBJECT
public:
    DocumentToolbar();
    ~DocumentToolbar(){
        delete toggleGridAction;
        delete insertNewPage;
        delete deletePageAction;
    }

public slots:
    void on_toggleGridAction_triggered();
    void on_insertNewPage_triggered();
    void on_deletePage_triggered();

signals:
    /** Signals that new page should be created */
    void signalInsertPage();
    void signalToggleGridVisibility();
    void signalDeletePage();

private:
    QAction *toggleGridAction;
    QAction *insertNewPage;
    QAction *deletePageAction;

    QAction* initAction( const QString& objectName,const QString& text, const QString& iconPath,const QString& tooltipText);

};

#endif // DOCUMENTTOOLBAR_H
