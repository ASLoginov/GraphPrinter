#ifndef JSONDATAREADER_H
#define JSONDATAREADER_H

#include "IDataReader.h"
#include "DateParsing/IDateTimeParser.h"

class JsonDataReader : public IDataReader
{
    std::shared_ptr<IDateTimeParser> _parser;
public:
    JsonDataReader(std::shared_ptr<IDateTimeParser> parser);
    QVector<QPair<QDateTime, qreal>> ReadData(const QString& filePath);
};

#endif // JSONDATAREADER_H
