#include "LineChartBuilder.h"

#include <QDateTimeAxis>
#include <QLineSeries>
#include <QValueAxis>
using namespace QtCharts;

LineChartBuilder::LineChartBuilder()
{

}

QtCharts::QChart *LineChartBuilder::GetChart(std::shared_ptr<QVector<QPair<QDateTime, qreal> > > data)
{
    double minY = std::numeric_limits<double>::max();
    double maxY = std::numeric_limits<double>::min();
    if (!data->isEmpty()) {
        for (const auto &pair : *data) {
            minY = qMin(minY, pair.second);
            maxY = qMax(maxY, pair.second);
        }
    }

    QLineSeries* series = new QLineSeries();
    series->setPen(QPen(QColor("blue"), 1));

    for (const auto& pair : *data) {
        const qreal x = pair.first.toMSecsSinceEpoch();
        const qreal y = pair.second;
        series->append(x, y);
    }

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::NoAnimation);
    //chart->setTitle("Линейный график");

    QDateTimeAxis* axisX = new QDateTimeAxis();
    axisX->setFormat("dd.MM.yyyy HH:mm");
    //axisX->setTitleText("Дата");
    axisX->setTickCount(8);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    axisX->setRange(data->first().first, data->last().first);

    QValueAxis* axisY = new QValueAxis();
    //axisY->setTitleText("Уровень");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    axisY->setRange(minY, maxY);

    return chart;
}
