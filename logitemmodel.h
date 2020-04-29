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
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

public:
    void add_log(const QString &log);
    void update(int lines);

private:
    std::vector<QString> m_logs;
};

#endif // LOGITEMMODEL_H
