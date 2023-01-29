#include "documentpagecontroller.h"
#include <iostream>

DocumentPageController::DocumentPageController(int currentPage,int currentNumberOfPages)
{
    this->btnNextPage= new QPushButton();
    this->btnNextPage->setIcon(QIcon(":/icons/chevron-right-24.png"));
    this->btnPrevPage= new QPushButton();
    this->btnPrevPage->setIcon(QIcon(":/icons/chevron-left-24.png"));
    this->lblTotalPages= new QLabel();
    this->lblTotalPages->setText( QString::number(currentNumberOfPages));

    inputValidator = new QIntValidator(1, currentNumberOfPages);

    this->inputCurrentPage = new QLineEdit(QString::number(currentPage+1));
    this->inputCurrentPage->setGeometry(QRect(0,0, 30,20));
    this->inputCurrentPage->setAlignment(Qt::AlignRight);
    this->inputCurrentPage->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->inputCurrentPage->setValidator(inputValidator);
    this->inputCurrentPage->setToolTip("Press enter to jump to page");

    this->setAlignment(Qt::AlignHCenter);
    // setup layout spacer, btn, input, label, btn, spacer
    this->addSpacerItem(new QSpacerItem(0,20, QSizePolicy::Expanding));
    this->addWidget(this->btnPrevPage);
    this->addWidget(this->inputCurrentPage);
    this->addWidget(new QLabel(QString("/")));
    this->addWidget(this->lblTotalPages);
    this->addWidget(this->btnNextPage);
    this->addSpacerItem(new QSpacerItem(0,20, QSizePolicy::Expanding));

    connect(btnNextPage, &QPushButton::clicked, this, &DocumentPageController::nextPage);
    connect(btnPrevPage, &QPushButton::clicked, this, &DocumentPageController::prevPage);
    connect(inputCurrentPage, &QLineEdit::returnPressed, this, &DocumentPageController::currentPageSubmit);
    connect(inputCurrentPage, &QLineEdit::textEdited, this, &DocumentPageController::currentPageValueChanged);
}

void DocumentPageController::currentPageValueChanged(const QString& value){
    // emits in both ifs because we can be at page 3 and then jump to 0, field will become 1 but the page wont change
    if(value.toInt() > this->lblTotalPages->text().toInt()){
        int maxPage = this->lblTotalPages->text().toInt();
        this->inputCurrentPage->setText(QString::number(maxPage));
        emit setCurrentPage(maxPage);
    }
    if(value.toInt() < 1){
        this->inputCurrentPage->setText("1");
        emit setCurrentPage(1);
    }
}
/** Submit on enter pressed, gets called only when input is valid (in range) */
void DocumentPageController::currentPageSubmit(){
    emit setCurrentPage(inputCurrentPage->text().toInt());
}

/** Updates number of pages when document size changes*/
void DocumentPageController::documentLengthChanged(int number){
    this->inputValidator->setTop(number);
    this->lblTotalPages->setText(QString::number(number));
}

/** Updates current page to given number. Must be greater than 0 */
void DocumentPageController::currentPageChanged(int currentPage){
    this->inputCurrentPage->setText(QString::number(currentPage));
}
