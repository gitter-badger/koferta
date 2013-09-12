#ifndef DATABASE_H
#define DATABASE_H

#include "AbstractDatabase.h"



/*!
 * \brief Klasa stanowiąca interface do lokalnej bazy danych SQLite.
 *
 * Klasa ta konstruuje odpowiednie modele na podstawie informacji z lokalnej bazy danych i
 * publicznie je udostępnia. Implementacja wykorzystuje wzorzec singleton.
 */

class LocalDatabase : public AbstractDatabase
{
    Q_OBJECT

public:
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

    QHash<QString, QString> optionsList(eOptionType type);


private:
    ///Blokuje konstrukcję obiektu z zewnątrz
    explicit LocalDatabase(QObject *parent = 0);
    ///Blokuje konstrukcję obiektu z zewnątrz
    LocalDatabase(const LocalDatabase&):AbstractDatabase(){}

    static LocalDatabase* m_instance;
};

#endif // DATABASE_H
