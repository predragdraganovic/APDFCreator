#ifndef DRAGGABLETOOL_H
#define DRAGGABLETOOL_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>

class DraggableTool : public QWidget
{
    Q_OBJECT
public:
    explicit DraggableTool(const QString& fileName,const QString& toolName, QWidget *parent = nullptr);


private:
    QLabel *toolLabel;
    QLabel *toolIcon;
    void mousePressEvent(QMouseEvent *event) override;




signals:

};

#endif // DRAGGABLETOOL_H
