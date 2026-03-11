#include "mainwindow.h"
#include "keychecker.h"
#include "default.h"

#include "dial.h"
#include "dialkey.h"

#include <iostream>

#include <QApplication>
#include <QObject>
#include <QDir>

int main(int argc, char *argv[])
{
    // creates folder and example
    Default::setDefaultConfigFiles();
    // import those files/config which were created, this variable to be used and change during operation

    QDir configPath = QDir(Default::getConfigPath());
    QStringList cfg = configPath.entryList(QStringList() << ("*" + Default::configSuffix), QDir::Files);
    std::cout << "ls: " << cfg.join(" : ").toStdString() << '\n';
    // loop for each file in directory
    Dial configs[100];

    for (int i = 0; i < cfg.length(); i++) {
        QString dialId = cfg[i];
        cfg[i].chop(5);
        Dial idSpecific = Default::importConfigFile(dialId);
        configs[i] = idSpecific;
    }



    // TESTING DIALKEY JSON -- START
    // QString exampleJson = "{keyEmulate : \"lctrl+c\", weight : \"1\", imagePath : \"\"}";
    // DialKey* test = new DialKey();
    // test->importFromJson(&exampleJson);
    // QString exported = config.exportToJson();
    // std::cout << "Your config is: " << exported.toStdString() << '\n';
    // TESTING DIALKEY JSON -- END

    // Set and Launch QT application
    QApplication overdial(argc, argv);
    QCoreApplication::setApplicationName("overdial");
    QCoreApplication::setApplicationVersion("0.0.1");

    QNativeInterface::QX11Application *appInfo = overdial.nativeInterface<QNativeInterface::QX11Application>();

    MainWindow w;
    w.appInfo = appInfo;
    w.dialCount = cfg.length();
    w.dials = configs; // keep it as a pointer so that we can access it from outside the window function

    w.updateSelection();
    w.show();

    // KeyChecker keycheck;
    // keycheck.hide();
    // keycheck.appInfo = appInfo;

    std::cout << "Your PATH is: " << Default::getAppPath().toStdString() << '\n';

    return overdial.exec();

    // return 1;
}
