#ifndef SQLITEDATAREADER_H
#define SQLITEDATAREADER_H

#include "IDataReader.h"
#include "DateParsing/IDateTimeParser.h"
#include <QSqlDatabase>

class SqliteDataReader : public IDataReader
{
    static QSqlDatabase& GetDB();
    std::shared_ptr<IDateTimeParser> _parser;
public:
    SqliteDataReader(std::shared_ptr<IDateTimeParser> parser);
    QVector<QPair<QDateTime, qreal>> ReadData(const QString& filePath);
};

#endif // SQLITEDATAREADER_H
