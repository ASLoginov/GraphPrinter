#include "SqliteDataReader.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

QSqlDatabase& SqliteDataReader::GetDB()
{
    static QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    return db;
}

SqliteDataReader::SqliteDataReader(std::shared_ptr<IDateTimeParser> parser)
{
    _parser = parser;
}

QVector<QPair<QDateTime, qreal>> SqliteDataReader::ReadData(const QString& filePath)
{
    QVector<QPair<QDateTime, qreal>> result;

    QSqlDatabase& db = GetDB();

    db.setDatabaseName(filePath);
    if (!db.open()) {
        qWarning() << "Failed to open database: " << db.lastError().text();
        return result;
    }

    QSqlQuery query(db);
    QStringList tables = db.tables();
    if (!query.exec("SELECT * FROM " + tables.first())) {
        qWarning() << "Query error: " << query.lastError().text();
        db.close();
        return result;
    }

    result.reserve(query.size());

    while (query.next()) {
        QDateTime date = _parser->ParseDateTime(query.value(0).toString());
        bool ok;
        qreal value = query.value(1).toReal(&ok);
        if (date.isValid() && ok) result.append({ date, value });
        else qWarning() << "Invalid data at row " << query.at();
    }

    db.close();
    std::sort(result.begin(), result.end());
    return result;
}
