#include "tooloptions.h"

ToolOptions::ToolOptions(QObject *parent) : QObject(parent)
{

}

void ToolOptions::componentFocused(QGraphicsItem * current, QGraphicsItem *previous)
{
     if(current!=nullptr){

        if(componentOptionsHolder!=nullptr){
            delete componentOptionsHolder;
            componentOptionsHolder = nullptr;
        }

        componentOptionsHolder = new QGroupBox;
        componentOptionsHolder->setFixedWidth(150);
        componentOptionsHolder->setTitle("Component options");
        componentOptionsHolder->setObjectName("componentOpts");

        if(current->type() == TextTool::Type){
           setTextToolOptions(*(TextTool*)current);
        }

        else if (current->type() == ImageTool::Type){
            setImageToolOptions(*(ImageTool*)current);
        }

        emit componentOptionsReady(componentOptionsHolder);
     }

     if(current == nullptr && previous->type()==TextTool::Type){
        if(fontSelector->hasFocus() or fontSize->hasFocus() ){
            return;
        }
        else{
            emit removeComponentOptions();
        }
    }

    else if (current == nullptr && previous->type()==ImageTool::Type){

        if(scaleSelector->hasFocus()){
            return;
        }
        else{

            emit removeComponentOptions();
        }
    }


}

QGroupBox *ToolOptions::getComponentOptionsHolder() const
{
    return componentOptionsHolder;
}

void ToolOptions::setTextToolOptions(TextTool& current)
{
    itemType = current.type();
    itemToEdit = &current;
    componentOptionsHolder->setLayout(current.getToolOptions());

    for(int i=0;i<componentOptionsHolder->layout()->count();i++)
        if(componentOptionsHolder->layout()->itemAt(i)->widget()->objectName()=="fontSelector"){
            fontSelector = (QFontComboBox*)componentOptionsHolder->layout()->itemAt(i)->widget();
            fontSelector->setCurrentFont(current.getTextDocument()->defaultFont());

        }
        else if (componentOptionsHolder->layout()->itemAt(i)->widget()->objectName()=="fontSizes") {
           fontSize = (QComboBox*)componentOptionsHolder->layout()->itemAt(i)->widget();
           fontSize->setCurrentText(QString::number(qRound(current.getTextDocument()->defaultFont().pointSize() / (300/72.0))));

    }

    connect(fontSize,SIGNAL(currentTextChanged(QString)),this,SLOT(changeTextToolFontSize(QString)));
    connect(fontSelector,SIGNAL(currentFontChanged(QFont)),this,SLOT(changeTextToolFont(QFont)));
}

void ToolOptions::setImageToolOptions(ImageTool& current)
{
    itemToEdit = &current;
    componentOptionsHolder->setLayout(current.getToolOptions());
    for(int i=0;i<componentOptionsHolder->layout()->count();i++)
        if(componentOptionsHolder->layout()->itemAt(i)->widget()->objectName()=="scaleSelector"){
            scaleSelector = (QSlider*)componentOptionsHolder->layout()->itemAt(i)->widget();
            connect(scaleSelector,SIGNAL(valueChanged(int)),this,SLOT(changeImageToolScale(int)));
        }
}

void ToolOptions::changeTextToolFont(QFont newFont)
{

    TextTool* current = (TextTool*)itemToEdit;

    if(fontSize!=nullptr){
        int newSize = fontSize->currentText().toInt() * (300/72.0);
        newFont.setPointSize(newSize);
    }

    current->getTextDocument()->setDefaultFont(newFont);
    emit updateToolSize(current);
    current->setFocus();
}

void ToolOptions::changeTextToolFontSize(QString newSize)
{

    TextTool* current = (TextTool*)itemToEdit;
    QFont newFont = current->getTextDocument()->defaultFont();
    int newPointSize = newSize.toInt();
    newFont.setPointSize(newPointSize * (300/72.0));
    current->getTextDocument()->setDefaultFont(newFont);
    emit updateToolSize(current);
    newPointSize = qRound(current->getTextDocument()->defaultFont().pointSize() / (300/72.0));
    fontSize->setCurrentText(QString::number(newPointSize));
    current->setFocus();
}

void ToolOptions::changeImageToolScale(int percentage)
{
    qreal newScale = percentage / 100.0;

    ImageTool* current = (ImageTool*)itemToEdit;
    current->setScaledPixmap(newScale);
    emit updateToolSize(current);
    scaleSelector->setValue(qRound(current->getImage_scale()*100));
}

int ToolOptions::getPaperHeight() const
{
    return paperHeight;
}

void ToolOptions::setPaperHeight(int newPaperHeight)
{
    paperHeight = newPaperHeight;
}

int ToolOptions::getPaperWidth() const
{
    return paperWidth;
}

void ToolOptions::setPaperWidth(int newPaperWidth)
{
    paperWidth = newPaperWidth;
}

void ToolOptions::deleteTools(){
    if(componentOptionsHolder!=nullptr){
        delete componentOptionsHolder;
        componentOptionsHolder=nullptr;
    }
}

