#include "SqliteDataReader.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

SqliteDataReader::SqliteDataReader(std::shared_ptr<IOCContainer> ioc)
{
    _parser = ioc->GetObject<IDateTimeParser>();
}

std::shared_ptr<QVector<QPair<QDateTime, qreal>>> SqliteDataReader::ReadData(const QString& filePath)
{
    auto result = std::make_shared<QVector<QPair<QDateTime, qreal>>>();

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

    result->reserve(query.size());

    while (query.next()) {
        QDateTime date = _parser->ParseDateTime(query.value(0).toString());
        bool ok;
        qreal value = query.value(1).toReal(&ok);
        if (date.isValid() && ok) result->append({ date, value });
        else qWarning() << "Invalid data at row " << query.at();
    }

    db.close();
    std::sort(result->begin(), result->end());
    return result;
}
