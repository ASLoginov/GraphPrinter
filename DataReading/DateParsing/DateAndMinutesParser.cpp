#include "DateAndMinutesParser.h"

DateAndMinutesParser::DateAndMinutesParser(std::shared_ptr<IDateTimeParser> dateParser)
{
    _dateParser = dateParser;
}

void DateAndMinutesParser::SetDateParser(std::shared_ptr<IDateTimeParser> dateParser)
{
    _dateParser = dateParser;
}

QDateTime DateAndMinutesParser::ParseDateTime(const QString& strDate)
{
    QStringList parts = strDate.split(' ');
        if (parts.size() != 2) return QDateTime();

        QDateTime date = _dateParser->ParseDateTime(parts[0]);
        if (!date.isValid()) return QDateTime();

        bool ok;
        int totalMinutes = parts[1].toInt(&ok);
        if (!ok || totalMinutes < 0 || totalMinutes > 1440) return QDateTime();

        date = date.addSecs(totalMinutes * 60);

        return date;
}
