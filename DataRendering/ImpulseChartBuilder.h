#ifndef IMPULSECHARTBUILDER_H
#define IMPULSECHARTBUILDER_H

#include "IChartBuilder.h"

class ImpulseChartBuilder : public IChartBuilder
{
public:
    ImpulseChartBuilder();
    QtCharts::QChart* GetChart(std::shared_ptr<QVector<QPair<QDateTime, qreal>>> data);
};

#endif // IMPULSECHARTBUILDER_H
