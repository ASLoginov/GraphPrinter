#include "MainWindow.h"
#include <QBoxLayout>
#include <QSplitter>
#include <QFileSystemModel>
#include <QGraphicsColorizeEffect>
#include "DependencyInjection/DataTypeManager.h"
#include "DependencyInjection/ChartTypeManager.h"
#include "DataProcessing/DataProcessing.h"

MainWindow::MainWindow(std::shared_ptr<IOCContainer> ioc, QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* vLayout = new QVBoxLayout(this);

    QHBoxLayout* header = new QHBoxLayout();
    header->setAlignment(Qt::AlignRight);
    vLayout->addLayout(header);

    auto styleSelection = new QComboBox();

    auto chartManager = ioc->GetInstance<ChartTypeManager>();
    connect(styleSelection, &QComboBox::currentTextChanged, chartManager.get(), &ChartTypeManager::SwitchChartType);

    QStringList charts = chartManager->GetChartTypes();
    styleSelection->addItems(charts);
    header->addWidget(styleSelection);
    chartManager->SwitchChartType(styleSelection->currentText());

    auto bWBox = new QCheckBox("BW");
    header->addWidget(bWBox);

    auto printButton = new QPushButton("Print");
    header->addWidget(printButton);

    auto fileModel = new QFileSystemModel(this);
    fileModel->setRootPath("");

    auto dataManager = ioc->GetInstance<DataTypeManager>();
    connect(this, &MainWindow::dataTypeChanged, dataManager.get(), &DataTypeManager::SwitchDataType);

    QStringList filter = dataManager->GetDataTypes();
    for (QString& str : filter) str.prepend("*.");

    fileModel->setNameFilters(filter);
    fileModel->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
    fileModel->setNameFilterDisables(false);

    auto filesWindow = new QTreeView();
    filesWindow->setModel(fileModel);
    filesWindow->setColumnHidden(1, true);
    filesWindow->setColumnHidden(3, true);
    QModelIndex startIndex = fileModel->index(QDir::currentPath());
    QModelIndex parentIndex = startIndex.parent();
    while (parentIndex.isValid()) {
        filesWindow->expand(parentIndex);
        parentIndex = parentIndex.parent();
    }
    filesWindow->expand(startIndex);
    filesWindow->scrollTo(startIndex);

    connect(filesWindow->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, [this, fileModel] (const QItemSelection& selected, const QItemSelection&) {
        QFileInfo file(fileModel->filePath(selected.indexes().first()));
        if (file.isFile()) emit dataTypeChanged(file.suffix());
    });

    connect(filesWindow->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, [this, fileModel] (const QItemSelection& selected, const QItemSelection&) {
        QFileInfo file(fileModel->filePath(selected.indexes().first()));
        if (file.isFile()) emit fileSelectionChanged(file.absoluteFilePath());
    });

    auto chartWindow = new QtCharts::QChartView();
    chartWindow->setRenderHint(QPainter::Antialiasing);

    auto processing = ioc->GetInstance<DataProcessing>();
    connect(this, &MainWindow::fileSelectionChanged, processing.get(), &DataProcessing::MakeData);
    connect(processing.get(), &DataProcessing::newChart, chartWindow, &QtCharts::QChartView::setChart);
    connect(styleSelection, &QComboBox::currentTextChanged, processing.get(), &DataProcessing::MakeChart);

    connect(bWBox, &QCheckBox::stateChanged, this, [chartWindow] (int state) {
        if (state) {
            auto effect = new QGraphicsColorizeEffect();
            effect->setColor(Qt::black);
            chartWindow->viewport()->setGraphicsEffect(effect);
        }
        else chartWindow->viewport()->setGraphicsEffect(nullptr);
    });

    QSplitter* splitter = new QSplitter();
    vLayout->addWidget(splitter);
    splitter->addWidget(filesWindow);
    splitter->addWidget(chartWindow);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);

    setMinimumSize(600, 300);
    filesWindow->resize(450, 0);
    filesWindow->setColumnWidth(0, 350);
    resize(1200, 800);
}

MainWindow::~MainWindow() {}
