#ifndef DIALKEY_H
#define DIALKEY_H

#include <QApplication>

class DialKey
{
public:
    DialKey();
    bool isActive = false;
    int weight;
    QString keyEmulate; // "shift+p", "l", "ctrl+shift+m"
    QString imagePath = "";

    QString exportToJson();
    bool importFromJson(QString* json);
};

#endif // DIALKEY_H
