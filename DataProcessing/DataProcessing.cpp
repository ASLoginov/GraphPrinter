#include "DataProcessing.h"

DataProcessing::DataProcessing(std::shared_ptr<IOCContainer> ioc, QObject *parent) : QObject(parent)
{
    _ioc = ioc;
}

void DataProcessing::MakeData(const QString &filePath)
{
    _data = _ioc->GetInstance<IDataReader>()->ReadData(filePath);
    MakeChart();
}

void DataProcessing::MakeChart()
{
    if (_data.isEmpty()) {
        emit newChart(new QtCharts::QChart());
        return;
    }
    auto chart = _ioc->GetInstance<IChartBuilder>()->BuildChart(_data);
    chart->setParent(this);
    emit newChart(chart);
}
