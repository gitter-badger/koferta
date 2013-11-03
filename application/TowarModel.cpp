#include "TowarModel.h"
#include "Merchandise.h"
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlRecord>
#include "LocalDatabase.h"

TowarModel::TowarModel(QObject *parent) :
    QAbstractTableModel(parent), m_pln(false), m_kurs(1)
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
    return (m_pln ? 9 : 8);
}

bool TowarModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role == Qt::EditRole && isRabat(index))
    {
        Merchandise* t = static_cast<Merchandise*>(index.internalPointer());
        t->setRabat(value.toDouble());
        emit dataChanged(index, index);
        return true;
    }
    if(role == Qt::EditRole && isIlosc(index))
    {
        Merchandise* t = static_cast<Merchandise*>(index.internalPointer());
        t->setIlosc(value.toDouble());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

QVariant TowarModel::data(const QModelIndex &index, int role) const
{

    if(!(role == Qt::DisplayRole || role == Qt::EditRole) || !index.isValid() || (index.row() > m_list.count()))
        return QVariant();

    Merchandise* t = static_cast<Merchandise*>(index.internalPointer());

    if(role == Qt::EditRole)
    {
        if(isRabat(index))
        {
            return t->rabat(); //m_list[index.row()]->rabat();
        }
        if(isIlosc(index))
        {
            return t->ilosc(); //m_list[index.row()]->ilosc();
        }
        return QVariant();
    }
/*
    if(t == NULL)
    {
        qWarning() << "Unable to cast index internal pointer to Towar";
        return QVariant();
    }
*/
    if(m_pln)
    {
        if(index.row() == m_list.count())
        {
            if(index.column() == 7)
                return tr("Suma:");
            if(index.column() == 8)
                return QString::number(przeliczSume(), 'f', 2);
            return QVariant();
        }
        else switch(index.column())
        {
            case 0: return t->kod();
            case 1: return t->nazwa();
            case 2: return QString::number(t->cenaKat(), 'f', 2);
            case 3: return QString::number(t->cenaPln(m_kurs), 'f', 2);
            case 4: return QString::number(t->rabat(), 'f', 2);
            case 5: return QString::number(t->cena(m_kurs), 'f', 2);
            case 6: return QString::number(t->ilosc(), 'f', 2);
            case 7: return tr(t->metr() ? "mb." : "szt.");
            case 8: return QString::number(t->wartosc(m_kurs), 'f', 2);
        }
    }
    else
    {
        if(index.row() == m_list.count())
        {
            if(index.column() == 6)
                return tr("Suma:");
            if(index.column() == 7)
                return QString::number(przeliczSume(), 'f', 2);
            return QVariant();
        }
        else switch(index.column())
        {
            case 0: return t->kod();
            case 1: return t->nazwa();
            case 2: return QString::number(t->cenaKat(), 'f', 2);
            case 3: return QString::number(t->rabat(), 'f', 2);
            case 4: return QString::number(t->cena(), 'f', 2);
            case 5: return QString::number(t->ilosc(), 'f', 2);
            case 6: return tr(t->metr() ? "mb." : "szt.");
            case 7: return QString::number(t->wartosc(), 'f', 2);
        }
    }
    qWarning() << "View requested non-existant column, number:" << index.column();

    return QVariant();
}

QVariant TowarModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(!role == Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Vertical)
    {
        if(section == m_list.count())
            return QVariant();

        return QString::number(section+1);
    }

    if(m_pln) switch(section)
    {
    case 0: return tr("Kod");
    case 1: return tr("Nazwa");
    case 2: return tr("Cena Kat. €");
    case 3: return tr("Cena Kat. zł");
    case 4: return tr("Rabat");
    case 5: return tr("Cena zł");
    case 6: return tr("Ilość");
    case 7: return tr("j/m");
    case 8: return tr("Wartość zł");
    }
    else switch(section)
    {
    case 0: return tr("Kod");
    case 1: return tr("Nazwa");
    case 2: return tr("Cena Kat. €");
    case 3: return tr("Rabat");
    case 4: return tr("Cena €");
    case 5: return tr("Ilość");
    case 6: return tr("j/m");
    case 7: return tr("Wartość €");
    }

    qWarning() << "View requested non-existant column, number:" << section;
    return QVariant();
}

