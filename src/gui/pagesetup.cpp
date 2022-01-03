#include "pagesetup.h"
#include "ui_pagesetup.h"

PageSetup::PageSetup(Document &document, QGraphicsView &view, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pagesetup)
{
    ui->setupUi(this);

    this->pageProperties = new PageProperties(
                document.getCurrentPage()->getPageSize(),
                document.getCurrentPage()->getRes(),
                document.getCurrentPage()->getMarginTop(),
                document.getCurrentPage()->getMarginBottom(),
                document.getCurrentPage()->getMarginLeft(),
                document.getCurrentPage()->getMarginRight()
                );


    QStringList dpi = (QStringList()<<"72"<<"200"<<"300"<<"600"<<"1200");
    ui->comboBox->addItems(dpi);

    comboSettingsScope = new SettingsScopeCombo();
    ui->hLayoutSettingsScope->addWidget(comboSettingsScope);

    paperSize = new PaperSizeCombo(document.getCurrentPage()->getPageSize());
    ui->hLayoutPaperSizes->addWidget(paperSize);

    currentView = &view;
    this->document = &document;

    ui->comboBox->setCurrentText(QString::number(document.getCurrentPage()->getRes()));

    ui->marginTop->setValue(pageProperties->getMarginTop());
    ui->marginBottom->setValue(pageProperties->getMarginBottom());
    ui->marginLeft->setValue(pageProperties->getMarginLeft());
    ui->marginRight->setValue(pageProperties->getMarginRight());

}

PageSetup::~PageSetup()
{
    delete ui;


}

void PageSetup::on_pushButton_2_clicked()
{
    close();
}

void PageSetup::on_comboBox_currentTextChanged(const QString &arg1)
{
    this->pageProperties->setDpi(arg1.toInt());
}


void PageSetup::on_pushButton_clicked()
{
    //this->pageProperties->setDpi(ui->comboBox->currentText().toInt()); // postavlja se listener-om
    this->pageProperties->setPageSize(paperSize->getSelectedPageSize());
    this->pageProperties->setMarginTop(ui->marginTop->value());
    this->pageProperties->setMarginBottom(ui->marginBottom->value());
    this->pageProperties->setMarginLeft(ui->marginLeft->value());
    this->pageProperties->setMarginRight(ui->marginRight->value());

    document->applyProperties(*pageProperties, comboSettingsScope->getSelectedScope());

    currentView->update();
    currentView->fitInView(document->getCurrentPage()->sceneRect(),Qt::KeepAspectRatio);

    close();
}


