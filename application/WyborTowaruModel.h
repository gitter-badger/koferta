#ifndef TOWARPROXY_H
#define TOWARPROXY_H

#include "SzukajTowaruModel.h"
#include <QHash>

class WyborTowaruModel : public SzukajTowaruModel
{
    Q_OBJECT

public:  
    WyborTowaruModel(QObject *parent);

    virtual int columnCount();
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    virtual void setHash(const QHash<QString, double>& hash);

protected:
    QHash<QString, double> m_hash;

};

#endif // TOWARPROXY_H
