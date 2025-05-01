#ifndef IDATEFORMATS_H
#define IDATEFORMATS_H

#include <QDateTime>

class IDateTimeParser
{
public:
    virtual ~IDateTimeParser() {}
    virtual QDateTime ParseDateTime(const QString& strDate) = 0;
};

#endif // IDATEFORMATS_H
