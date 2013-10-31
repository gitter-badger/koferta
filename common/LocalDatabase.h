#ifndef DATABASE_H
#define DATABASE_H

#include "AbstractDatabase.h"
#include "sqlitedatabase.h"
#include <QHash>

/*!
 * \brief Klasa stanowiąca interface do lokalnej bazy danych.
 *
 * Implementacja wykorzystuje wzorzec singleton.
 * Typ bazy danych jest przekazywany jako parametr szablonu.
 */
template<class dbType>
class LocalDatabase
{
public:

    static AbstractDatabase* instance();

    //models
    static QSqlTableModel* customerModel();
    static QSqlTableModel* merchandiseModel();
/*
    static QSqlTableModel* usersModel();
    static QSqlTableModel* optionsModel();
    static QSqlTableModel* savedModel();
    static QSqlTableModel* savedOptionsModel();
    static QSqlTableModel* savedMerchandiseModel();
    static QSqlTableModel* infoModel();
*/

    //remote database login information
    static QString remoteDbUserPass();
    static QString remoteDbUserName();

    //database
    static QSqlDatabase* db();

    //table user
    static void setCurrentUser(int id);
    static QString userName();
    static QString userMail();
    static QString userAdress();
    static int userOfferNumber();
    static QString userOfferId();
    static QHash<int, QString> userNames();

    //table options
    static QHash<QString, QString> optionsList(AbstractDatabase::eOptionType type);


private:
    ///Blokuje konstrukcję obiektu z zewnątrz
    explicit LocalDatabase();
    ///Blokuje konstrukcję obiektu z zewnątrz
    LocalDatabase(const LocalDatabase&)
    { qFatal("Singleton copy?!"); }

    static AbstractDatabase* m_instance;
};



typedef LocalDatabase<SQLiteDatabase> localDatabase;

#endif // DATABASE_H
