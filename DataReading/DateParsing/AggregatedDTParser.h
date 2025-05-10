#ifndef AGGREGATEDDTPARSER_H
#define AGGREGATEDDTPARSER_H

#include "IDateTimeParser.h"
#include <memory>
#include <unordered_set>

class AggregatedDTParser : public IDateTimeParser
{
    std::unordered_set<std::shared_ptr<IDateTimeParser>> _parsers;
public:
    AggregatedDTParser();
    void AddParser(std::shared_ptr<IDateTimeParser> parser);
    void RemoveParser(std::shared_ptr<IDateTimeParser> parser);
    void ClearParsers();
    QDateTime ParseDateTime(const QString& strDate);
};

#endif // AGGREGATEDDTPARSER_H
