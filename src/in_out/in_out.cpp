#include "in_out.h"

// -----------------------------------------------------------
// TODO: promeniti da vadi sve listove
// -----------------------------------------------------------

InputOutput::InputOutput()
{

}
void InputOutput::exportToPdf(Document &document){
    QString filename = QFileDialog::getSaveFileName(nullptr,"Export as PDF...","","PDF file (*.pdf)");
    if (filename == "")
        return;
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filename);

    QPainter painter = QPainter(&printer);

    for(int i = 0; i < document.getDocumentLength(); i++){
        printer.setPageSize(document.getPaperAt(i)->getPageSize());
        printer.setPageMargins(QMarginsF(0,0,0,0));
        printer.setResolution(document.getPaperAt(i)->getRes());
        bool wasVisible = document.getPaperAt(i)->getPageGrid()->isVisible();
        document.getPaperAt(i)->getPageGrid()->setVisible(false);
        document.getPaperAt(i)->render(&painter);
        if(wasVisible)
            document.getPaperAt(i)->getPageGrid()->setVisible(true);
        if(i+1 != document.getDocumentLength()){
            printer.newPage();
        }
    }

    painter.end();
}

void InputOutput::printDocument(Document &document){
    QPrinter printer(QPrinter::HighResolution);

    printer.setPageSize(document.getCurrentPage()->getPageSize());
    printer.setPageMargins(QMarginsF(0,0,0,0));
    printer.setResolution(document.getCurrentPage()->getRes());

    QPrintDialog print_dialog(&printer);
    if (QPrintDialog(&printer).exec() == QDialog::Accepted){
        QPainter painter(&printer);
        painter.setRenderHint(QPainter::Antialiasing);
        for(int i = 0; i < document.getDocumentLength(); i++){
            bool wasVisible = document.getPaperAt(i)->getPageGrid()->isVisible();
            document.getPaperAt(i)->getPageGrid()->setVisible(false);
            document.getPaperAt(i)->render(&painter);
            if(wasVisible)
                document.getPaperAt(i)->getPageGrid()->setVisible(true);
            if(i+1!=document.getDocumentLength())
                printer.newPage();
        }

        painter.end();
    }
}

void InputOutput::saveToApdfAs(QString& fileName, Document& document){
    if(fileName=="")
        return;
    currentFile = new QFile(fileName);

    if(!currentFile->open(QIODevice::ReadWrite)){
        QMessageBox err(QMessageBox::Critical,"Error","Can't create file!");
        err.exec();
        return;
    }

    saveToFile(document);
    currentFile->close();
}

void InputOutput::saveToApdf(Document& document){
    if (currentFile==nullptr){
        QString fileName = QFileDialog::getSaveFileName(nullptr,"Save as...",QString(), QObject::tr("APDF format (*.apdf)"));
        saveToApdfAs(fileName, document);
    }
    else{
        if(!currentFile->open(QIODevice::ReadWrite)){
            QMessageBox err(QMessageBox::Critical,"Error","Can't save to file!");
            err.exec();
            return;
        }
        saveToFile(document);
        currentFile->close();
    }
}

void InputOutput::saveToFile(Document& document){
    QJsonDocument jsonDoc = fromPaperToJson(document);
    currentFile->write(jsonDoc.toJson());
}

QJsonDocument InputOutput::fromPaperToJson(Document& document){
    QJsonDocument jsonDoc;
    QJsonObject fileStruct;
    QJsonObject header;
    QJsonArray pages;

    header.insert("Document Name",QFileInfo(*currentFile).fileName());
    fileStruct.insert("Document Info", header);

    for(int i = 0; i < document.getDocumentLength(); i++){

        QJsonObject page;
        QJsonArray items;

        page.insert("Paper Type", document.getPaperAt(i)->getPageSize().name());
        page.insert("Paper Width", document.getPaperAt(i)->getPageSize().sizePoints().width());
        page.insert("Paper Height", document.getPaperAt(i)->getPageSize().sizePoints().height());
        page.insert("Page Resolution",document.getPaperAt(i)->getRes());

        for(auto item : document.getPaperAt(i)->items()){
            if(item->type() == TextTool::Type){
                QJsonObject textItem;
                TextTool *currentItem = (TextTool*)item;
                textItem.insert("x",item->scenePos().x());
                textItem.insert("y",item->scenePos().y());
                textItem.insert("type",TextTool::Type);
                textItem.insert("font",currentItem->getTextDocument()->defaultFont().toString());
                textItem.insert("data",currentItem->getTextData());
                items.append(textItem);
            }
            else if(item->type() == ImageTool::Type){
                QJsonObject imageItem;
                ImageTool *currentItem = (ImageTool*)item;
                imageItem.insert("x",item->scenePos().x());
                imageItem.insert("y",item->scenePos().y());
                imageItem.insert("scale",currentItem->getImage_scale());
                imageItem.insert("type",ImageTool::Type);

                QByteArray imageBytes;
                QBuffer buffer(&imageBytes);

                buffer.open(QIODevice::WriteOnly);
                buffer.close();
                currentItem->getOriginalPixmap().save(&buffer,"PNG");



                imageItem.insert("data",QString(imageBytes.toBase64()));
                items.append(imageItem);
            }
            else if(item->type() == FormulaTool::Type){
                QJsonObject formulaItem;
                FormulaTool *currentItem = (FormulaTool*)item;
                formulaItem.insert("x",item->scenePos().x());
                formulaItem.insert("y",item->scenePos().y());
                formulaItem.insert("type",FormulaTool::Type);

                formulaItem.insert("latex",currentItem->getLatexString());
                formulaItem.insert("latex res",currentItem->getLatexRes());

                items.append(formulaItem);

            }
        }

        page.insert("Page number", i+1);
        page.insert("Items",items);
        pages.append(page);
    }

    fileStruct.insert("Pages",pages);
    jsonDoc.setObject(fileStruct);

    return jsonDoc;

}

