#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//     Initializing UI and paper, addding tools
//     to the groupbox and making sure paper stays in the view
    document = new Document(this);
    pageController = new DocumentPageController(0, 1);

    //initRulers();

    io = new InputOutput();
    toolOpts = new ToolOptions();
    ui->groupBox->setFixedWidth(150);
    QVBoxLayout *vbox = new QVBoxLayout;
    DraggableTool *header    = new DraggableTool(":/icons/header.png","Header");
    DraggableTool *paragraph = new DraggableTool(":/icons/paragraph.png","Paragraph");
    DraggableTool *image = new DraggableTool(":/icons/imagetool.png","Image");
    DraggableTool *formula = new DraggableTool(":/icons/formula.png","Formula");

    QLabel *zoomLabel = new QLabel(tr("Zoom in & out"));
    zoomSpinBox = new QSpinBox;
    zoomSpinBox->setRange(10, 1000);
    zoomSpinBox->setSingleStep(10);
    zoomSpinBox->setSuffix("%");
    zoomSpinBox->setValue(100);
    currentScale=100;


    vbox->setAlignment(Qt::AlignTop);

    vbox->addWidget(zoomLabel);
    vbox->addWidget(zoomSpinBox);
    vbox->addWidget(header);
    vbox->addWidget(paragraph);
    vbox->addWidget(image);
    vbox->addWidget(formula);

    ui->groupBox->setLayout(vbox);

    ui->graphicsView->setBackgroundBrush(QBrush(Qt::gray));
    ui->graphicsView->setScene(document->getPaperAt(0));

    ui->graphicsView->fitInView(document->getPaperAt(0)->sceneRect());
    ui->graphicsView->centerOn(0,0);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    ui->gridLayout->addLayout(pageController, 2, 1);

    this->toolbar = new DocumentToolbar();
    this->addToolBar(toolbar);

    // TODO: povezati ruler

    connect(toolbar, &DocumentToolbar::signalToggleGridVisibility, document, &Document::slotToggleGridVisibility);
    connect(toolbar, &DocumentToolbar::signalInsertPage, document, &Document::addPage);
    connect(toolbar, &DocumentToolbar::signalDeletePage, document, &Document::deleteCurrentPage);

    connect(pageController, &DocumentPageController::nextPage, document, &Document::nextPage);
    connect(pageController, &DocumentPageController::prevPage, document, &Document::prevPage);
    connect(pageController, &DocumentPageController::setCurrentPage, document, &Document::setCurrentPage);

    connect(document, &Document::currentPageChanged, pageController, &DocumentPageController::currentPageChanged);
    connect(document, &Document::documentLengthChanged, pageController, &DocumentPageController::documentLengthChanged);

    connect(document, &Document::currentPageChanged, this, &MainWindow::setNewPageScene);
    connect(document, &Document::currentPagePropertiesChanged, this, &MainWindow::resetPageViewScale);

    connect(document, SIGNAL(signalFocusItemChanged(QGraphicsItem*,QGraphicsItem*,Qt::FocusReason)), toolOpts,SLOT(componentFocused(QGraphicsItem*,QGraphicsItem*)));
    connect(toolOpts,SIGNAL(componentOptionsReady(QGroupBox*)),this,SLOT(addToolOptions(QGroupBox*)));
    connect(toolOpts, SIGNAL(removeComponentOptions()),this, SLOT(removeToolOptions()));
    connect(toolOpts,SIGNAL(updateToolSize(QGraphicsItem*)),document, SLOT(slotUpdateItemGeometry(QGraphicsItem*)));
    connect(zoomSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::on_actionZoomTriggered);
    connect(document, SIGNAL(signalItemRemoved()),this,SLOT(removeToolOptions()));
}

