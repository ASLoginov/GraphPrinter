#ifndef IDATAREADER_H
#define IDATAREADER_H

#include <memory>
#include <QDateTime>

class IDataReader
{
public:
    virtual ~IDataReader() = default;
    virtual QVector<QPair<QDateTime, qreal>> ReadData(const QString& filePath) = 0;
};

#endif // IDATAREADER_H
