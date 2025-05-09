#ifndef ICHARTBUILDER_H
#define ICHARTBUILDER_H

#include <QChart>
#include <memory>
#include <QDateTime>

class IChartBuilder
{
public:
    virtual ~IChartBuilder() = default;
    virtual QtCharts::QChart* BuildChart(const QVector<QPair<QDateTime, qreal>>& data) = 0;
};

#endif // ICHARTBUILDER_H
