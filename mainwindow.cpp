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
    Builder builder;

    int compileResult = builder.compile(ui->textEdit->toPlainText());
    if(compileResult == -1)
    {
        QVector<Command> *commands = builder.getCompiledProgramm();
        if(commands->size() > RAM_COM_CAPACITY)
        {
            QString compileResultStr = "Размер программы слишком большой!";
            QMessageBox::warning(this, "Ошибка", compileResultStr);
            return;
        }
        else
        {
            QString compileResultStr = "Компиляция прошла успешно!";
            QMessageBox::information(this, "Результат компиляции", compileResultStr);

            cpu.init(commands);
            updateMemory();
        }
    }
    else
    {
        QString compileResultStr = "Компиляция прошла неудачно!\nОшибка в "
                              + QString::number(compileResult + 1) + " строке...";

        QMessageBox::warning(this, "Результат компиляции", compileResultStr);
    }

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
    updateCPUInfo();
}

void MainWindow::setupConnections()
{
    connect(ui->actionCompile, SIGNAL(triggered()), this, SLOT(compile()));
    connect(ui->actionNext, SIGNAL(triggered()), this, SLOT(next()));
    connect(ui->actionRun, SIGNAL(triggered()), this, SLOT(run()));
    connect(ui->actionReset, SIGNAL(triggered()), this, SLOT(reset()));

    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionLoad, SIGNAL(triggered()), this, SLOT(load()));
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
    updatePC();
}

void MainWindow::updateDataStack()
{
    showStackData(cpu.getStackData(), ui->dataList);
}

void MainWindow::updateRevertStack()
{
    showStackData(cpu.getStackRevert(), ui->revertList);
}

void MainWindow::updateFlags()
{
    quint8 mask = 1;
    quint8 flags = cpu.getFlags();

    for(int i=0; i<flagsLabels.size(); i++)
    {
        flagsLabels[i]->setText(QString::number( (flags & mask) >> i ));
        mask = static_cast<quint8>(mask << 1);
    }
}

void MainWindow::updateMemory()
{
    QListWidget *memoryWidget = ui->memoryList;
    memoryWidget->clear();

    QVector<quint32> *memory = cpu.getRAM()->getData();


    for(int i=0; i<memory->size(); i++)
    {
        quint32 word = memory->at(i);
        QString out = toAnothSys(i, 16, 2) + QString::fromUtf8(": ") +
                      toAnothSys(word >> 16, 16, 4) + QString::fromUtf8(" ") +
                      toAnothSys(word & 0xFFFF, 16, 4);

        memoryWidget->addItem(out);
    }
}

void MainWindow::updatePC()
{
    ui->pcv->setText(toAnothSys(cpu.getPC(), 16, 2));
}

QString MainWindow::toAnothSys(const int num, const int numSys, const int size) const
{
    return QString("%1").arg(QString::number(num, numSys), size, QLatin1Char('0')).toUpper();
}

void MainWindow::showStackData(Stack *stack, QListWidget *stackWidget)
{
    stackWidget->clear();

    if(!stack->isEmpty())
    {
        QVector<quint16> *stackData = stack->getData();

        quint8 begin = stack->getPointer();

        for(int i=begin; i> -1; i--)
        {
            QString out = toAnothSys(begin - i, 16, 2) + QString::fromUtf8(": ") +
                          toAnothSys(stackData->at(i), 16, 4);

            stackWidget->addItem(out);
        }
    }
}
