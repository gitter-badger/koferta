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
        optShipping = 0,//dostawa
        optOffer = 1,   //oferta
        optPayment = 2, //platnosc
        optDelivery = 3 //termin
    };

    explicit AbstractDatabase(QObject *parent = 0);

    //remote database login information
    virtual QString remoteDbUserName();
    virtual QString remoteDbUserPass();

    //database
    QSqlDatabase* db() const
    { return m_db; }

    //models
    QSqlTableModel* merchandiseModel();
    QSqlTableModel* customerModel();
    QSqlTableModel* usersModel();
    QSqlTableModel* optionsModel();
    QSqlTableModel* savedModel();
    QSqlTableModel* savedOptionsModel();
    QSqlTableModel* savedMerchandiseModel();
    QSqlTableModel* infoModel();

    //table user
    void setCurrentUser(int id);
    QString userName();
    QString userMail();
    QString userAdress();
    int userOfferNumber();
    QString userOfferId();
    QHash<int, QString> userNames();

    //table options
    QHash<QString, QString> optionsList(eOptionType type);
    
signals:
    
public slots:

protected:

    AbstractDatabase(const AbstractDatabase& /*other*/):QObject(nullptr){}

    QSqlDatabase* m_db;

  //  static AbstractDatabase* m_instance;

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