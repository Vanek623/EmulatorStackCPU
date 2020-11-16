#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDir>
#include <QLabel>
#include <QMainWindow>
#include <QTextStream>
#include <QFileDialog>
#include <QListWidget>
#include <QMessageBox>

#include <QDebug>

#include "cpu.h"
#include "builder.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

    QVector<QLabel*> flagsLabels;

    CPU cpu;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void compile();
    void save();
    void load();
    void next();
    void run();
    void reset();

private:
    void setupConnections();
    void initFlags();

    void updateCPUInfo();

    void updateDataStack();
    void updateRevertStack();
    void updateFlags();
    void updateMemory();
    void updatePC();

    QString toAnothSys(const int num, const int numSys, const int size) const;
    void showStackData(Stack *stack, QListWidget *stackWidget);

};

#endif // MAINWINDOW_H
