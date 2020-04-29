#ifndef LOGITEMMODEL_H
#define LOGITEMMODEL_H

#include <QAbstractTableModel>

class LogItemModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    LogItemModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};

#endif // LOGITEMMODEL_H