Qt::ItemFlags TowarModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return 0;

    if(isRabat(index) || isIlosc(index))
        return Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsEnabled;

    return Qt::ItemIsSelectable|Qt::ItemIsEnabled;
}

QModelIndex TowarModel::index(int row, int column, const QModelIndex & /*parent*/) const
{
    if(row > m_list.count())
        return QModelIndex();
    else if(row == m_list.count())
        return QAbstractTableModel::createIndex(row, column, nullptr);
    return QAbstractTableModel::createIndex(row, column, m_list[row]);
}

bool TowarModel::pln() const
{
    return m_pln;
}

void TowarModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, m_list.count()-1);
    qDeleteAll(m_list);
    m_list.clear();
    endRemoveRows();
}
double TowarModel::kurs() const
{
    return m_kurs;
}

bool TowarModel::isRabat(const QModelIndex &i) const
{
    if(i.row() < m_list.count() && ((m_pln && i.column() == 4) || (!m_pln && i.column() == 3)))
        return true;
    return false;
}

bool TowarModel::isIlosc(const QModelIndex &i) const
{
    if(i.row() < m_list.count() && ((m_pln && i.column() == 6) || (!m_pln && i.column() == 5)))
        return true;
    return false;
}

void TowarModel::setKurs(double kurs)
{
    if(m_pln && (m_kurs == 0 || m_kurs == 1 || m_kurs == -1))
    {
        m_kurs = 1;
        beginRemoveColumns(QModelIndex(), 3, 3);
        m_pln = false;
        endRemoveColumns();
    }
    else
    {
        m_kurs = kurs;
        beginInsertColumns(QModelIndex(), 3, 3);
        m_pln = true;
        endInsertColumns();
    }
}

void TowarModel::changeItemCount(int id, double ile)
{
    Merchandise* t = new Merchandise(id);
    if(m_list.contains(t))
        m_list[m_list.indexOf(t)]->setIlosc(ile);
    else
    {
        m_list.append(localDatabase()->merchandise(id));
    }
}


bool TowarModel::removeRows(int row, int count, const QModelIndex & /*parent*/)
{
    if(row == m_list.count())
        return false;

    beginRemoveRows(QModelIndex(), row, row+count-1);
    for(int i=row; i < row+count; i++)
    {
        delete m_list[i];
        m_list.removeAt(i);
    }
    endRemoveRows();

    return true;
}

void TowarModel::setGlobalRabat(double r)
{
    foreach(Merchandise* t, m_list)
    {
        t->setRabat(r);
    }
// potrzebne?   emit dataChanged(this->index(2, 0), this->index(m_list.count(), 8)); -- ?
}

QHash<int, double> TowarModel::hash() const
{
    QHash<int, double> hash;

    foreach(Merchandise* t, m_list)
        hash.insert(t->id(), t->ilosc());

    return hash;
}

double TowarModel::przeliczSume() const
{
    double suma = 0;
    foreach(Merchandise* t, m_list)
        suma += t->wartosc(m_kurs);
    return suma;
}

void TowarModel::addItem(Merchandise *towar)
{
    int numer = m_list.count();
    beginInsertRows(QModelIndex(), numer, numer);
    m_list.append(towar);
    endInsertRows();
}

void TowarModel::loadOffer(const QSqlTableModel &mod)
{
    // TODO
    /*
    QSqlTableModel towary;
    towary.setTable("towar");
    towary.select();

    Merchandise* t;
    QSqlRecord record, towarRecord;

    for(int row=0; row<mod.rowCount(); ++row)
    {
        record = mod.record(row);

        towary.setFilter(QString("id='%1'").arg(record.value("kod").toString()));
        towarRecord = towary.record(0);

        t = new Merchandise(towarRecord);
        t->setRabat(record.value("rabat").toDouble());
        t->setIlosc(record.value("ilosc").toInt());

        addItem(t);
    }
    */
}

