#include "logitemmodel.h"

LogItemModel::LogItemModel()
{

}

int LogItemModel::rowCount(const QModelIndex &parent) const
{
    return 2;
}

int LogItemModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant LogItemModel::data(const QModelIndex &index, int role) const
{
    return {};
}
