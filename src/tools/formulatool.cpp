#include "formulatool.h"


FormulaTool::FormulaTool()
{
    formulaEd =  new FormulaEditor();
    formulaEd->exec();

    latexString = formulaEd->getLatex();
    latexRes = formulaEd->getFormulaResolution();

    setPixmap(updateImage(latexRes, latexString));

    setFlags(QGraphicsItem::ItemIsMovable);
}

FormulaTool::FormulaTool(const QString& latex, int res){
    latexString = latex;
    latexRes = res;

    setPixmap(updateImage(latexRes,latexString));
    setFlags(QGraphicsItem::ItemIsMovable);
}

bool FormulaTool::sceneEvent(QEvent *event)
{
    if(event->type() == QEvent::GraphicsSceneMouseDoubleClick){
        formulaEd->exec();
        latexRes = formulaEd->getFormulaResolution();
        latexString = formulaEd->getLatex();
        setPixmap(updateImage(latexRes, latexString));
    }

    return QGraphicsPixmapItem::sceneEvent(event);
}



QPixmap FormulaTool::updateImage(int latexRes, const QString& latexString){
    QFile file("formula.tex");

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qCritical()<<"Unable to create file!";
        return QPixmap();
    }

    QTextStream input(&file);

    input<<"\\documentclass[preview]{standalone}\n\\nofiles\n\\thispagestyle{empty}\n\\begin{document}\n{$"<<latexString<<"$}\n\\end{document}";

    QFileInfo fI = QFileInfo(file);
    file.close();



    QProcess *latexToPng = new QProcess();

    latexToPng->setProgram("latex");
    QStringList arguments;
    arguments<<fI.absoluteFilePath();
    arguments<<"-output-directory="+fI.absolutePath();
    arguments<<"-quiet";
    latexToPng->setArguments(arguments);
    latexToPng->start();
    bool started = latexToPng->waitForStarted();
    latexToPng->waitForFinished();

    if(!started){
        qCritical()<<"Unable to process to dvi";
        return QPixmap();
    }

    if(QFile::exists("formula.log")){
        QFile::remove("formula.log");
    }

    if (QFile::exists("formula.tex")){
        QFile::remove("formula.tex");
    }

    if(!QFile::exists("formula.dvi")){
        qCritical()<<"Dvi not created, aborting";
        return QPixmap();
    }

    latexToPng->setProgram("dvipng");
    latexToPng->setWorkingDirectory(fI.absolutePath());
    fI = QFileInfo("formula.dvi");

    arguments.clear();

    arguments<<"-D "+QString::number(latexRes);
    arguments<<"-bg 'Transparent'";
    arguments<<"-q*";
    arguments<<fI.absoluteFilePath();

    latexToPng->setArguments(arguments);
    latexToPng->start();
    latexToPng->waitForFinished();

    if(QFile::exists("formula.dvi")){
        QFile::remove("formula.dvi");
    }

    delete latexToPng;
    if(QFile::exists("formula1.png")){
        QPixmap ret;
        ret = QPixmap("formula1.png");
        QFile::remove("formula1.png");
        return ret;
    }

    qCritical() << "Png doesn't exist";
    return QPixmap();
}

const QString &FormulaTool::getLatexString() const
{
    return latexString;
}

void FormulaTool::setLatexString(const QString &newLatexString)
{
    latexString = newLatexString;
}

int FormulaTool::getLatexRes() const
{
    return latexRes;
}

void FormulaTool::setLatexRes(int newLatexRes)
{
    latexRes = newLatexRes;
}

int FormulaTool::type() const
{
    return Type;
}

