#include <QApplication>
#include "MainWindow.h"

#include <QDateTime>
#include <QDebug>
#include "DataReading/SqliteDataReader.h"
#include "DataReading/JsonDataReader.h"
#include "DataReading/DateParsing/AggregatedDTParser.h"
#include "DataReading/DateParsing/DateAndMinutesParser.h"
#include "DataReading/DateParsing/MultiformatDTParser.h"
#include "DataRendering/ImpulseChartBuilder.h"
#include "DataRendering/LineChartBuilder.h"
#include "DataRendering/ScatterChartBuilder.h"
#include "DependencyInjection/IOC_Contaner.h"
#include "DependencyInjection/DataTypeManager.h"
#include "DependencyInjection/ChartTypeManager.h"
#include "DataProcessing/DataProcessing.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto ioc = std::make_shared<IOCContainer>();
    ioc->RegisterInstance<IOCContainer>(ioc);

    ioc->RegisterInstance<MultiformatDTParser, MultiformatDTParser>();
    auto multiformatParser = ioc->GetInstance<MultiformatDTParser>();
    multiformatParser->AddFormat("dd.MM.yyyy hh:mm");
    multiformatParser->AddFormat("dd.MM.yyyy");
    multiformatParser->AddFormat("yyyy-MM-dd hh:mm");
    multiformatParser->AddFormat("yyyy-MM-dd");

    ioc->RegisterFactory<DateAndMinutesParser, DateAndMinutesParser, MultiformatDTParser>();

    ioc->RegisterInstance<AggregatedDTParser, AggregatedDTParser>();
    auto aggregateParser = ioc->GetInstance<AggregatedDTParser>();
    aggregateParser->AddParser(ioc->GetInstance<MultiformatDTParser>());
    aggregateParser->AddParser(ioc->GetInstance<DateAndMinutesParser>());
    ioc->RegisterInstance<IDateTimeParser>(aggregateParser);

    ioc->RegisterInstance<DataTypeManager, DataTypeManager, IOCContainer>();
    auto dataManager = ioc->GetInstance<DataTypeManager>();
    dataManager->AddDataType<SqliteDataReader, IDateTimeParser>("sqlite");
    dataManager->AddDataType<JsonDataReader, IDateTimeParser>("json");

    ioc->RegisterInstance<ChartTypeManager, ChartTypeManager, IOCContainer>();
    auto chartManager = ioc->GetInstance<ChartTypeManager>();
    chartManager->AddChartType<LineChartBuilder>("Line");
    chartManager->AddChartType<ScatterChartBuilder>("Scatter");
    chartManager->AddChartType<ImpulseChartBuilder>("Impulse");

    ioc->RegisterInstance<DataProcessing, DataProcessing, IOCContainer>();

    ioc->RegisterInstance<MainWindow, MainWindow, IOCContainer>();
    ioc->GetInstance<MainWindow>()->show();

    return app.exec();
}

