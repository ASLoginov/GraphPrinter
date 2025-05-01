#include "MultiformatDTParser.h"

MultiformatDTParser::MultiformatDTParser()
{

}

void MultiformatDTParser::AddFormat(const QString& format)
{
    availableFormats.insert(format);
}

void MultiformatDTParser::RemoveFormat(const QString& format)
{
    availableFormats.remove(format);
}

void MultiformatDTParser::RemoveAllFormats()
{
    availableFormats.clear();
}

QDateTime MultiformatDTParser::ParseDateTime(const QString& strDate)
{
    foreach (const QString& format, availableFormats) {
        QDateTime dt = QDateTime::fromString(strDate, format);
        if (dt.isValid()) return dt;
    }
    return QDateTime();
}
