#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "logitemmodel.h"
#include <QMainWindow>

class LogItemModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(LogItemModel *model, QWidget *parent = nullptr);
    ~MainWindow();

private:
    LogItemModel *m_model;
};
#endif // MAINWINDOW_H
