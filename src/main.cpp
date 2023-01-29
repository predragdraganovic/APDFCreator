#include "gui/welcomepage/welcomepage.h"
#include "gui/mainwindow.h"
#include <QApplication>
#include <QProcess>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    WelcomePage w;
//     HINT: for easier development
    MainWindow w;

    bool foundTex = false;

    QProcess* latex = new QProcess();
    latex->closeReadChannel(QProcess::StandardOutput);
    latex->setProgram("latex");
    QStringList arguments;
    arguments<<"--version";
    latex->setArguments(arguments);
    latex->start();
    bool started = latex->waitForStarted();
    latex->waitForFinished();
    if(started){
        latex->setProgram("dvipng");
        arguments.clear();
        arguments<<"-h";
        latex->setArguments(arguments);
        latex->start();
        started = latex->waitForStarted();
        latex->waitForFinished();
        if(started){
            foundTex = true;
        }
    }

    delete latex;

    if(!foundTex){
        QMessageBox errorMsg(QMessageBox::Critical,"Error","LaTeX not found!");
        errorMsg.exec();
        exit(EXIT_FAILURE);
    }

    w.show();
    return a.exec();

}
