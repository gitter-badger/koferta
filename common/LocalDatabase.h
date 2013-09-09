#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>

class QSqlDatabase;
class QString;
class QSqlTableModel;

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
    QString userName() const;
    QString userMail() const;
    QString userAdress() const;
    QString userOfferNumber() const;

protected:
    QSqlDatabase* m_db;

    QSqlTableModel* userModel();
    QSqlTableModel* m_userModel;
private:
    ///Blokuje konstrukcję obiektu z zewnątrz
    LocalDatabase();
    ///Blokuje konstrukcję obiektu z zewnątrz
    LocalDatabase(const LocalDatabase&):QObject(){}

    static LocalDatabase* m_instance;
    int m_currentUserId;
};

#endif // DATABASE_H
