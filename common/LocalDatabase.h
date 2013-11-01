#ifndef LOCALDATABASE_H
#define LOCALDATABASE_H

class SQLiteDatabase;
class QSqlRecord;

#include "Database.h"
#include <QHash>

/*!
 * \brief Klasa reprezentująca lokalną bazę danych wykorzystująca wzorzec singleton
 */
class LocalDatabase : public Database
{
public:
    //table user
    QString remoteDbUserPass();
    QString remoteDbUserName();
    virtual void setCurrentUser(int id);
    virtual QString userName();
    virtual QString userMail();
    virtual QString userAdress();
    virtual QString userOfferId();

protected:
    ///Blokuje konstrukcję obiektu z zewnątrz
    explicit LocalDatabase();
    ///Blokuje kopiowanie obiektu bazy
    LocalDatabase(const LocalDatabase& other) : Database(other)
    { static_assert(1, "Singleton copy?!"); }
    ///Blokuje kopiowanie obiektu bazy
    LocalDatabase& operator=(const LocalDatabase&)
    { static_assert(1, "Singleton copy?!"); }

    friend LocalDatabase* localDatabase();
    static LocalDatabase* instance();
    static LocalDatabase* m_instance;

    SQLiteDatabase* m_db;
    virtual AbstractDatabase* db();

    int userOfferNumber();
    QSqlRecord* m_curUsr;
};

LocalDatabase* localDatabase();

#endif
