#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->addWireBtn, &QPushButton::clicked, this, [this]{ addElement(1); });
    connect(ui->addConnectionBtn, &QPushButton::clicked, this, [this]{ addElement(2); });
    connect(ui->addGNDBtn, &QPushButton::clicked, this, [this]{ addElement(3); });
    connect(ui->addNetBtn, &QPushButton::clicked, this, [this]{ addElement(4); });
    connect(ui->addAndBtn, &QPushButton::clicked, this, [this]{ addElement(5); });
    connect(ui->addNandBtn, &QPushButton::clicked, this, [this]{ addElement(6); });
    connect(ui->addOrBtn, &QPushButton::clicked, this, [this]{ addElement(7); });
    connect(ui->addNorBtn, &QPushButton::clicked, this, [this]{ addElement(8); });
    connect(ui->addNotBtn, &QPushButton::clicked, this, [this]{ addElement(9); });
    connect(ui->addXorBtn, &QPushButton::clicked, this, [this]{ addElement(10); });
    connect(ui->addResistorBtn, &QPushButton::clicked, this, [this]{ addElement(11); });
    connect(ui->addCapacitorBtn, &QPushButton::clicked, this, [this]{ addElement(12); });
    connect(ui->addLogicBtn, &QPushButton::clicked, this, [this]{ addElement(13); });

    createActions();
    createMenus();

    savedLabel = new QLabel(this);
    //actionLabel = new QLabel(this);
    savedLabel->setText("[]");
    //actionLabel->setText("...");
    statusBar()->addWidget(savedLabel);
    //statusBar()->addWidget(actionLabel);

    chart = new GraphicsView(this);
    ui->graphicsLayout->addWidget(chart);

    connect(chart, &GraphicsView::savedStateChanged, this, [this]{ updateSavedLabel(); });
}

MainWindow::~MainWindow()
{
    delete chart;
    delete savedLabel;
    delete ui;
}

void MainWindow::openFile(const QString &path)
{
    if (!askForSave())
        return;
    if (!path.isEmpty())
        chart->open(path);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (!askForSave())
        event->ignore();
    else
        QMainWindow::closeEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_R)
        chart->rotate();
}

void MainWindow::addElement(int id)
{
    chart->addNode(id);

}

void MainWindow::createCircuit()
{
    if (!askForSave())
        return;
    chart->createNewChart();
}

void MainWindow::openCircuit()
{
    if (!askForSave())
        return;
    path = QFileDialog::getOpenFileName(this, "Open circuit",
                                        QCoreApplication::applicationDirPath(),
                                        "Circuit file (*.circ)" );
    if (!path.isEmpty())
        chart->open(path);
}

void MainWindow::exportCircuit()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save image",
                                                    QCoreApplication::applicationDirPath(),
                                                    "BMP Files (*.bmp);;JPEG (*.JPEG);;PNG (*.png)" );
    if (!fileName.isEmpty()) {
        chart->removeGrid();
        QPixmap pixMap = chart->grab();
        pixMap.save(fileName);
        chart->addGrid();
    }
}

void MainWindow::saveCircuit()
{
    if (!chart->getPath().isEmpty())
        chart->save();
    else
        saveCircuitAs();
}

void MainWindow::saveCircuitAs()
{
    path = QFileDialog::getSaveFileName(this, "Save circuit",
                                        QCoreApplication::applicationDirPath(),
                                        "Circuit file (*.circ)" );
    if (!path.isEmpty())
        chart->saveAs(path);
}

void MainWindow::exit()
{
    if (!askForSave())
        return;
    QApplication::exit();
}

void MainWindow::createActions()
{
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcut(QKeySequence::New);
    newAct->setStatusTip(tr("Crate new circuit"));
    connect(newAct, &QAction::triggered, this, &MainWindow::createCircuit);

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcut(QKeySequence::Open);
    openAct->setStatusTip(tr("Open circuit from a file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::openCircuit);

    exportAct = new QAction(tr("&Export..."), this);
    exportAct->setShortcut(QKeySequence("Ctrl+E"));
    exportAct->setStatusTip(tr("Export circuit as image"));
    connect(exportAct, &QAction::triggered, this, &MainWindow::exportCircuit);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save circuit to a file"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveCircuit);

    saveAsAct = new QAction(tr("&Save as..."), this);
    saveAsAct->setShortcut(QKeySequence("Ctrl+Shift+S"));
    saveAsAct->setStatusTip(tr("Save circuit to a file"));
    connect(saveAsAct, &QAction::triggered, this, &MainWindow::saveCircuitAs);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addAction(exportAct);
}

void MainWindow::updateSavedLabel()
{
    QString text("[");
    text.append(chart->getPath());
    text.append("]");
    if (!chart->isSaved())
        text.append("*");
    savedLabel->setText(text);
}

bool MainWindow::askForSave()
{
    if (!chart->isSaved()) {
        QMessageBox msgBox;
        msgBox.setText("The document has unsaved changes");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard |
                                  QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
          case QMessageBox::Save:
              saveCircuit();
              return true;
              break;
          case QMessageBox::Cancel:
              return false;
              break;
          default:
              return true;
              break;
        }
    }
    return true;
}
