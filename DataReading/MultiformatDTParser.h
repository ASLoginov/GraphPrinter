#ifndef MULTIFORMATDTPARSER_H
#define MULTIFORMATDTPARSER_H

#include "IDateTimeParser.h"
#include <QSet>

class MultiformatDTParser : public IDateTimeParser
{
    QSet<QString> availableFormats;
public:
    MultiformatDTParser();
    void AddFormat(const QString& format);
    void RemoveFormat(const QString& format);
    void RemoveAllFormats();
    QDateTime ParseDateTime(const QString& strDate);
};

#endif // MULTIFORMATDTPARSER_H
