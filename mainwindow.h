#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dial.h"

#include <QMainWindow>
#include <QGuiApplication>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // void on_actionKey_Checker_clicked();
    void App(QGuiApplication *parent = nullptr);
    QNativeInterface::QX11Application *appInfo;
    Dial* dials;
    int dialCount;

    void updateDials();
    void updateSelection();

public slots:
    void MainWindowTestSlot();

private slots:
    void on_saveSelect_activated(int index);

    void on_saveButton_clicked();

    void on_saveSelect_currentTextChanged(const QString &arg1);

private:
    QGuiApplication *parentApp;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
