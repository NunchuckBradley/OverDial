#include "default.h"
#include "dial.h"
#include "dialkey.h"

#include <QFile>
#include <QDir>
#include <QRegularExpression>

#include <cstdlib>
#include <cassert>
#include <filesystem>
#include <iostream>

QString Default::appName = "OverDial";
QString Default::configName = "config.cfg";



Default::Default() {
}

QString Default::getAppPath() {
    if (char* env_p = std::getenv("XDG_CONFIG_HOME")) {
        return QString(env_p) + "/" + Default::appName;
    }
    else {
        return 0;
    }
}

QString Default::getConfigPath() {
    return Default::getAppPath() + "/" + Default::configName;
}

void Default::setDefaultConfigFiles() {
    QDir* appFolder = new QDir(Default::getAppPath());
    if( ! appFolder->exists() ) {
        std::cout << "Created config folder at    : " << Default::getAppPath().toStdString() << '\n';
        appFolder->mkdir(appFolder->path());
        appFolder->mkdir(Default::getConfigPath());
    }
    else {
        std::cout << "Config folder already exists..." << '\n';
    }

    if ( ! QFile::exists(Default::getConfigPath())) {
        std::cout << "Creating config file at   : " << Default::getConfigPath().toStdString() << '\n';

        Dial* standardDial = new Dial();
        standardDial->dialId = "copypaste";
        standardDial->setId = 1;
        standardDial->keyBind = QString("lctrl+rctrl");

        DialKey* copy = new DialKey();
        copy->weight = 1;
        copy->keyEmulate = QString("lctrl+c");
        copy->isActive = true;
        DialKey* paste = new DialKey();
        paste->weight = 2;
        paste->keyEmulate = QString("lctrl+v");
        paste->isActive = true;
        DialKey* cut = new DialKey();
        cut->weight = 3;
        cut->keyEmulate = QString("lctrl+x");
        cut->isActive = true;

        standardDial->keys[0] = copy;
        standardDial->keys[1] = paste;
        standardDial->keys[2] = cut;

        QString json = standardDial->exportToJson();
        // QString json = copy->exportToJson();

        // write json to the file
        QFile configFile(Default::getConfigPath());
        configFile.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&configFile);
        out << json;
        configFile.close();

        std::cout << "Config file created at   : " << Default::getConfigPath().toStdString() << '\n';

    } else {
        std::cout << "Config file already exists..." << '\n';
    }

    return;
}

void Default::deleteConfig(int dialId) {
    // incorperate dialId to delete specific ones, if 0 delete all of them
    if( dialId > 0) {

    }
    else {
        // delete whole config as a file
        QFile::remove(Default::getConfigPath());
        // recreate config file?
        // Default::setDefaultConfigFiles();
    }
}

Dial Default::importConfigFiles() {
    QFile file_obj(Default::getConfigPath());

    if (!file_obj.open(QIODevice::ReadOnly)) {
        std::cout << "Failed to open " << Default::getConfigPath().toStdString() << std::endl;
        exit(1);
    }

    // step 2
    QTextStream file_text(&file_obj);
    QString json_string;
    json_string = file_text.readAll();
    file_obj.close();
    QByteArray json_bytes = json_string.toLocal8Bit();

    Dial configs = Dial();
    configs.importFromJson(&json_string);

    return configs;
}

QString Default::extractSingleKeyPairValueFromJson(QString* json, QString key) {
    // QByteArray json_bytes = json->toLocal8Bit();
    // first find location of key value
    QString tmp = *json;
    int location = tmp.indexOf(key);
    // find next : from this key and split everything up to there, just incase our key has quotes around it
    int colonLocation = tmp.indexOf(":", location);
    // remove everything up to this
    if (location < 0 || colonLocation < 0) {
        return "JSON INVALID";
    }
    // remove leading nonsense and whitespace using trimmed
    QString from = tmp.slice(colonLocation + 1).trimmed();
    // identify the next value, possible solutions, "{", "[", "int", " \" "
    static QRegularExpression notWhiteSpace("[^\\s-]");
    // static QRegularExpression notWhiteSpace("(.|\\s)*\\S(.|\\s)*");
    // static QRegularExpression notWhiteSpace("e");
    // static QRegularExpression notWhiteSpace("([^|]*)");
    // create posibilities for this solution
    QChar val = from.at(0);

    // std::cout << "val detected... " << QString(val).toStdString() << std::endl;
    // std::cout << "timmed full ... " << from.trimmed().toStdString() << std::endl;


    // prepare for NESTED and ARRAYS and STRINGS and NUMBERS
    if (val == "{" || val == "[" || val == "\"") {
        // std::cout << "runs in here..." << std::endl;
        // std::cout << "from.size...   " << from.size() << std::endl;
        QString lb;
        QString rb;
        if (val == "{") {
            lb = "{";
            rb = "}";
        }
        if (val == "[") {
            lb = "[";
            rb = "]";
        }
        if (val == "\"") {
            lb = "\"";
            rb = "\"";
        }

        // std::cout << "lb/rb...   " << lb.toStdString() << "/" << rb.toStdString() << std::endl;

        int tally = 0; // run a tally incase there are nested objects
        for (int i = 1; i < from.size(); i++) {
            if (from.at(i) == rb) {
                // std::cout << "hit an end... tally..." << tally << std::endl;
                // std::cout << "hit an end... end..." << QString(from.at(i)).toStdString() << std::endl;
                if (tally > 0) {
                    tally--;
                }
                else {
                    std::cout << key.toStdString() << " : " << from.left(i+1).toStdString() << std::endl;
                    return from.left(i+1);
                }
            }
            if (from.at(i) == lb) {
                tally++;
            }
        }
    }
    else if (val.isDigit()) {
        return from.left(from.indexOf(notWhiteSpace, from.indexOf(notWhiteSpace)) + 1);
    }
    else {
        return "NO KEY VALUE DETECTED";
    }

    return "ERROR";

    // QByteArray fromQuote = from.slice(from.indexOf(firstCharSplit.toStdString(), 0) + 1);
    // QByteArray keyValue = fromQuote.first(fromQuote.indexOf(lastCharSplit.toStdString(), 0));
}
