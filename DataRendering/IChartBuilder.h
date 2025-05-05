#ifndef ICHARTBUILDER_H
#define ICHARTBUILDER_H

#include <QChart>
#include <memory>
#include <QDateTime>

class IChartBuilder
{
public:
    virtual ~IChartBuilder() = default;
    virtual QtCharts::QChart* GetChart(std::shared_ptr<QVector<QPair<QDateTime, qreal>>> data) = 0;
};

#endif // ICHARTBUILDER_H
