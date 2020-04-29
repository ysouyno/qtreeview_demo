#include "logitemmodel.h"

LogItemModel::LogItemModel()
{

}

int LogItemModel::rowCount(const QModelIndex &parent) const
{
    return m_logs.size();
}

int LogItemModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant LogItemModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return m_logs.at(index.row());
    }

    return {};
}

QVariant LogItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return "Log";
    }

    return {};
}

void LogItemModel::add_log(const QString &log)
{
    m_logs.push_back(log);
}

void LogItemModel::update(int lines)
{
    beginInsertRows({}, m_logs.size(), m_logs.size() + lines);
    endInsertRows();
}
