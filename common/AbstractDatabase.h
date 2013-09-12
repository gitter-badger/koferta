#ifndef ABSTRACTDATABASE_H
#define ABSTRACTDATABASE_H

#include <QObject>
#include <QHash>

class QSqlDatabase;
class QString;
class QSqlTableModel;
class QSqlRecord;

class AbstractDatabase : public QObject
{
    Q_OBJECT

public:

    enum eOptionType
    {
        optShipping = 0,
        optOffer,
        optPayment,
        optDelivery
    };

    QString psqlPass();
    QString psqlName();
    QHash<int, QString> userNames();
    void setCurrentUser(int id);


    QSqlTableModel* merchandiseModel();
    QSqlTableModel* customerModel();
    QSqlTableModel* usersModel();
    QSqlTableModel* optionsModel();
    QSqlTableModel* savedModel();
    QSqlTableModel* savedOptionsModel();
    QSqlTableModel* savedMerchandiseModel();
    QSqlTableModel* infoModel();

    QSqlDatabase* db() const
    { return m_db; }
    
signals:
    
public slots:

protected:
    explicit AbstractDatabase(QObject *parent = 0);
    AbstractDatabase(const AbstractDatabase& /*other*/):QObject(nullptr){}

    QSqlDatabase* m_db;

private:
    QSqlTableModel* m_merchandiseModel;
    QSqlTableModel* m_customerModel;
    QSqlTableModel* m_usersModel;
    QSqlTableModel* m_optionsModel;
    QSqlTableModel* m_savedModel;
    QSqlTableModel* m_savedOptionsModel;
    QSqlTableModel* m_savedMerchandiseModel;
    QSqlTableModel* m_infoModel;
};

#endif // ABSTRACTDATABASE_H
