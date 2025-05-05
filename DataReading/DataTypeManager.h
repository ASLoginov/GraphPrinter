#ifndef DATATYPEMANAGER_H
#define DATATYPEMANAGER_H

#include <QObject>
#include <QHash>
#include <QString>
#include "IDataReader.h"
#include "DependencyInjection/IOC_Contaner.h"
#include "DateParsing/IDateTimeParser.h"

class DataTypeManager
{
    Q_OBJECT
    std::shared_ptr<IOCContainer> _ioc;
    QHash<QString, std::function<std::shared_ptr<IDataReader>(std::shared_ptr<IOCContainer>)>> _dataTypes;

public:
    DataTypeManager(std::shared_ptr<IOCContainer> ioc);
    void AddType(const QString& type, const std::function<std::shared_ptr<IDataReader>(std::shared_ptr<IOCContainer>)>& functor);
    void RemoveType(const QString& type);
    QStringList GetTypes();

public slots:
    void SwitchType(const QString& type);
};

#endif // DATATYPEMANAGER_H
