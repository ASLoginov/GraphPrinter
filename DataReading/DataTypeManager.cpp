#include "DataTypeManager.h"
#include "SqliteDataReader.h"

DataTypeManager::DataTypeManager(std::shared_ptr<IOCContainer> ioc)
{
    _ioc = ioc;
}

void DataTypeManager::AddType(const QString& type, const std::function<std::shared_ptr<IDataReader>(std::shared_ptr<IOCContainer>)>& functor)
{
    _dataTypes.insert(type, functor);
}

void DataTypeManager::RemoveType(const QString& type)
{
    _dataTypes.remove(type);
}

QStringList DataTypeManager::GetTypes()
{
    return _dataTypes.keys();
}

void DataTypeManager::SwitchType(const QString& type)
{
    _ioc->RegisterFunctor<IDataReader, IOCContainer>(_dataTypes[type]);
}
