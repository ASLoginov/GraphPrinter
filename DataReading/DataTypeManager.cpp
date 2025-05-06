#include "DataTypeManager.h"
#include "SqliteDataReader.h"

DataTypeManager::DataTypeManager(std::shared_ptr<IOCContainer> ioc) : QObject()
{
    _ioc = ioc;
}

//void DataTypeManager::AddFunctor(const QString& type, const std::function<std::shared_ptr<IDataReader>()>& functor)
//{
//    _dataTypes.insert(type, functor);
//}

void DataTypeManager::RemoveDataType(const QString& type)
{
    _dataTypes.remove(type);
}

QStringList DataTypeManager::GetTypes()
{
    return _dataTypes.keys();
}

void DataTypeManager::SwitchDataType(const QString& type)
{
    _ioc->RegisterFunctor<IDataReader>(_dataTypes[type]);
}
