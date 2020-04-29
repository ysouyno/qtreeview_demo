#include "mainwindow.h"
#include <QTreeView>

MainWindow::MainWindow(LogItemModel *model, QWidget *parent)
    : QMainWindow(parent)
    , m_model(model)
{
    QTreeView *view = new QTreeView();
    view->setModel(m_model);
    view->setRootIsDecorated(false);
    setCentralWidget(view);
}

MainWindow::~MainWindow()
{
}

