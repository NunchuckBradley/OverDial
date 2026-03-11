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
    static QString getConfigPath();
    static QString getAppPath();
    static void setDefaultConfigFiles();
    static void deleteConfig(int dialId);

    static Dial importConfigFiles();
    static QString extractSingleKeyPairValueFromJson(QString* json, QString key);
};

#endif // DEFAULT_H
