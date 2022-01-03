#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QGridLayout>
#include <QSharedPointer>
#include <QLabel>
#include <QToolBar>
#include <QAction>
#include <QIcon>
#include <QSpinBox>
#include "../tools/draggabletool.h"
#include "../components/documenttoolbar.h"
#include "document.h"
#include "../components/documentpagecontroller.h"
#include "components/ruler/ruler.h"
#include "../gui/paper.h"
#include "pagesetup.h"
#include "qpagesize.h"
#include "in_out/in_out.h"
#include <tools/tooloptions.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// let the compiler know such class will be defined
class DocumentToolbar;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void setNewPageScene(int newPageIndex);
    void resetPageViewScale();

private slots:
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
    void on_actionExport_triggered();
    void on_actionPrint_triggered();
    void on_actionPage_Setup_triggered();
    void on_actionSave_as_triggered();
    void on_actionSave_triggered();
    void on_actionOpen_triggered();

    void on_actionNew_triggered();

    void addToolOptions(QGroupBox*);
    void removeToolOptions();

    void on_actionZoomTriggered(int newScale);
    void on_PaperRedrawn();

private:
    void initRulers();
    void setViewScale(QPageSize pageSize);

    Ui::MainWindow *ui;
    Document *document;
    DocumentToolbar *toolbar;
    DocumentPageController *pageController;

    PageGrid* pageGrid;
    Ruler *horizontalRuler;
    Ruler *verticalRuler;

    InputOutput* io;
    ToolOptions* toolOpts;
    QSpinBox *zoomSpinBox;
    int currentScale;
    bool firstShow = true;
    virtual void showEvent(QShowEvent *e);
    //virtual void resizeEvent(QResizeEvent *e);
    virtual void changeEvent(QEvent* e);
    QGraphicsItem* itemToEdit = nullptr;

};
#endif // MAINWINDOW_H
