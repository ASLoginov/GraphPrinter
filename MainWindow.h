#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "DependencyInjection/IOC_Contaner.h"
#include <QWidget>
#include <QTreeView>
#include <QChartView>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>

class MainWindow : public QWidget
{
    Q_OBJECT

    QTreeView* _filesWindow;
    QtCharts::QChartView* _chartWindow;
    QComboBox* _styleSelection;
    QPushButton* _printButton;
    QCheckBox* _blackAndWhiteBox;

public:
    MainWindow(std::shared_ptr<IOCContainer> ioc, QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
