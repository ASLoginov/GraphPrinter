#ifndef SCATTERCHARTBUILDER_H
#define SCATTERCHARTBUILDER_H

#include "IChartBuilder.h"

class ScatterChartBuilder : public IChartBuilder
{
public:
    ScatterChartBuilder();
    virtual QtCharts::QChart *GetChart(std::shared_ptr<QVector<QPair<QDateTime, qreal>>> data);
};

#endif // SCATTERCHARTBUILDER_H
