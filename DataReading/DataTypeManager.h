#ifndef DATATYPEMANAGER_H
#define DATATYPEMANAGER_H

#include <QObject>
#include <QHash>
#include <QString>
#include "IDataReader.h"
#include "DependencyInjection/IOC_Contaner.h"
#include "DateParsing/IDateTimeParser.h"

class DataTypeManager : public QObject
{
    Q_OBJECT
    std::shared_ptr<IOCContainer> _ioc;
    QHash<QString, std::function<std::shared_ptr<IDataReader>()>> _dataTypes;
    //void AddFunctor(const QString& type, const std::function<std::shared_ptr<IDataReader>()>& functor);

public:
    DataTypeManager(std::shared_ptr<IOCContainer> ioc);
    void RemoveDataType(const QString& type);
    QStringList GetTypes();

    template<class TReader, class ...TArgs>
    void AddDataType(const QString& type)
    {
        _dataTypes.insert(type, [this] () { return std::make_shared<TReader>(_ioc->GetInstance<TArgs>()...); });
    }

public slots:
    void SwitchDataType(const QString& type);
};

#endif // DATATYPEMANAGER_H
