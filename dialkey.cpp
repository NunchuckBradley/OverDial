#include "dialkey.h"
#include "default.h"

#include <iostream>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QRegularExpression>

DialKey::DialKey() {}

QString DialKey::exportToJson() {
    QString json = "{";

    std::cout << "keyemulate!!!!   " << this->keyEmulate.toStdString() << std::endl;

    json += "keyEmulate : \"" + this->keyEmulate + "\"";
    json += ", ";
    json += "weight : \"" + QString::number(this->weight) + "\"";
    json += ", ";
    json += "imagePath : \"" + this->imagePath + "\"";

    // get json output of

    return json + "}";
}

bool DialKey::importFromJson(QString* json) {

    // std::cout << json->toStdString() << std::endl;
    this->keyEmulate = Default::jsonGetKeyValue(json, "keyEmulate");
    // std::cout << "keyemulate!!!!   " << this->keyEmulate.toStdString() << std::endl;
    this->weight = Default::jsonGetKeyValue(json, "weight").toInt();
    this->imagePath = Default::jsonGetKeyValue(json, "imagePath");

    this->isActive = true;

    // QByteArrayView find("keyEmulate"); // find start of keyEmulate and chop


    // QByteArray keyPair = json_bytes.sliced(find, commaOrWhiteSpaceAfter);
    // auto json_doc = QJsonDocument::fromJson(json_bytes);

    // if (json_doc.isNull()) {
    //     std::cout << "Failed to create JSON doc." << std::endl;
    //     return false;
    // }
    // if (!json_doc.isObject()) {
    //     std::cout << "JSON is not an object." << std::endl;
    //     return false;
    // }

    // QJsonObject json_obj = json_doc.object();

    // if (json_obj.isEmpty()) {
    //     std::cout << "JSON object is empty." << std::endl;
    //     return false;
    // }

    // // step 4
    // QVariantMap result = json_obj.toVariantMap();

    return true;
}
