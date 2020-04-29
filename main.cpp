#include "mainwindow.h"
#include "logitemmodel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LogItemModel log_item_model;
    MainWindow w(&log_item_model);
    w.show();
    return a.exec();
}
