#ifndef TOOLOPTIONS_H
#define TOOLOPTIONS_H

#include <QObject>
#include <QGraphicsItem>
#include <QComboBox>
#include <QFontComboBox>
#include <QFont>
#include <QSlider>
#include <QGroupBox>
#include "texttool.h"
#include "imagetool.h"

class ToolOptions : public QObject
{
    Q_OBJECT
public:
    explicit ToolOptions(QObject *parent = nullptr);

    QGroupBox *getComponentOptionsHolder() const;
    void deleteTools();

    int getPaperWidth() const;
    void setPaperWidth(int newPaperWidth);

    int getPaperHeight() const;
    void setPaperHeight(int newPaperHeight);

signals:
    void componentOptionsReady(QGroupBox*);
    void removeComponentOptions();
    void updateToolSize(QGraphicsItem*);

public slots:
    void componentFocused(QGraphicsItem*,QGraphicsItem*);
    void changeTextToolFont(QFont);
    void changeTextToolFontSize(const QString&);
    void changeImageToolScale(int);


private:
    QGraphicsItem* itemToEdit = nullptr;
    QGroupBox* componentOptionsHolder = nullptr;

    QFontComboBox* fontSelector = nullptr;
    QComboBox* fontSize = nullptr;

    QSlider* scaleSelector = nullptr;

    int itemType;
    int paperWidth;
    int paperHeight;

    void setTextToolOptions(TextTool&);
    void setImageToolOptions(ImageTool&);

};

#endif // TOOLOPTIONS_H
