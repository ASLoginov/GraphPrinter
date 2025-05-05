#ifndef LINECHARTBUILDER_H
#define LINECHARTBUILDER_H

#include "IChartBuilder.h"

class LineChartBuilder : public IChartBuilder
{
public:
    LineChartBuilder();
    QtCharts::QChart* GetChart(std::shared_ptr<QVector<QPair<QDateTime, qreal>>> data);
};

#endif // LINECHARTBUILDER_H
