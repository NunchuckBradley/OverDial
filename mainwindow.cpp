#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dial.h"
#include "dialkey.h"
#include "keychecker.h"
#include "default.h"

#include <QObject>
#include <QFileDialog>
#include <QLayout>
#include <iostream>

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

void MainWindow::updateSelection() {
    for (int i = 0; i < this->dialCount; i++) {
        this->ui->saveSelect->addItem(this->dials[i].dialId);
        std::cout << "Created config folder at    : " << this->dials[i].dialId.toStdString() << '\n';
    }
}

void MainWindow::updateDials() {
    // this->dials;
    // ui->dialWidget.
}


void MainWindow::on_saveButton_clicked()
{
    if (this->ui->saveSelect->currentIndex() == 0) {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Config name"), Default::getConfigPath(), tr("Json (*json)"));
        std::cout << "Pretend file saved at    : " << fileName.toStdString() << '\n';
        // QFileDialog dialog;
        // dialog.setFileMode(QFileDialog::Directory);
        // dialog.exec();

    }
}


void MainWindow::on_saveSelect_currentTextChanged(const QString &arg1)
{
    // this->ui->dialWidget->layout()->addWidget(new QPushButton("button text"));
    // this->ui->groupBox->ad
}

