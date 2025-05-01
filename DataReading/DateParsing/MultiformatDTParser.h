#ifndef MULTIFORMATDTPARSER_H
#define MULTIFORMATDTPARSER_H

#include "IDateTimeParser.h"
#include <QSet>

class MultiformatDTParser : public IDateTimeParser
{
    QSet<QString> _availableFormats;
public:
    MultiformatDTParser();
    void AddFormat(const QString& format);
    void RemoveFormat(const QString& format);
    void ClearFormats();
    QDateTime ParseDateTime(const QString& strDate);
};

#endif // MULTIFORMATDTPARSER_H
