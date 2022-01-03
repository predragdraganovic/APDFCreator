#ifndef FORMULATOOL_H
#define FORMULATOOL_H

#include <QGraphicsPixmapItem>
#include <gui/formulaeditor.h>
#include <QProcess>
#include <QFile>
#include <QFileInfo>
#include <QEvent>
#include <QPixmap>

class FormulaTool : public QGraphicsPixmapItem
{
public:
    enum{
        Type = UserType+1
    };

    FormulaTool();
    FormulaTool(QString latex, int res);

    bool sceneEvent(QEvent *event) override;
    QPixmap updateImage(int latexRes, QString latexString);

    const QString &getLatexString() const;
    void setLatexString(const QString &newLatexString);

    int getLatexRes() const;
    void setLatexRes(int newLatexRes);

    int type() const override;


private:
    QString latexString;
    FormulaEditor* formulaEd;
    int latexRes;

};

#endif // FORMULATOOL_H