void InputOutput::openApdf(QString& fileName, Document& document){
    if(fileName == "")
        return;
    if(currentFile == nullptr){
        currentFile = new QFile(fileName);
        if(!currentFile->open(QIODevice::ReadWrite)){
            QMessageBox err(QMessageBox::Critical,"Error","Unable to open selected file");
            err.exec();
            return;
        }

    }

    else {
       delete currentFile;
       currentFile = new QFile(fileName);
       if(!currentFile->open(QIODevice::ReadWrite)){
           QMessageBox err(QMessageBox::Critical,"Error","Unable to open selected file");
           err.exec();
           return;
       }

    }
    // TODO: mozda bi bilo lakse da se ponovo izgenerise dokument, proveriti ovo
    document.clearAllPages();

//    for(auto item: document.getCurrentPage()->items()){
//        if (item->type() != QGraphicsRectItem::Type){
//            document.getCurrentPage()->removeItem(item);
//            delete item;
//        }
//    }


    QByteArray fileData = currentFile->readAll();
    QJsonDocument jsonData = QJsonDocument::fromJson(fileData);

    QJsonArray pages = jsonData["Pages"].toArray();

     for(auto page:pages){
        QJsonObject aPage = page.toObject();
        QSize pageDimensions(aPage["Paper Width"].toInt(),aPage["Paper Height"].toInt());
        QPageSize pageSize = QPageSize(pageDimensions,aPage["Paper Type"].toString());

        document.appendPage(pageSize, aPage["Page Resolution"].toInt(), nullptr);
        QJsonArray items = aPage["Items"].toArray();
        for(auto item:items){
            QJsonObject currItem = item.toObject();
            if(currItem["type"] == TextTool::Type){

                TextTool *currTool = new TextTool(32);
                currTool->setTextData(currItem["data"].toString());
                QFont font;
                font.fromString(currItem["font"].toString());
                currTool->getTextDocument()->setDefaultFont(font);
                currTool->setPos(currItem["x"].toDouble(),currItem["y"].toDouble());

                document.getLastPage()->addItem(currTool);
            }
            else if (currItem["type"] == ImageTool::Type){
                ImageTool *currTool = new ImageTool();
                QByteArray imageBytes = QByteArray::fromBase64(currItem["data"].toString().toLatin1());

                QPixmap p;
                p.loadFromData(imageBytes,"PNG");
                currTool->setImage_scale(currItem["scale"].toDouble());
                int width = p.width()*currTool->getImage_scale();
                int height = p.height()*currTool->getImage_scale();
                currTool->setOriginalHeight(p.height());
                currTool->setOriginalWidth(p.width());
                currTool->setOriginalPixmap(p);
                currTool->setPixmap(p.scaled(width,height));
                currTool->setPos(currItem["x"].toDouble(),currItem["y"].toDouble());

                document.getLastPage()->addItem(currTool);
            }
            else if(currItem["type"] == FormulaTool::Type){
                FormulaTool *currTool = new FormulaTool(currItem["latex"].toString(),currItem["latex res"].toInt());
                currTool->setPos(currItem["x"].toDouble(),currItem["y"].toDouble());

                document.getLastPage()->addItem(currTool);
            }
        }

    }

    currentFile->close();
    document.setCurrentPage(1);
}

QFile *InputOutput::getCurrentFile() const
{
    return currentFile;
}

void InputOutput::setCurrentFile(QFile *newCurrentFile)
{
    currentFile = newCurrentFile;
}

void InputOutput::clearCurrentFile()
{
    delete currentFile;
    currentFile=nullptr;
}
