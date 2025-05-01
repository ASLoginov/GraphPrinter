#ifndef SQLITEDATAREADER_H
#define SQLITEDATAREADER_H

#include "IDataReader.h"
#include "IDateTimeParser.h"

class SqliteDataReader : public IDataReader
{
    std::shared_ptr<IDateTimeParser> _parser;
public:
    SqliteDataReader(std::shared_ptr<IDateTimeParser> parser);
    std::shared_ptr<QMap<QDateTime, double>> ReadData(const QString& filePath);
};

#endif // SQLITEDATAREADER_H
