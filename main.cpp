#include <QApplication>

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

    auto reader = ioc->GetInstance<IDataReader>();

    QElapsedTimer timer;

    timer.start(); // Запуск таймера
    auto data = reader->ReadData("C:/Qt projects/GraphPrinter/InputData/TEMPERATURE_NOVOSIB.sqlite");
    qint64 elapsedMilliseconds = timer.elapsed(); // Время в наносекундах
    qDebug() << elapsedMilliseconds;

//    QLineSeries *series = new QLineSeries();
//    series->setPen(QPen(Qt::darkGreen, 1));

//    // Собираем данные и добавляем разрывы
//    for (const auto &pair : *data) {
//        const qreal x = pair.first.toMSecsSinceEpoch();
//        const qreal y = pair.second;

//        // Вертикальная линия
//        series->append(x, 0);
//        series->append(x, y);

//        // Двойной разрыв
//        series->append(qQNaN(), qQNaN());
//        series->append(qQNaN(), qQNaN());
//    }

//    QChart *chart = new QChart();
//    chart->addSeries(series);
//    chart->legend()->hide();
//    chart->setTitle("Вертикальные линии с разрывами");

//    // Ось X (время)
//    QDateTimeAxis *axisX = new QDateTimeAxis();
//    axisX->setFormat("dd.MM HH:mm");
//    axisX->setTitleText("Дата");
//    chart->addAxis(axisX, Qt::AlignBottom);
//    series->attachAxis(axisX);

//    // Ось Y (значения)
//    QValueAxis *axisY = new QValueAxis();
//    axisY->setTitleText("Уровень");
//    chart->addAxis(axisY, Qt::AlignLeft);
//    series->attachAxis(axisY);

//    // Автонастройка диапазона Y
//    axisY->applyNiceNumbers();

//    QChartView *chartView = new QChartView(chart);
//    chartView->setRenderHint(QPainter::Antialiasing);

//    chart->setAnimationOptions(QChart::NoAnimation);

    auto builder = std::make_shared<LineChartBuilder>();
    QChartView* chartView = new QChartView(builder->GetChart(data));
    chartView->setRenderHint(QPainter::Antialiasing);

    chartView->show();

    return app.exec();
}

