#ifndef TOWARMODEL_H
#define TOWARMODEL_H

#include <QAbstractTableModel>
#include <QList>

class Towar;
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


signals:

public slots:

protected:
    QList<Towar*> m_list;
};

/*
class ImageModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    ImageModel(QObject *parent = 0);

    void setImage(const QImage &image);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:
    QImage modelImage;
};
*/
#endif // TOWARMODEL_H
