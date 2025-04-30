#ifndef SQLITEDATAREADER_H
#define SQLITEDATAREADER_H

#include "IDataReader.h"

class SqliteDataReader : public IDataReader
{
    QString dateFormat = "YYYY-MM-DD";
public:
    SqliteDataReader() = default;
    SqliteDataReader(const QString& format);
    std::shared_ptr<QMap<QDate, double>> ReadData(const QString& filePath);
    void SetDateFormat(const QString& format);
};

#endif // SQLITEDATAREADER_H
