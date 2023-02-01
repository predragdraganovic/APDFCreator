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
    ~FormulaTool() {delete formulaEd;}
    FormulaTool(const QString& latex, int res): latexString(latex)
    {
        latexRes    = res;

        setPixmap(updateImage(latexRes, latexString));
        setFlags(QGraphicsItem::ItemIsMovable);
    }

    bool sceneEvent(QEvent *event) override;
    QPixmap updateImage(int latexRes, const QString& latexString);

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
