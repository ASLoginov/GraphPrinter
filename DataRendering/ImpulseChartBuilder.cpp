#include "ImpulseChartBuilder.h"

#include <QDateTimeAxis>
#include <QLineSeries>
#include <QValueAxis>
using namespace QtCharts;

ImpulseChartBuilder::ImpulseChartBuilder()
{

}

QChart* ImpulseChartBuilder::BuildChart(const QVector<QPair<QDateTime, qreal>>& data)
{
    if (data.isEmpty()) return new QChart();

    double minY = std::numeric_limits<double>::max();
    double maxY = std::numeric_limits<double>::min();
    for (const auto &pair : data) {
        minY = qMin(minY, pair.second);
        maxY = qMax(maxY, pair.second);
    }

    QLineSeries* series = new QLineSeries();
    series->setPen(QPen(QColor(Qt::darkCyan), 3));

    for (const auto& pair : data) {
        const qreal x = pair.first.toMSecsSinceEpoch();
        const qreal y = pair.second;

        series->append(x, minY - 100);
        series->append(x, y);
        series->append(x, minY - 100);
    }

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::NoAnimation);
    //chart->setTitle("Импульсный график");

    QDateTimeAxis* axisX = new QDateTimeAxis();
    axisX->setFormat("dd.MM.yyyy HH:mm");
    //axisX->setTitleText("Дата");
    axisX->setTickCount(8);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    axisX->setRange(data.first().first, data.last().first);

    QValueAxis* axisY = new QValueAxis();
    //axisY->setTitleText("Уровень");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    axisY->setRange(minY, maxY);

    return chart;
}
