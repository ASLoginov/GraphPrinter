#ifndef IDATAREADER_H
#define IDATAREADER_H

#include <QtGlobal>
#include <memory>
#include <QDateTime>

class IDataReader
{
public:
    virtual ~IDataReader() {}
    virtual std::shared_ptr<QMap<QDateTime, double>> ReadData(const QString& filePath) = 0;
};

#endif // IDATAREADER_H
