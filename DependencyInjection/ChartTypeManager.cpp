#include "ChartTypeManager.h"

ChartTypeManager::ChartTypeManager(std::shared_ptr<IOCContainer> ioc, QObject *parent) : QObject(parent)
{
    _ioc = ioc;
}

void ChartTypeManager::RemoveChartType(const QString &type)
{
    _chartTypes.remove(type);
}

QStringList ChartTypeManager::GetChartTypes()
{
    return _chartTypes.keys();
}

void ChartTypeManager::SwitchChartType(const QString &type)
{
    _ioc->RegisterFunctor<IChartBuilder>(_chartTypes[type]);
}
