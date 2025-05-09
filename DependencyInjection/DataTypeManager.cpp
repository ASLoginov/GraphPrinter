#include "DataTypeManager.h"

DataTypeManager::DataTypeManager(std::shared_ptr<IOCContainer> ioc, QObject *parent) : QObject(parent)
{
    _ioc = ioc;
}

void DataTypeManager::RemoveDataType(const QString& type)
{
    _dataTypes.remove(type);
}

QStringList DataTypeManager::GetDataTypes()
{
    return _dataTypes.keys();
}

void DataTypeManager::SwitchDataType(const QString& type)
{
    _ioc->RegisterFunctor<IDataReader>(_dataTypes[type]);
}
