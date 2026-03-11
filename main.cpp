#include "mainwindow.h"
#include "keychecker.h"
#include "default.h"

#include "dial.h"
#include "dialkey.h"

#include <iostream>

#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{
    // creates folder and example
    Default::setDefaultConfigFiles();
    // import those files/config which were created, this variable to be used and change during operation
    Dial config = Default::importConfigFiles();

    // TESTING DIALKEY JSON -- START
    // QString exampleJson = "{keyEmulate : \"lctrl+c\", weight : \"1\", imagePath : \"\"}";
    // DialKey* test = new DialKey();
    // test->importFromJson(&exampleJson);
    std::cout << "Your config is: " << config.exportToJson().toStdString() << '\n';
    // TESTING DIALKEY JSON -- END

    // // Set and Launch QT application
    // QApplication overdial(argc, argv);
    // QCoreApplication::setApplicationName("overdial");
    // QCoreApplication::setApplicationVersion("0.0.1");


    // QNativeInterface::QX11Application *appInfo = overdial.nativeInterface<QNativeInterface::QX11Application>();

    // MainWindow w;
    // w.show();

    // KeyChecker keycheck;
    // // keycheck.hide();
    // keycheck.appInfo = appInfo;

    // std::cout << "Your PATH is: " << Default::getAppPath().toStdString() << '\n';

    // return overdial.exec();

    return 1;
}
