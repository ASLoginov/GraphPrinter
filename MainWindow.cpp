#include "MainWindow.h"
#include <QBoxLayout>
#include <QSplitter>
#include <QFileSystemModel>
#include <QGraphicsColorizeEffect>
#include <QFileDialog>
#include <QPdfWriter>
#include "DependencyInjection/DataTypeManager.h"
#include "DependencyInjection/ChartTypeManager.h"
#include "DataProcessing/DataProcessing.h"

MainWindow::MainWindow(std::shared_ptr<IOCContainer> ioc, QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* vLayout = new QVBoxLayout(this);

    QHBoxLayout* header = new QHBoxLayout();
    header->setAlignment(Qt::AlignRight);
    vLayout->addLayout(header);

    _styleSelection = new QComboBox();

    auto chartManager = ioc->GetInstance<ChartTypeManager>();
    connect(_styleSelection, &QComboBox::currentTextChanged, chartManager.get(), &ChartTypeManager::SwitchChartType);

    QStringList charts = chartManager->GetChartTypes();
    _styleSelection->addItems(charts);
    header->addWidget(_styleSelection);
    chartManager->SwitchChartType(_styleSelection->currentText());

    _bWBox = new QCheckBox("BW");
    header->addWidget(_bWBox);

    _printButton = new QPushButton("Print");
    header->addWidget(_printButton);

    auto fileModel = new QFileSystemModel(this);
    fileModel->setRootPath("");

    auto dataManager = ioc->GetInstance<DataTypeManager>();
    connect(this, &MainWindow::dataTypeChanged, dataManager.get(), &DataTypeManager::SwitchDataType);

    QStringList filter = dataManager->GetDataTypes();
    for (QString& str : filter) str.prepend("*.");

    fileModel->setNameFilters(filter);
    fileModel->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
    fileModel->setNameFilterDisables(false);

    _filesWindow = new QTreeView();
    _filesWindow->setModel(fileModel);
    _filesWindow->setColumnHidden(1, true);
    _filesWindow->setColumnHidden(3, true);
    QModelIndex startIndex = fileModel->index(QDir::currentPath());
    QModelIndex parentIndex = startIndex.parent();
    while (parentIndex.isValid()) {
        _filesWindow->expand(parentIndex);
        parentIndex = parentIndex.parent();
    }
    _filesWindow->expand(startIndex);
    _filesWindow->scrollTo(startIndex);

    connect(_filesWindow->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, [this, fileModel] (const QItemSelection& selected, const QItemSelection&) {
        QFileInfo file(fileModel->filePath(selected.indexes().first()));
        if (file.isFile()) emit dataTypeChanged(file.suffix());
    });

    connect(_filesWindow->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, [this, fileModel] (const QItemSelection& selected, const QItemSelection&) {
        QFileInfo file(fileModel->filePath(selected.indexes().first()));
        if (file.isFile()) emit fileSelectionChanged(file.absoluteFilePath());
    });

    _chartWindow = new QtCharts::QChartView();
    _chartWindow->setRenderHint(QPainter::Antialiasing);

    auto processing = ioc->GetInstance<DataProcessing>();
    connect(this, &MainWindow::fileSelectionChanged, processing.get(), &DataProcessing::MakeData);
    connect(processing.get(), &DataProcessing::newChart, _chartWindow, [this] (QtCharts::QChart* chart) {
        auto oldChart = _chartWindow->chart();
        _chartWindow->setChart(chart);
        oldChart->deleteLater();
    });
    connect(_styleSelection, &QComboBox::currentTextChanged, processing.get(), &DataProcessing::MakeChart);

    connect(_bWBox, &QCheckBox::stateChanged, _chartWindow, [this] (int state) {
        if (state) {
            auto effect = new QGraphicsColorizeEffect();
            effect->setColor(Qt::black);
            _chartWindow->viewport()->setGraphicsEffect(effect);
        }
        else _chartWindow->viewport()->setGraphicsEffect(nullptr);
    });

    connect(_printButton, &QPushButton::clicked, _chartWindow, [this] {
        QString fileName = QFileDialog::getSaveFileName(this, "Print to PDF", "result.pdf", "PDF (*.pdf)");
        if (fileName.isEmpty()) return;
        QPdfWriter printer(fileName);
        QPainter painter(&printer);
        auto effect = _chartWindow->viewport()->graphicsEffect();
        _chartWindow->chart()->setGraphicsEffect(effect);
        _chartWindow->render(&painter);
        _chartWindow->viewport()->setGraphicsEffect(effect);
        _chartWindow->chart()->setGraphicsEffect(nullptr);
    });

    QSplitter* splitter = new QSplitter();
    vLayout->addWidget(splitter);
    splitter->addWidget(_filesWindow);
    splitter->addWidget(_chartWindow);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);

    setMinimumSize(600, 300);
    _filesWindow->resize(450, 0);
    _filesWindow->setColumnWidth(0, 350);
    resize(1200, 800);
}

MainWindow::~MainWindow() {}
