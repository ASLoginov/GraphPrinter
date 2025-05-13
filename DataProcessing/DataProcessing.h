#ifndef DATAPROCESSING_H
#define DATAPROCESSING_H

#include "DataReading/IDataReader.h"
#include "DataRendering/IChartBuilder.h"
#include "DependencyInjection/IOC_Contaner.h"

class DataProcessing : public QObject
{
    Q_OBJECT

    QVector<QPair<QDateTime, qreal>> _data;
    std::shared_ptr<IOCContainer> _ioc;

public:
    DataProcessing(std::shared_ptr<IOCContainer> ioc, QObject* parent = nullptr);
    void MakeData(const QString& filePath);
    void MakeChart();

signals:
    void newChart(QtCharts::QChart* chart);
};

#endif // DATAPROCESSING_H
