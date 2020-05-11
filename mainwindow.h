#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "logitemmodel.h"
#include "windebugmonitor.h"
#include <QMainWindow>

class LogItemModel;

class MainWindow : public QMainWindow, WinDebugMonitor
{
    Q_OBJECT

public:
    MainWindow(LogItemModel *model, QWidget *parent = nullptr);
    ~MainWindow();

public:
    virtual void OutputWinDebugString(const char *str)
    {
        m_model->add_log(str);
        m_model->update(1);
    };

private:
    LogItemModel *m_model;
};
#endif // MAINWINDOW_H
