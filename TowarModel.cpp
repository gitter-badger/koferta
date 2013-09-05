#include "TowarModel.h"
#include "Towar.h"

TowarModel::TowarModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

TowarModel::~TowarModel()
{
    qDeleteAll(m_list);
}

int TowarModel::rowCount(const QModelIndex & /*parent*/) const
{
    return m_list.count() + 1;
}

int TowarModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 0;
}

QVariant TowarModel::data(const QModelIndex &index, int role) const
{
    if(!role == Qt::DisplayRole || index.row() >= m_list.count())
        return QVariant();

    Towar* t = m_list[index.row()];
    switch(index.column())
    {
    case 0:
        return t->kod();
    case 1:
        return t->nazwa();
    case 2:
        return 0;
    }

    return QVariant();
}

QVariant TowarModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return tr("");
}
