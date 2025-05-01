#include "SqliteDataReader.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

SqliteDataReader::SqliteDataReader(std::shared_ptr<IDateTimeParser> parser)
{
    _parser = parser;
}

std::shared_ptr<QMap<QDateTime, double>> SqliteDataReader::ReadData(const QString& filePath)
{
    auto result = std::make_shared<QMap<QDateTime, double>>();

    if (!QSqlDatabase::isDriverAvailable("QSQLITE")) {
        qWarning() << "SQLite driver is unavailable!";
        return result;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
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

    while (query.next()) {
        QDateTime date = _parser->ParseDateTime(query.value(0).toString());
        bool ok;
        double value = query.value(1).toDouble(&ok);
        if (date.isValid() && ok) result->insert(date, value);
        else qWarning() << "Invalid data at row " << query.at();
    }

    db.close();
    return result;
}
