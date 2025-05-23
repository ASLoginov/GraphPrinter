#ifndef DATATYPEMANAGER_H
#define DATATYPEMANAGER_H

#include <QObject>
#include <QHash>
#include <QString>
#include "DataReading/IDataReader.h"
#include "IOC_Contaner.h"

class DataTypeManager : public QObject
{
    Q_OBJECT
    std::shared_ptr<IOCContainer> _ioc;
    QHash<QString, std::function<std::shared_ptr<IDataReader>()>> _dataTypes;

public:
    DataTypeManager(std::shared_ptr<IOCContainer> ioc, QObject *parent = nullptr);
    void RemoveDataType(const QString& type);
    QStringList GetDataTypes();

    template<class TReader, class ...TArgs>
    void AddDataType(const QString& type)
    {
        _dataTypes.insert(type, [this]() { return std::make_shared<TReader>(_ioc->GetInstance<TArgs>()...); });
    }

    void SwitchDataType(const QString& type);
};

#endif // DATATYPEMANAGER_H
