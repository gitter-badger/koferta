#ifndef DATABASE_H
#define DATABASE_H

#include <QHash>
#include <QString>

//class QSqlDatabase;
class QSqlTableModel;
class QString;
class AbstractDatabase;
class Towar;

/*!
 * \brief Klasa stanowiąca interface do bazy danych wykorzystując wzorzec most.
 */
class Database
{
public:
    enum eOptionType
    {
        optShipping = 0,//dostawa
        optOffer = 1,   //oferta
        optPayment = 2, //platnosc
        optDelivery = 3 //termin
    };

    Database();

  //  QSqlDatabase* db();

    //modele
    virtual QSqlTableModel* customerModel();
    virtual QSqlTableModel* merchandiseModel();

    //table user
    virtual QHash<int, QString> userNames();

    //table options
    virtual QHash<QString, QString> optionsList(eOptionType type);

    //table merchandise
    virtual Towar* merchandise(int id);

protected:
    /// Funkcja powinna zwracać wskaźnik na implementację bazy
    virtual AbstractDatabase* db() = 0;

//private:
    Database(const Database& /*other*/)
    { static_assert(1, "Database object copying not implemented"); }
    Database& operator=(const Database& /*other*/)
    { static_assert(1, "Database object copying not implemented"); }
};

#endif // DATABASE_H


/*
    static QSqlTableModel* usersModel();
    static QSqlTableModel* optionsModel();
    static QSqlTableModel* savedModel();
    static QSqlTableModel* savedOptionsModel();
    static QSqlTableModel* savedMerchandiseModel();
    static QSqlTableModel* infoModel();

    static int userOfferNumber();
*/
