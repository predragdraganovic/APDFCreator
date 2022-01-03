#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include <QMainWindow>
#include "gui/mainwindow.h"

namespace Ui {
class WelcomePage;
}

class WelcomePage : public QMainWindow
{
    Q_OBJECT

public:
    explicit WelcomePage(QWidget *parent = nullptr);
    ~WelcomePage();

signals:
    void on_btnStartNewProject_clicked();

private:
    Ui::WelcomePage *ui;
    MainWindow *mainwindow;
};

#endif // WELCOMEPAGE_H
