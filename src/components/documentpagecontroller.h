#ifndef DOCUMENTPAGECONTROLLER_H
#define DOCUMENTPAGECONTROLLER_H

#include <QHBoxLayout>
#include <QPushButton>
#include <QIcon>
#include <QLineEdit>
#include <QLabel>
#include <QSpacerItem>
#include <QIntValidator>

class DocumentPageController : public QHBoxLayout
{
    Q_OBJECT
public:
    DocumentPageController(int currentPage, int currentNumberOfPages);
    ~DocumentPageController(){
        delete inputValidator;
    }

private:
    QPushButton *btnPrevPage;
    QPushButton *btnNextPage;
    QLineEdit *inputCurrentPage;
    QLabel *lblTotalPages;
    QIntValidator *inputValidator;

signals:
    /** Sets currentPage to next page if it exists */
    void nextPage();

    /** Sets currentPage to previous page if it exists */
    void prevPage();

    /** Sets page that should be displayed. If the page doesn't exist value is ignored.
     *  This is support for jumping pages. */
    void setCurrentPage(int number);

public slots:
    /** Updates number of pages when document size changes*/
    void documentLengthChanged(int number);

    /** Updates current page to given number. */
    void currentPageChanged(int currentPage);

    /** Catches whenever input value changes */
    void currentPageValueChanged(const QString& value);

    /** on enter, triggers only when input validator returns QValidator::Acceptable */
    void currentPageSubmit();
};

#endif // DOCUMENTPAGECONTROLLER_H