// TODO: refactor/split
void MainWindow::initRulers(){
    verticalRuler = new Ruler(Ruler::RulerOrientation::VERTICAL, QPageSize::A4, 300);
    ui->graphicsViewRulerVertical->setBackgroundBrush(QBrush(Qt::lightGray));
    ui->graphicsViewRulerVertical->setScene(verticalRuler);
    ui->graphicsViewRulerVertical->fitInView(verticalRuler->sceneRect());
    ui->graphicsViewRulerVertical->centerOn(0,0);
    ui->graphicsViewRulerVertical->setRenderHint(QPainter::Antialiasing);

    horizontalRuler = new Ruler(Ruler::RulerOrientation::HORIZONTAL, QPageSize::A4, 300);
    ui->graphicsViewRulerHorizontal->setBackgroundBrush(QBrush(Qt::lightGray));
    ui->graphicsViewRulerHorizontal->setScene(horizontalRuler);
    ui->graphicsViewRulerHorizontal->fitInView(horizontalRuler->sceneRect());
    ui->graphicsViewRulerHorizontal->centerOn(0,0);
    ui->graphicsViewRulerHorizontal->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::setViewScale(const QPageSize& pageSize)
{
    QScreen *srn = QApplication::screens().at(0);
    qreal dotsPerInch = (qreal)srn->logicalDotsPerInch();
    QSizeF screenPixelSize = QPageSize::sizePixels(pageSize.id(),dotsPerInch);
    QSizeF viewSize=ui->graphicsView->viewport()->size();
    double viewScale;
    if(screenPixelSize.width()>screenPixelSize.height())
    {
        viewScale=viewSize.width()/screenPixelSize.width();
    }
    else
    {
        viewScale=viewSize.height()/screenPixelSize.height();
    }
    zoomSpinBox->setValue(int(viewScale*100));
}

void MainWindow::setNewPageScene(int newPageIndex)
{
    document->getCurrentPage()->clearFocus();
    removeToolOptions();
    Paper *currentPage = document->getCurrentPage();
    connect(currentPage,SIGNAL(focusItemChanged(QGraphicsItem*,QGraphicsItem*,Qt::FocusReason)),toolOpts,SLOT(componentFocused(QGraphicsItem*,QGraphicsItem*)));
    setViewScale(currentPage->getPageSize());
    ui->graphicsView->setScene(currentPage);
}

void MainWindow::resetPageViewScale()
{
    Paper *currentPage = document->getCurrentPage();
    setViewScale(currentPage->getPageSize());
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Redefining mainwindow events in order to resize paper on window resize while keeping aspect ratio

void MainWindow::showEvent(QShowEvent *e)
{
    if(firstShow)
    {
        firstShow=false;
        setViewScale(document->getCurrentPage()->getPageSize());

        ui->graphicsView->fitInView(0,0,document->getCurrentPage()->width(),document->getCurrentPage()->height(),Qt::KeepAspectRatio);
    }
    QWidget::showEvent(e);
}

void MainWindow::changeEvent(QEvent *e)
{
    if(e->type() == QEvent::WindowStateChange){
        if(isMaximized()){
            setViewScale(document->getCurrentPage()->getPageSize());
        }
    }


}

/*void MainWindow::resizeEvent(QResizeEvent *e){
    ui->graphicsView->fitInView(0,0,document->getCurrentPage()->width(),document->getCurrentPage()->height(),Qt::KeepAspectRatio);

}*/

// Quit application
void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


// Initializing About menu and displaying it

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox msgBox (QMessageBox::Information,"About","<center>Academic PDF Creator</center>",QMessageBox::Ok);
    msgBox.setInformativeText("<center>Work in progress...</center>");
    msgBox.exec();

}


// Setting up QPrinter object for exporting to a PDF file.
// This is done by grabbing the rendered scene and providing it to the painter which we provide to the printer.

void MainWindow::on_actionExport_triggered()
{
    InputOutput::exportToPdf(*document);
}

// Creating a QPrinter object used for printing to a real printer. This is done by calling the system print dialog
// and sending the rendered graphics scene as the data input

void MainWindow::on_actionPrint_triggered()
{
    InputOutput::printDocument(*document);
}

//Creating and opening the page setup window

void MainWindow::on_actionPage_Setup_triggered()
{
    PageSetup *window = new PageSetup(*document, *(ui->graphicsView), this);
    window->exec();
    delete window;

}


void MainWindow::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Save as...",QString(),tr("APDF format (*.apdf)"));
    io->saveToApdfAs(fileName, *document);

}

void MainWindow::on_actionSave_triggered()
{
    io->saveToApdf(*document);
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open APDF file",QString(),"APDF file (*.apdf)");
    io->openApdf(fileName,*document);
}


void MainWindow::on_actionNew_triggered()
{

//    for(auto item:ui->graphicsView->scene()->items()){
//        if (item->type() != QGraphicsRectItem::Type){
//            ui->graphicsView->scene()->removeItem(item);
//            delete item;
//        }
//    }

    document->createNewDocument();
    //document->addPage();

    if(io->getCurrentFile() != nullptr){
        io->clearCurrentFile();
    }
}

void MainWindow::addToolOptions(QGroupBox * /*unused*/)
{
    ui->verticalLayout_2->addWidget(toolOpts->getComponentOptionsHolder());
}

void MainWindow::removeToolOptions()
{
    itemToEdit = nullptr;
    toolOpts->deleteTools();
}

void MainWindow::on_actionZoomTriggered(int newScale)
{
    ui->graphicsView->setTransformationAnchor((QGraphicsView::AnchorUnderMouse));
    ui->graphicsView->scale(double(newScale)/currentScale,double(newScale)/currentScale);
    currentScale=newScale;
}

void MainWindow::on_PaperRedrawn()
{
    zoomSpinBox->setValue(100);
}


