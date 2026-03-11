#ifndef DIAL_H
#define DIAL_H

#include "dialkey.h"
#include <QApplication>

class Dial
{
public:
    Dial();
    int keyCount = 0;
    QString dialId; // each group/file has individual id attatched, this links to them, just the name for the config
    int setId; // which dial this is in the group
    DialKey* keys[100]; // pointer to keys "array" of items
    QString keyBind; // activation key for this dial

    QString exportToJson();
    bool importFromJson(QString* json);
};

#endif // DIAL_H
