#include "formulaeditor.h"
#include "ui_formulaeditor.h"

FormulaEditor::FormulaEditor(QWidget *parent) : QDialog(parent), ui(new Ui::FormulaEditor)
{
    ui->setupUi(this);
    ui->spinBox->setValue(600);
    ui->plainTextEdit->setPlainText(latexString);
    formulaResolution = 600;
}

FormulaEditor::~FormulaEditor() { delete ui; }

void FormulaEditor::on_pushButton_clicked() { close(); }

void FormulaEditor::on_pushButton_2_clicked()
{
    latexString       = ui->plainTextEdit->toPlainText();
    formulaResolution = ui->spinBox->value();
    close();
}

int FormulaEditor::getFormulaResolution() const { return formulaResolution; }

const QString &FormulaEditor::getLatex() const { return latexString; }
