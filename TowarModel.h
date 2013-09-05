#ifndef TOWARMODEL_H
#define TOWARMODEL_H

#include <QAbstractTableModel>
#include <QHash>

class Towar;
class QSqlTableModel;
class QSqlRecord;

/*!
 * \brief Model przechowywujący listę oferowanych towarów
 */
class TowarModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TowarModel(QObject *parent = 0);
    virtual ~TowarModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

    bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());

    void addItem(Towar* towar);
    void loadOffer(const QSqlTableModel& mod);

    bool pln() const;
    void setPln(bool pln);

    double kurs() const;
    void setKurs(double kurs);

signals:
    void iloscTowaru(int ile);

public slots:
    void ileTowaru(QString kod);
    void clear();

    void changeItemCount(const QSqlRecord& rec, int ile);

protected:
    QHash<QString, Towar*> m_kody;
    QHash<int, Towar*> m_numery;

    bool m_pln;
    double m_kurs;

    double m_suma;
};

#endif // TOWARMODEL_H
