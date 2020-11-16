#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupConnections();

    initFlags();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::compile()
{

}

void MainWindow::save()
{
    QDir dir = QDir::current();
    dir.cdUp();

    QString path = dir.absolutePath() + QString::fromUtf8("/EmulatorStackCPU/Programs");
    path = QFileDialog::getOpenFileName(nullptr, QString(), path);

    QFile file(path);

    QTextStream stream(&file);

    if(file.open(QIODevice::WriteOnly))
    {
        stream << ui->textEdit->toPlainText();
    }

    file.close();
}

void MainWindow::load()
{
    QDir dir = QDir::current();
    dir.cdUp();

    QString path = dir.absolutePath() + QString::fromUtf8("/EmulatorStackCPU/Programs");
    path = QFileDialog::getOpenFileName(nullptr, QString(), path);

    QFile file(path);

    QTextStream stream(&file);

    if(file.open(QIODevice::ReadOnly))
    {
        ui->textEdit->setText(stream.readAll());
    }

    file.close();
}

void MainWindow::next()
{
    if(cpu.work())
    {
        updateCPUInfo();
    }
}

void MainWindow::run()
{
    while (cpu.work());

    updateCPUInfo();
}

void MainWindow::reset()
{
    cpu.reset();
}

void MainWindow::setupConnections()
{
    connect(ui->menuCompile, SIGNAL(triggered(QAction*)), this, SLOT(compile()));
    connect(ui->menuNext, SIGNAL(triggered(QAction*)), this, SLOT(next()));
    connect(ui->menuRun, SIGNAL(triggered(QAction*)), this, SLOT(run()));
    connect(ui->menuReset, SIGNAL(triggered(QAction*)), this, SLOT(reset()));

    connect(ui->menuSave, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->menuLoad, SIGNAL(triggered()), this, SLOT(load()));
}

void MainWindow::initFlags()
{
    flagsLabels.append(ui->nv);
    flagsLabels.append(ui->zv);
    flagsLabels.append(ui->cv);
    flagsLabels.append(ui->sev);
    flagsLabels.append(ui->sov);
    flagsLabels.append(ui->sofv);
}

void MainWindow::updateCPUInfo()
{
    updateDataStack();
    updateRevertStack();
    updateMemory();
    updateFlags();

}

void MainWindow::updateDataStack()
{

}

void MainWindow::updateRevertStack()
{

}

void MainWindow::updateFlags()
{

}

void MainWindow::updateMemory()
{

}

void MainWindow::updatePC()
{

}
