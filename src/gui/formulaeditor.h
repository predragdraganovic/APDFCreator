#ifndef FORMULAEDITOR_H
#define FORMULAEDITOR_H

#include <QDialog>
#include <QGraphicsPixmapItem>

namespace Ui {
class FormulaEditor;
}

class FormulaEditor : public QDialog
{
    Q_OBJECT

public:
    explicit FormulaEditor(QWidget *parent = nullptr);
    ~FormulaEditor();

    const QString &getLatex() const;
    int getFormulaResolution() const;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::FormulaEditor *ui;
    QString latexString = "";
    int formulaResolution;
};

#endif // FORMULAEDITOR_H
