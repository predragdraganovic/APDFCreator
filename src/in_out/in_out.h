#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QPainter>
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QByteArray>
#include <QBuffer>
#include <QObject>
#include "gui/document.h"

class InputOutput
{
public:
    InputOutput();
    static void exportToPdf(Document&);
    static void printDocument(Document&);
    void saveToApdfAs(QString &fileName, Document&);

    void saveToApdf(Document&);
    void openApdf(QString &fileName, Document &);
    QFile *getCurrentFile() const;
    void setCurrentFile(QFile *newCurrentFile);
    void clearCurrentFile();

private:
    QFile *currentFile = nullptr;
    void saveToFile(Document&);
    QJsonDocument fromPaperToJson(Document &paper);
};

#endif // INPUTOUTPUT_H
