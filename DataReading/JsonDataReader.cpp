#include "JsonDataReader.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

JsonDataReader::JsonDataReader(std::shared_ptr<IDateTimeParser> parser)
{
    _parser = parser;
}

QVector<QPair<QDateTime, qreal>> JsonDataReader::ReadData(const QString& filePath)
{
    QVector<QPair<QDateTime, qreal>> result;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open file:" << filePath;
        return result;
    }

    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (jsonDoc.isNull()) {
        qWarning() << "Invalid JSON document";
        return result;
    }

    QJsonArray jsonArr = jsonDoc.array();
    for (int i = 0; i < jsonArr.size(); i++) {
        auto obj = jsonArr[i].toObject();
        QDateTime date;
        double value = 0;
        bool ok = false;
        for (const QJsonValue& jsonVal : obj) {
            if (jsonVal.isString()) date = _parser->ParseDateTime(jsonVal.toString());
            else if (jsonVal.isDouble()) {
                value = jsonVal.toDouble();
                ok = true;
            }
        }
        if (date.isValid() && ok) result.append({ date, value });
        else qWarning() << "Invalid data at record " << i;
    }

    return result;
}
