#ifndef TEXTTOOL_H
#define TEXTTOOL_H

#include <QGraphicsTextItem>
#include <QGraphicsSceneEvent>
#include <QFont>
#include <QEvent>
#include <QTextDocument>
#include <QTextCursor>
#include <QVBoxLayout>
#include <QLabel>
#include <QFontComboBox>


class TextTool : public QGraphicsTextItem
{
public:
    TextTool();
    explicit TextTool(int size, QGraphicsItem *parent = nullptr);
    ~TextTool(){
        delete textDocument;
    };

    void focusOutEvent(QFocusEvent* event) override;
    bool sceneEvent(QEvent *event) override;

    QString getTextData() const;
    void setTextData(const QString& text);

    QTextDocument *getTextDocument() const;
    QVBoxLayout *getToolOptions() const;


private:
    QTextDocument *textDocument;


};

#endif // TEXTTOOL_H
