#include "papersizecombo.h"
#include <iostream>
PaperSizeCombo::PaperSizeCombo(const QPageSize& currentSize)
{
    paperSizeOptions = new QMap<QString, QPageSize>();

    paperSizeOptions->insert("A0",QPageSize::A0);
    paperSizeOptions->insert("A1",QPageSize::A1);
    paperSizeOptions->insert("A2",QPageSize::A2);
    paperSizeOptions->insert("A3",QPageSize::A3);
    paperSizeOptions->insert("A4",QPageSize::A4);
    paperSizeOptions->insert("A5",QPageSize::A5);
    paperSizeOptions->insert("A6",QPageSize::A6);
    paperSizeOptions->insert("A7",QPageSize::A7);
    paperSizeOptions->insert("A8",QPageSize::A8);
    paperSizeOptions->insert("A9",QPageSize::A9);

    paperSizeOptions->insert("B0",QPageSize::B0);
    paperSizeOptions->insert("B1",QPageSize::B1);
    paperSizeOptions->insert("B2",QPageSize::B2);
    paperSizeOptions->insert("B3",QPageSize::B3);
    paperSizeOptions->insert("B4",QPageSize::B4);
    paperSizeOptions->insert("B5",QPageSize::B5);
    paperSizeOptions->insert("B6",QPageSize::B6);
    paperSizeOptions->insert("B7",QPageSize::B7);
    paperSizeOptions->insert("B8",QPageSize::B8);
    paperSizeOptions->insert("B9",QPageSize::B9);
    paperSizeOptions->insert("B10",QPageSize::B10);

    paperSizeOptions->insert("C5E",QPageSize::C5E);
    paperSizeOptions->insert("Comm10E",QPageSize::Comm10E);
    paperSizeOptions->insert("DLE",QPageSize::DLE);
    paperSizeOptions->insert("Executive",QPageSize::Executive);
    paperSizeOptions->insert("Folio",QPageSize::Folio);
    paperSizeOptions->insert("Ledger",QPageSize::Ledger);
    paperSizeOptions->insert("Legal",QPageSize::Legal);
    paperSizeOptions->insert("Letter",QPageSize::Letter);
    paperSizeOptions->insert("Tabloid",QPageSize::Tabloid);

    this->addItems(QStringList(paperSizeOptions->keys()));

    setCurrentItem(findItems(
                       paperSizeOptions->keys()[(paperSizeOptions->values().indexOf(currentSize))]
                       , Qt::MatchExactly).at(0));

}


QPageSize PaperSizeCombo::getSelectedPageSize(){
    return this->paperSizeOptions->value(currentItem()->text(), QPageSize::A4);
}
