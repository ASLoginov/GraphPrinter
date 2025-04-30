#ifndef IDATAREADER_H
#define IDATAREADER_H

#include <QtGlobal>
#include <memory>
#include <QDate>

class IDataReader
{
    virtual ~IDataReader() {}
    virtual std::shared_ptr<QMap<QDate, double>> ReadData(const QString& filePath) = 0;
};

#endif // IDATAREADER_H
