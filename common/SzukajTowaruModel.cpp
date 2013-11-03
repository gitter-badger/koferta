#include "SzukajTowaruModel.h"
#include <QtDebug>
#include <QDate>
#include <QSqlTableModel>

const QString SzukajTowaruModel::m_dateFmt = "dd.MM.yyyy";

SzukajTowaruModel::SzukajTowaruModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

bool SzukajTowaruModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    return d(left, 1).toString() < d(right, 1).toString();
}

bool SzukajTowaruModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QDate from = QDate::fromString(sourceModel()->data(sourceModel()->index(sourceRow, 5, sourceParent)).toString(), m_dateFmt);
    QDate to = QDate::fromString(sourceModel()->data(sourceModel()->index(sourceRow, 6, sourceParent)).toString(), m_dateFmt);
    return (QDate::currentDate() > from) && (QDate::currentDate() < to);
}

int SzukajTowaruModel::columnCount()
{
    return 4;
}
/*
Qt::ItemFlags SzukajTowaruModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return 0;

    if(index.column() == 0)
        return Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsEnabled;

    return 0;
}
*/

QVariant SzukajTowaruModel::data(const QModelIndex &index, int role) const
{
    if(!(role == Qt::DisplayRole || role == Qt::EditRole || role == Qt::UserRole) || !index.isValid())
        return QVariant();

    if(role == Qt::UserRole)
        return d(index, 0);

    if(role == Qt::EditRole && index.column() > 0)
        return QVariant();

    int section = index.column();

    switch(section)
    {
    case 0: return d(index, 1);
    case 1: return d(index, 2);
    case 2: return d(index, 3);
    case 3: return d(index, 4).toChar() == 'p' ? tr("szt.") : tr("m.b.");
    }

    qWarning() << "View requested non-existant column, number:" << section;
    return QVariant();
}

QVariant SzukajTowaruModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(!role == Qt::DisplayRole || orientation == Qt::Vertical)
        return QVariant();

    switch(section)
    {
    case 0: return tr("Kod");
    case 1: return tr("Nazwa");
    case 2: return tr("Cena Kat. €");
    case 3: return tr("j/m");
    }

    qWarning() << "View requested non-existant column, number:" << section;
    return QVariant();
}

void SzukajTowaruModel::setFilter(const QString &filter)
{
    QSqlTableModel* t = qobject_cast<QSqlTableModel*>(sourceModel());
    if(t)
        t->setFilter(filter);
}

QVariant SzukajTowaruModel::d(const QModelIndex &index, int col) const
{
    return sourceModel()->data(sourceModel()->index(index.row(), col, index.parent()));
}
