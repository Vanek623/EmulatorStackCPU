#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDir>
#include <QLabel>
#include <QMainWindow>
#include <QTextStream>
#include <QFileDialog>

#include <QDebug>

#include "cpu.h"

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

};

#endif // MAINWINDOW_H
