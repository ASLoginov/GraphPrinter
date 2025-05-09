#include <QApplication>
#include "MainWindow.h"

#include <QDateTime>
#include <QDebug>
#include "DataReading/SqliteDataReader.h"
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

    auto multiformatParser = std::make_shared<MultiformatDTParser>();
    multiformatParser->AddFormat("dd.MM.yyyy hh:mm");
    multiformatParser->AddFormat("dd.MM.yyyy");

    auto exoticParser = std::make_shared<DateAndMinutesParser>(multiformatParser);

    auto aggregateParser = std::make_shared<AggregatedDTParser>();
    aggregateParser->AddParser(multiformatParser);
    aggregateParser->AddParser(exoticParser);

    ioc->RegisterInstance<IDateTimeParser>(aggregateParser);

    ioc->RegisterInstance<DataTypeManager, DataTypeManager, IOCContainer>();
    auto dataManager = ioc->GetInstance<DataTypeManager>();
    dataManager->AddDataType<SqliteDataReader, IDateTimeParser>("sqlite");

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

