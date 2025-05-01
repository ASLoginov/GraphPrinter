#ifndef DATEANDMINUTESPARSER_H
#define DATEANDMINUTESPARSER_H

#include "IDateTimeParser.h"
#include <memory>

class DateAndMinutesParser : public IDateTimeParser
{
    std::shared_ptr<IDateTimeParser> _dateParser;
public:
    DateAndMinutesParser(std::shared_ptr<IDateTimeParser> dateParser);
    void SetDateParser(std::shared_ptr<IDateTimeParser> dateParser);
    QDateTime ParseDateTime(const QString& strDate);
};

#endif // DATEANDMINUTESPARSER_H
