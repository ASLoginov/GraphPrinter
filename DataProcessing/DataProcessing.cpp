#include "DataProcessing.h"

DataProcessing::DataProcessing(std::shared_ptr<IOCContainer> ioc, QObject *parent) : QObject(parent)
{
    _ioc = ioc;
}

void DataProcessing::MakeData(const QString &filePath)
{
    auto reader = _ioc->GetInstance<IDataReader>();
    _data = reader->ReadData(filePath);
    MakeChart();
}

void DataProcessing::MakeChart()
{
    if (_data.isEmpty()) return;
    auto builder = _ioc->GetInstance<IChartBuilder>();
    auto oldChart = _chart;
    _chart = builder->BuildChart(_data);
    _chart->setParent(this);
    emit newChart(_chart);
    if (oldChart) oldChart->deleteLater();
}
