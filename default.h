#ifndef DEFAULT_H
#define DEFAULT_H

#include <QApplication>
#include "dial.h"

class Default
{
public:
    Default();
    static QString appName;
    static QString configName;
    static QString configPath;
    static QString configSuffix;
    static QString getConfigPath();
    static QString getAppPath();
    static void setDefaultConfigFiles();
    static void deleteConfig(QString dialId);

    static Dial importConfigFile(QString dialId);
    static QString jsonGetKeyValue(QString* json, QString key);
};

#endif // DEFAULT_H
