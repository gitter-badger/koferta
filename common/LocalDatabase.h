#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QHash>

class QSqlDatabase;
class QString;
class QSqlTableModel;
class QSqlRecord;

enum eOptionType
{
    optShipping = 0,
    optOffer,
    optPayment,
    optDelivery
};

/*!
 * \brief Klasa stanowiąca interface do lokalnej bazy danych SQLite.
 *
 * Klasa ta konstruuje odpowiednie modele na podstawie informacji z lokalnej bazy danych i
 * publicznie je udostępnia. Implementacja wykorzystuje wzorzec singleton.
 */

class LocalDatabase : public QObject
{
    Q_OBJECT

public:
    ///Zwraca wskaźnik na instancję obiektu bazy danych, w przypadku gdy instancja nie istnieje, wywouje konstruktor.
    static LocalDatabase* instance();
/*
    QString userName(int id) const;
    QString userMail(int id) const;
    QString userAdress(int id) const;
    QString userOfferNumber(int id) const;
*/
    //table user
    QString userName();
    QString userMail();
    QString userAdress();
    int userOfferNumber();
    QString userOfferId();

    QHash<int, QString> userNames();
    void setCurrentUser(int id);

    QList<QSqlRecord> optionsList(eOptionType type); //?

    QSqlTableModel* merchandiseModel();
    QSqlTableModel* customerModel();
    QSqlTableModel* usersModel();
    QSqlTableModel* optionsModel();
    QSqlTableModel* savedModel();
    QSqlTableModel* savedOptionsModel();
    QSqlTableModel* savedMerchandiseModel();
    QSqlTableModel* infoModel();

    QSqlDatabase* db();

protected:
    QSqlDatabase* m_db;

    QSqlTableModel* m_merchandiseModel;
    QSqlTableModel* m_customerModel;
    QSqlTableModel* m_usersModel;
    QSqlTableModel* m_optionsModel;
    QSqlTableModel* m_savedModel;
    QSqlTableModel* m_savedOptionsModel;
    QSqlTableModel* m_savedMerchandiseModel;
    QSqlTableModel* m_infoModel;

private:
    ///Blokuje konstrukcję obiektu z zewnątrz
    LocalDatabase();
    ///Blokuje konstrukcję obiektu z zewnątrz
    LocalDatabase(const LocalDatabase&):QObject(){}

    static LocalDatabase* m_instance;
};

#endif // DATABASE_H
