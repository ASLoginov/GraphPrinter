#include "MultiformatDTParser.h"

MultiformatDTParser::MultiformatDTParser()
{

}

void MultiformatDTParser::AddFormat(const QString& format)
{
    _availableFormats.insert(format);
}

void MultiformatDTParser::RemoveFormat(const QString& format)
{
    _availableFormats.remove(format);
}

void MultiformatDTParser::ClearFormats()
{
    _availableFormats.clear();
}

QDateTime MultiformatDTParser::ParseDateTime(const QString& strDate)
{
    foreach (const QString& format, _availableFormats) {
        QDateTime dt = QDateTime::fromString(strDate, format);
        if (dt.isValid()) return dt;
    }
    return QDateTime();
}
