#ifndef KEYCHECKER_H
#define KEYCHECKER_H

#include <QMainWindow>
#include <QGuiApplication>

namespace Ui {
class KeyChecker;
}

class KeyChecker : public QMainWindow
{
    Q_OBJECT

public:
    explicit KeyChecker(QWidget *parent = nullptr);
    ~KeyChecker();
    QNativeInterface::QX11Application *appInfo;

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void hoverMoveEvent(QHoverEvent *event);

public slots:
    void show_window();

private slots:
    // void on_outputkeyChecker_focusInEvent();

private:
    Ui::KeyChecker *ui;


};

#endif // KEYCHECKER_H
