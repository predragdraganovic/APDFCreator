#include "welcomepage.h"
#include "ui_welcomepage.h"

WelcomePage::WelcomePage(QWidget *parent) : QMainWindow(parent), ui(new Ui::WelcomePage)
{
    ui->setupUi(this);

    mainwindow = new MainWindow();
    connect(this, &WelcomePage::on_btnStartNewProject_clicked, mainwindow, &MainWindow::show);
    connect(this, &WelcomePage::on_btnStartNewProject_clicked, this, &WelcomePage::close);
}

WelcomePage::~WelcomePage() { delete ui; }

// TODO: delete when needed
// void WelcomePage::on_btnStartNewProject_clicked(){
//    mainwindow->show();
//    this->close();
//}
