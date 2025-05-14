QT       += core gui sql charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DataProcessing/DataProcessing.cpp \
    DataReading/DateParsing/AggregatedDTParser.cpp \
    DataReading/DateParsing/DateAndMinutesParser.cpp \
    DataReading/DateParsing/MultiformatDTParser.cpp \
    DataReading/JsonDataReader.cpp \
    DataReading/SqliteDataReader.cpp \
    DataRendering/ImpulseChartBuilder.cpp \
    DataRendering/LineChartBuilder.cpp \
    DataRendering/ScatterChartBuilder.cpp \
    DependencyInjection/ChartTypeManager.cpp \
    DependencyInjection/DataTypeManager.cpp \
    DependencyInjection/IOC_Container.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    DataProcessing/DataProcessing.h \
    DataReading/DateParsing/AggregatedDTParser.h \
    DataReading/DateParsing/DateAndMinutesParser.h \
    DataReading/DateParsing/IDateTimeParser.h \
    DataReading/DateParsing/MultiformatDTParser.h \
    DataReading/IDataReader.h \
    DataReading/JsonDataReader.h \
    DataReading/SqliteDataReader.h \
    DataRendering/IChartBuilder.h \
    DataRendering/ImpulseChartBuilder.h \
    DataRendering/LineChartBuilder.h \
    DataRendering/ScatterChartBuilder.h \
    DependencyInjection/ChartTypeManager.h \
    DependencyInjection/DataTypeManager.h \
    DependencyInjection/IOC_Contaner.h \
    MainWindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
