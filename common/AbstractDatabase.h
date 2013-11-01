#ifndef ABSTRACTDATABASE_H
#define ABSTRACTDATABASE_H

#include <QHash>

class QSqlDatabase;
class QString;
class QSqlTableModel;
class QSqlRecord;

class AbstractDatabase
{
public:
    explicit AbstractDatabase();
    virtual ~AbstractDatabase() = 0;
/*
    //remote database login information
    virtual QString remoteDbUserName();
    virtual QString remoteDbUserPass();
*/
    //database
    QSqlDatabase* db() const
    { return m_db; }

    //models
    virtual QSqlTableModel* merchandiseModel();
    virtual QSqlTableModel* customerModel();
    virtual QSqlTableModel* usersModel();
    virtual QSqlTableModel* optionsModel();
    virtual QSqlTableModel* savedModel();
    virtual QSqlTableModel* savedOptionsModel();
    virtual QSqlTableModel* savedMerchandiseModel();
    virtual QSqlTableModel* infoModel();
/*
    //table user
    virtual void setCurrentUser(int id);
    virtual QString userName();
    virtual QString userMail();
    virtual QString userAdress();
    virtual int userOfferNumber();
    virtual QString userOfferId();
    virtual QHash<int, QString> userNames();

    //table options
    virtual QHash<QString, QString> optionsList(eOptionType type);
*/

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

//private:
    AbstractDatabase(const AbstractDatabase& /*other*/)
    { static_assert(1, "Database object copying not implemented"); }
    AbstractDatabase& operator=(const AbstractDatabase& /*other*/)
    { static_assert(1, "Database object copying not implemented"); }
};

#endif // ABSTRACTDATABASE_H
