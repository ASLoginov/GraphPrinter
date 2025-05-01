#include <QApplication>

#include <QDateTime>
#include <QDebug>
#include "DataReading/SqliteDataReader.h"
#include "DataReading/DateParsing/AggregatedDTParser.h"
#include "DataReading/DateParsing/DateAndMinutesParser.h"
#include "DataReading/DateParsing/MultiformatDTParser.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);


    QString format = "yyyy.MM.dd";
    QString str = "2025.02.17";
    auto date = QDateTime::fromString(str, format);;
    qDebug() << date;

    auto multiformatParser = std::make_shared<MultiformatDTParser>();
    multiformatParser->AddFormat("dd.MM.yyyy hh:mm");
    multiformatParser->AddFormat("dd.MM.yyyy");

    auto aggregateParser = std::make_shared<AggregatedDTParser>();
    aggregateParser->AddParser(multiformatParser);

    auto exoticParser = std::make_shared<DateAndMinutesParser>(multiformatParser);
    aggregateParser->AddParser(exoticParser);

    auto sqliteReader = std::make_shared<SqliteDataReader>(aggregateParser);
    auto map = sqliteReader->ReadData("C:/Qt projects/GraphPrinter/InputData/BLOOD_SUGAR.sqlite");
    qDebug() << *map.get();

    return app.exec();
}

