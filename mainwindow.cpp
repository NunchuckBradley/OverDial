#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "keychecker.h"

#include <QObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // create slot to connect the windows together
    KeyChecker *keycheck = new KeyChecker();
    // QPushButton *myButton = findChild<QPushButton*>("actionKey_Checker");
    QObject::connect(ui->actionKey_Checker, &QAction::triggered, keycheck, &KeyChecker::show_window);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::MainWindowTestSlot()
{
    this->destroy();
}

void MainWindow::App(QGuiApplication *app)
{
    parentApp = app;
}

void MainWindow::on_saveSelect_activated(int index)
{
    // Pull recent changes and any log files saved in .config/OverDial/dials
}

