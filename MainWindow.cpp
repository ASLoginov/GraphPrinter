#include "MainWindow.h"
#include <QBoxLayout>
#include <QSplitter>
#include <QFileSystemModel>
#include "DataReading/DataTypeManager.h"
#include "DataRendering/IChartBuilder.h"

MainWindow::MainWindow(std::shared_ptr<IOCContainer> ioc, QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* vLayout = new QVBoxLayout(this);

    QHBoxLayout* header = new QHBoxLayout();
    header->setAlignment(Qt::AlignRight);
    vLayout->addLayout(header);

    _styleSelection = new QComboBox();
    header->addWidget(_styleSelection);

    _blackAndWhiteBox = new QCheckBox("B&W");
    header->addWidget(_blackAndWhiteBox);

    _printButton = new QPushButton("Print");
    header->addWidget(_printButton);

    QFileSystemModel* fileModel = new QFileSystemModel(this);
    fileModel->setRootPath("");

    auto dataManager = ioc->GetInstance<DataTypeManager>();
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
            dataManager.get(), [=] (const QItemSelection& selected, const QItemSelection& ) {
        dataManager->SwitchDataType(QFileInfo(fileModel->filePath(selected.indexes().first())).suffix());
    });

    _chartWindow = new QtCharts::QChartView();
    _chartWindow->setRenderHint(QPainter::Antialiasing);

    connect(_filesWindow->selectionModel(), &QItemSelectionModel::selectionChanged,
            _chartWindow, [=] (const QItemSelection& selected, const QItemSelection& ) {
        QString file = fileModel->filePath(selected.indexes().first());
        auto data = ioc->GetInstance<IDataReader>()->ReadData(file);
        _chartWindow->setChart(ioc->GetInstance<IChartBuilder>()->GetChart(data));
    });

    QSplitter* splitter = new QSplitter();
    vLayout->addWidget(splitter);
    splitter->addWidget(_filesWindow);
    splitter->addWidget(_chartWindow);

    setMinimumSize(600, 300);
    _chartWindow->resize(400, 0);
    _filesWindow->resize(400, 0);
    _filesWindow->setColumnWidth(0, 350);
    resize(1000, 600);
}

MainWindow::~MainWindow() {}
