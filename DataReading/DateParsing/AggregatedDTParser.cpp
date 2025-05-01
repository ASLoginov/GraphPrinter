#include "AggregatedDTParser.h"

AggregatedDTParser::AggregatedDTParser()
{

}

void AggregatedDTParser::AddParser(std::shared_ptr<IDateTimeParser> parser)
{
    _parsers.insert(parser);
}

void AggregatedDTParser::RemoveParser(std::shared_ptr<IDateTimeParser> parser)
{
    _parsers.erase(parser);
}

void AggregatedDTParser::ClearParsers()
{
    _parsers.clear();
}

QDateTime AggregatedDTParser::ParseDateTime(const QString& strDate)
{
    for (auto parser : _parsers) {
        QDateTime dt = parser->ParseDateTime(strDate);
        if (dt.isValid()) return dt;
    }
    return QDateTime();
}
