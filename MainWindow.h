#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "DependencyInjection/IOC_Contaner.h"
#include <QWidget>
#include <QTreeView>
#include <QChartView>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <qstackedwidget.h>

class MainWindow : public QWidget
{
    Q_OBJECT

    QTreeView* _filesWindow;
    QtCharts::QChartView* _chartWindow;
    QComboBox* _styleSelection;
    QPushButton* _printButton;
    QCheckBox* _bWBox;
    QLabel* _invalidDataMessage;
    QStackedWidget* _stacked;

public:
    MainWindow(std::shared_ptr<IOCContainer> ioc, QWidget* parent = nullptr);
    ~MainWindow();

signals:
    void dataTypeChanged(const QString& type);
    void fileSelectionChanged(const QString& filePath);
};
#endif // MAINWINDOW_H
