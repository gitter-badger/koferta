#include "TowarModel.h"
#include "Towar.h"
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlRecord>

TowarModel::TowarModel(QObject *parent) :
    QAbstractTableModel(parent), m_pln(false), m_kurs(1), m_suma(0)
{
}

TowarModel::~TowarModel()
{
    qDeleteAll(m_numery);
}

int TowarModel::rowCount(const QModelIndex & /*parent*/) const
{
    return m_numery.count() + 1;
}

int TowarModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 8;
}

QVariant TowarModel::data(const QModelIndex &index, int role) const
{
    if(!role == Qt::DisplayRole || index.row() > m_numery.count())
        return QVariant();

    if(index.row() == m_numery.count())
    {
        if(index.column() == 6)
            return tr("Suma:");
        if(index.column() == 7)
            return QString::number(m_suma);
        return QVariant();
    }

    Towar* t = static_cast<Towar*>(index.internalPointer());
/*
    if(t == NULL)
    {
        qWarning() << "Unable to cast index internal pointer to Towar";
        return QVariant();
    }
*/
    switch(index.column())
    {
    case 0:
        return t->kod();
    case 1:
        return t->nazwa();
    case 2:
        //------ PLN -------------------------------------
        return QString::number(t->cenaKat(), 'f', 2);
    case 3:
        return QString::number(t->rabat(), 'f', 2);
    case 4:
        return QString::number(t->cena(), 'f', 2);
    case 5:
        return QString::number(t->ilosc(), 'f', 2);
    case 6:
        if(t->metr())
            return QString("mb.");
        else
            return QString("szt.");
    case 7:
        return QString::number(t->wartosc(), 'f', 2);
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
        if(section == m_numery.count())
            return QVariant();

        return QString::number(section);
    }

    switch(section)
    {
    case 0:
        return tr("Kod");
    case 1:
        return tr("Nazwa");
    case 2:
        if(m_pln)
            return tr("Cena Kat. zł");
        else
            return tr("Cena Kat. €");
    case 3:
        return tr("Rabat");
    case 4:
        if(m_pln)
            return tr("Cena zł");
        else
            return tr("Cena €");
    case 5:
        return tr("Ilość");
    case 6:
        return tr("j/m");
    case 7:
        if(m_pln)
            return tr("Wartość zł");
        else
            return tr("Wartość €");
    }

    qWarning() << "View requested non-existant column, number:" << section;

    return QVariant();
}

Qt::ItemFlags TowarModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    if(index.column() == 3 || index.column() == 5)
        return Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsEnabled;

    return Qt::ItemIsSelectable|Qt::ItemIsEnabled;
}

QModelIndex TowarModel::index(int row, int column, const QModelIndex & /*parent*/) const
{
    if(row > m_numery.count())
        return QModelIndex();
    else if(row == m_numery.count())
        return QAbstractTableModel::createIndex(row, column, 0);
    return QAbstractTableModel::createIndex(row, column, m_numery[row]);
}

bool TowarModel::pln() const
{
    return m_pln;
}

void TowarModel::setPln(bool pln)
{
    m_pln = pln;
}

void TowarModel::ileTowaru(QString kod)
{
    if(m_kody.contains(kod))
        emit iloscTowaru(m_kody[kod]->ilosc());
    //else 0 ?
}

void TowarModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, m_numery.count()-1);
    qDeleteAll(m_numery);
    m_numery.clear();
    m_kody.clear();
    endRemoveRows();
}
double TowarModel::kurs() const
{
    return m_kurs;
}

void TowarModel::setKurs(double kurs)
{
    m_kurs = kurs;
}


bool TowarModel::removeRows(int row, int count, const QModelIndex & /*parent*/)
{
    beginRemoveRows(QModelIndex(), row, row+count);

    for(int i=row; i < row+count; i++)
    {
        m_kody.remove(m_numery[i]->kod());
        delete m_numery[i];
        m_numery.remove(i);
    }

    endRemoveRows();
    return true;
}

void TowarModel::changeItemCount(const QSqlRecord &rec, int ile)
{
    QString kod = rec.value("id").toString();
    if(!m_kody.contains(kod))
    {
        addItem(new Towar(rec));
    }

    m_kody[kod]->setIlosc(ile);
}

void TowarModel::addItem(Towar *towar)
{
    int numer = m_numery.count();
    beginInsertRows(QModelIndex(), numer, numer+1);
    m_numery.insert(numer, towar);
    m_kody.insert(towar->kod(), towar);
    endInsertRows();
}

void TowarModel::loadOffer(const QSqlTableModel &mod)
{
    QSqlTableModel towary;
    towary.setTable("towar");
    towary.select();

    Towar* t;
    QSqlRecord record, towarRecord;

    for(int row=0; row<mod.rowCount(); ++row)
    {
        record = mod.record(row);

        towary.setFilter(QString("id='%1'").arg(record.value("kod").toString()));
        towarRecord = towary.record(0);

        t = new Towar(towarRecord);
        t->setRabat(record.value("rabat").toDouble());
        t->setIlosc(record.value("ilosc").toInt());

        addItem(t);
    }
}

