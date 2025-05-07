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
#include "DataReading/DataTypeManager.h"

#include <QtCharts>
using namespace QtCharts;

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

    auto manager = ioc->GetInstance<DataTypeManager>();
    manager->AddDataType<SqliteDataReader, IDateTimeParser>("sqlite");
    manager->SwitchDataType("sqlite");

    ioc->RegisterFactory<IChartBuilder, LineChartBuilder>();

    /*
    auto reader = ioc->GetInstance<IDataReader>();

    QElapsedTimer timer;

    timer.start(); // Запуск таймера
    auto data = reader->ReadData("C:/Qt projects/GraphPrinter/InputData/TEMPERATURE_NOVOSIB.sqlite");
    qint64 elapsedMilliseconds = timer.elapsed(); // Время в наносекундах
    qDebug() << elapsedMilliseconds;

    auto builder = std::make_shared<LineChartBuilder>();

    timer.start();
    QChart* chart = builder->GetChart(data);
    elapsedMilliseconds = timer.elapsed(); // Время в наносекундах
    qDebug() << elapsedMilliseconds;

    timer.start();
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    elapsedMilliseconds = timer.elapsed(); // Время в наносекундах
    qDebug() << elapsedMilliseconds;

    timer.start();
    chartView->show();
    elapsedMilliseconds = timer.elapsed(); // Время в наносекундах
    qDebug() << elapsedMilliseconds;
*/

    MainWindow w(ioc);
    w.show();

    return app.exec();
}

