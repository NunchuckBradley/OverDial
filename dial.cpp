#include "dial.h"
#include "dialkey.h"
#include "default.h"

#import <iostream>
#import <QRegularExpression>

Dial::Dial() {}

// manual export and import keybinding because there arnt many for this
QString Dial::exportToJson() {
    QString json = "{";

    json += "dialId : \"" + this->dialId + " \"";
    json += ", ";
    json += "setId : \"" + QString::number(this->setId) + " \"";
    json += ", keys: [";

    // for (DialKey* key : this->keys) {
    //     // not all arrays have been initiated, cancel most of them
    //     if (key != NULL && key != nullptr) {
    //         json += key->exportToJson();
    //         json += ",";
    //     }
    // }

    // i = 100 is how many keys limit on a dial you can have
    for (int i = 0; i < this->keyCount; i++) {
        // not all arrays have been initiated, cancel most of them
        if (this->keys[i]->isActive) {
            json += this->keys[i]->exportToJson();
            json += ",";
        }
    }

    json += "], keyBind : \"" + this->keyBind + " \"";

    // get json output of

    return json + "}";
}

bool Dial::importFromJson(QString* json) {
    this->dialId = Default::jsonGetKeyValue(json, "dialId");
    this->setId = Default::jsonGetKeyValue(json, "setId").toInt();
    this->keyBind = Default::jsonGetKeyValue(json, "keyBind");

    QRegularExpression jsonArrayToSplitAt = QRegularExpression("}\\s+,\\s+{");
    QStringList keyArray = Default::jsonGetKeyValue(json, "keys").split("},{");
    // std::cout << "keyArray: " << keyArray.join("--").toStdString() << '\n';
    for (int i = 0; i < keyArray.length(); i++) {
        QString keyJson = QString(keyArray[i]);
        DialKey* key = new DialKey();

        std::cout << "keyJson: " << keyJson.toStdString() << '\n';

        key->importFromJson(&keyJson);
        this->keys[i] = key;
        this->keyCount++;
    }

    return true;
}
