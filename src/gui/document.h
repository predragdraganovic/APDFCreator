#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QList>
#include <QGraphicsScene>
#include "paper.h"
#include "../components/pagegrid.h"
#include "../components/pageproperties.h"
#include "../components/settingsscopecombo.h"

class Document: public QObject
{
    Q_OBJECT
public:
    explicit Document(QObject *parent);
    // TODO: brisanje papira etc
    ~Document(){
        clearAllPages();
        delete this;
    }
    Paper* getPaperAt(int position);
    Paper* getCurrentPage();

    void appendPage(QPageSize page_size, int res, QObject *parent);

    Paper* getLastPage();

    int getDocumentLength(){ return papers.length(); }

    void applyProperties(PageProperties properties, SettingsScopeCombo::SetupScope propertiesScope);

    /** Leaves only one blank page */
    void clearAllPages();

    void createNewDocument();
public slots:
    /** Adds new page after the currently active page and sets it to current */
    void addPage();

    /** Sets currentPage to next page if it exists */
    void nextPage();

    /** Sets currentPage to previous page if it exists */
    void prevPage();

    /** Deletes current page, and sets it to previous or if the new document length is 0
     *  then creates a new blank page */
    void deleteCurrentPage();

    /** Sets page that should be displayed. If the page doesn't exist value is ignored.
     *  This is support for jumping pages. */
    void setCurrentPage(int number);

    void slotToggleGridVisibility();

    /** Propagates from paper */
    void slotFocusItemChanged(QGraphicsItem *newFocusItem, QGraphicsItem *oldFocusItem, Qt::FocusReason reason){
        emit signalFocusItemChanged(newFocusItem, oldFocusItem, reason);
    }

    /** Propagates from paper */
    void slotItemRemoved(){
        emit signalItemRemoved();
    }

    void slotUpdateItemGeometry(QGraphicsItem* item);

signals:
    /** Signals that number of available pages changed */
    void documentLengthChanged(int number);

    /** Signals that current page is changed to given number, and sets current page in document. */
    void currentPageChanged(int currentPage);

    /** Propagates from paper */
    void signalFocusItemChanged(QGraphicsItem *newFocusItem, QGraphicsItem *oldFocusItem, Qt::FocusReason reason);

    /** Propagates from paper */
    void signalItemRemoved();

    /** Signals that current page properties are changed. */
    void currentPagePropertiesChanged();

    void signalUpdateItemGeometry(QGraphicsItem*);

private:
    QList<Paper*> papers = QList<Paper*>();
    /** Zero based current page */
    int currentPage;

    bool isVisibleGrid = false;

    /** Updates current page */
    void updatePageChanged(int currentPage);

    /** Creates new page and connects signals and slots to document */
    Paper* getNewPage();

};

#endif // DOCUMENT_H
