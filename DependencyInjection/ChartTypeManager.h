#ifndef CHARTTYPEMANAGER_H
#define CHARTTYPEMANAGER_H

#include <QObject>
#include <QHash>
#include <QString>
#include "DataRendering/IChartBuilder.h"
#include "IOC_Contaner.h"

class ChartTypeManager : public QObject
{
    Q_OBJECT
    std::shared_ptr<IOCContainer> _ioc;
    QHash<QString, std::function<std::shared_ptr<IChartBuilder>()>> _chartTypes;

public:
    ChartTypeManager(std::shared_ptr<IOCContainer> ioc, QObject *parent = nullptr);
    void RemoveChartType(const QString& type);
    QStringList GetChartTypes();

    template<class TBuilder, class ...TArgs>
    void AddChartType(const QString& type)
    {
        _chartTypes.insert(type, [this]() { return std::make_shared<TBuilder>(_ioc->GetInstance<TArgs>()...); });
    }

    void SwitchChartType(const QString& type);
};

#endif // CHARTTYPEMANAGER_H
