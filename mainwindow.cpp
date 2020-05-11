#include "mainwindow.h"
#include <QTreeView>
#include <QTimer>

MainWindow::MainWindow(LogItemModel *model, QWidget *parent)
    : QMainWindow(parent)
    , m_model(model)
{
    QTreeView *view = new QTreeView();
    view->setModel(m_model);
    view->setRootIsDecorated(false);
    setCentralWidget(view);

    /*auto test_add_log = [this] {
        m_model->add_log("msg");
        m_model->update(1);
    };

    QTimer *timer = new QTimer();
    timer->setInterval(1000);
    timer->setSingleShot(false);
    QObject::connect(timer, &QTimer::timeout, test_add_log);
    timer->start();*/
}

MainWindow::~MainWindow()
{
}

