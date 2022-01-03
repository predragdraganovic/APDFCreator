#include "texttool.h"

// Constructor for text based items
// Calculates the proper pixel size for scaled font size and sets the font
// and placeholder text. It also defines the item behavior.

TextTool::TextTool(int size, QGraphicsItem* parent)
{
    textDocument = new QTextDocument();
    QFont font = QFont("Helvetica");
    font.setPointSize(size * (300/72.0));
    textDocument->setDefaultFont(font);
    QTextCursor *tc = new QTextCursor(textDocument);
    setTextCursor(*tc);
    this->textCursor().insertText("Double click to edit");

    setDocument(textDocument);


    setFlags(QGraphicsItem::ItemIsMovable);

    setTextInteractionFlags(Qt::NoTextInteraction);


}


// Changes the text edit interaction flags in order to make item movable.
// It is impossible to move items with TextEditorInteraction due to Qt limitations.

void TextTool::focusOutEvent(QFocusEvent *event)
{
    if(textInteractionFlags() ==  Qt::TextEditorInteraction)
        setTextInteractionFlags(Qt::NoTextInteraction);
    QTextCursor c = textCursor();
    c.clearSelection();
    setTextCursor(c);
    QGraphicsTextItem::focusOutEvent(event);
}

// Double click to edit text

bool TextTool::sceneEvent(QEvent *event)
{
    if(event->type() == QEvent::GraphicsSceneMouseDoubleClick){
        setTextInteractionFlags(Qt::TextEditorInteraction);
        bool ret = QGraphicsTextItem::sceneEvent(event);
        setFocus(Qt::MouseFocusReason);
        return ret;
    }
    return QGraphicsTextItem::sceneEvent(event);
}

QString TextTool::getTextData() const
{
    return textDocument->toMarkdown();
}

void TextTool::setTextData(QString text)
{
    textDocument->setMarkdown(text);
}

QTextDocument *TextTool::getTextDocument() const
{
    return textDocument;
}

QVBoxLayout *TextTool::getToolOptions() const
{
    QVBoxLayout* optsLayout = new QVBoxLayout;

    QLabel* fontSelectorLabel = new QLabel("Select a font:");
    QLabel* fontSizeLabel = new QLabel("Select a size:");
    QFontComboBox* fontSelector = new QFontComboBox;

    fontSelector->setMaximumWidth(130);
    fontSelector->setObjectName("fontSelector");
    QComboBox* fontSizes = new QComboBox();
    fontSizes->setObjectName("fontSizes");
    fontSizes->setEditable(true);
    fontSizes->addItems(QStringList()<<"8"<<"9"<<"10"<<"11"<<"12"<<"14"<<"16"<<"18"<<"20"<<"22"<<"24"<<"26"<<"28"<<"36"<<"48"<<"72");
    optsLayout->addWidget(fontSelectorLabel);
    optsLayout->addWidget(fontSelector);
    optsLayout->addWidget(fontSizeLabel);
    optsLayout->addWidget(fontSizes);

    return optsLayout;

}







