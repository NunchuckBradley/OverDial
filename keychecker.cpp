#include "keychecker.h"
#include "ui_keychecker.h"

#include <X11/Xlib.h>
#include <QGuiApplication>

KeyChecker::KeyChecker(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::KeyChecker)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_Hover, true);

    ui->outputkeyChecker->setText("dipper");
}

KeyChecker::~KeyChecker()
{
    delete ui;
}

void KeyChecker::show_window()
{
    this->show();

    Display *display = XOpenDisplay(NULL);

    // XSelectInput(display, XGetWindowAttributes(display),KeyPressMask|KeyReleaseMask);
    while(0) {
        while(XPending(display)) { //Repeats until all events are computed
            XEvent KeyEvent;
            XNextEvent(display,&KeyEvent); //Gets exactly one event
            if(KeyEvent.type==KeyPress) {
                QString KeyEventCode = QString::number(KeyEvent.xkey.keycode); //Gets the key code, NOT HIS CHAR EQUIVALENT

                ui->outputkeyChecker->setText(KeyEventCode);
                this->update();

                /* Code handling a Keypress event */

            }
            // else if(KeyEvent.type==KeyRelease) {
            //     uint32_t KeyEventCode=KeyEvent.xkey.keycode;
            //     std::cout << KeyEventCode << '\n'; //Displays the key code

            //     /* Code handling a KeyRelease event */

            // }
        }

        /* General code */

    }
}


void KeyChecker::enterEvent(QEvent *event) {
    Q_UNUSED(event);
    // Change style when mouse enters: red text, light blue background
    setStyleSheet("QLabel { color: red; background-color: #cce5ff; padding: 0px; border: 2px solid #0066cc; }");
}

void KeyChecker::leaveEvent(QEvent *event) {
    Q_UNUSED(event);
    // Reset style when mouse leaves: black text, light gray background
    setStyleSheet("QLabel { color: black; background-color: #f0f0f0; padding: 0px; border: 2px solid #ccc; }");
}



void KeyChecker::hoverMoveEvent(QHoverEvent *event)
{
    Q_UNUSED(event);
    // Get mouse position relative to the label (x, y coordinates)
    // QPoint pos = event->pos();
    // Show tooltip with position (e.g., "X: 50, Y: 20")
    // setToolTip(QString("Mouse Position: X: %1, Y: %2").arg(pos.x()).arg(pos.y()));

    Display *display = XOpenDisplay(NULL);

    // XSelectInput(display, XGetWindowAttributes(display),KeyPressMask|KeyReleaseMask);
    while(1) {
        while(XPending(display)) { //Repeats until all events are computed
            XEvent KeyEvent;
            XNextEvent(display,&KeyEvent); //Gets exactly one event
            if(KeyEvent.type==KeyPress) {
                QString KeyEventCode = QString::number(KeyEvent.xkey.keycode); //Gets the key code, NOT HIS CHAR EQUIVALENT

                ui->outputkeyChecker->setText(KeyEventCode);
                this->update();

                /* Code handling a Keypress event */

            }
            // else if(KeyEvent.type==KeyRelease) {
            //     uint32_t KeyEventCode=KeyEvent.xkey.keycode;
            //     std::cout << KeyEventCode << '\n'; //Displays the key code

            //     /* Code handling a KeyRelease event */

            // }
        }

        /* General code */

    }
}

