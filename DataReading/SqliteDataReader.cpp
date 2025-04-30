#include "SqliteDataReader.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

SqliteDataReader::SqliteDataReader() {}

SqliteDataReader::SqliteDataReader(const QString &format)
{
    dateFormat = format;
}

std::shared_ptr<QMap<QDate, double>> SqliteDataReader::ReadData(const QString& filePath)
{
    auto result = std::make_shared<QMap<QDate, double>>();

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
        const QDate date = QDate::fromString(query.value(0).toString(), dateFormat);
        bool ok;
        const double value = query.value(1).toDouble(&ok);
        if (date.isValid() && ok) result->insert(date, value);
        else qWarning() << "Invalid data at row " << query.at();
    }
}

void SqliteDataReader::SetDateFormat(const QString& format)
{
    dateFormat = format;
}
