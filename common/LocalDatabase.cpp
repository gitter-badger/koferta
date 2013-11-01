#include "LocalDatabase.h"
#include "sqlitedatabase.h"
#include <QtDebug>
#include <QSqlField>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QDate>

LocalDatabase* LocalDatabase::m_instance = nullptr;

LocalDatabase* localDatabase()
{
    return LocalDatabase::instance();
}

LocalDatabase::LocalDatabase()
{
    m_db = new SQLiteDatabase();
    m_curUsr = nullptr;
}

LocalDatabase* LocalDatabase::instance()
{
    if(m_instance == nullptr)
    {
        qDebug() << "making new instance of local database";
        m_instance = new LocalDatabase;
    }
    return m_instance;
}


/*******************************
 *      Users table
 */

QString LocalDatabase::remoteDbUserName()
{
    if(!m_curUsr)
    {
        qWarning() << "No user selected!";
        return QString();
    }

    return m_curUsr->value("remoteName").toString();
}

QString LocalDatabase::remoteDbUserPass()
{
    if(!m_curUsr)
    {
        qWarning() << "No user selected!";
        return QString();
    }

    return m_curUsr->value("remotePass").toString();
}



void LocalDatabase::setCurrentUser(int id)
{
    m_db->usersModel()->setFilter(QString("id = %1").arg(id));
    delete m_curUsr;
    m_curUsr = new QSqlRecord(m_db->usersModel()->record(0));
    m_db->usersModel()->setFilter("");
}

QString LocalDatabase::userName()
{
    if(!m_curUsr)
    {
        qWarning() << "No user selected!";
        return QString();
    }

    return m_curUsr->value("name").toString();
}

QString LocalDatabase::userMail()
{
    if(!m_curUsr)
    {
        qWarning() << "No user selected!";
        return QString();
    }

    return m_curUsr->value("mail").toString();
}

QString LocalDatabase::userAdress()
{
    if(!m_curUsr)
    {
        qWarning() << "No user selected!";
        return QString();
    }

    return m_curUsr->value("address").toString();
}

int LocalDatabase::userOfferNumber()
{
    if(m_curUsr->value("lastOfferYear").toInt() != QDate::currentDate().year())
    {
        m_curUsr->field("lastOfferNumber").setValue(QVariant(0));
        m_curUsr->field("lastOfferYear").setValue(QVariant(QDate::currentDate().year()));
        //rec.replace(rec.indexOf("lastOfferNumber"), QSqlField());
     //   usersModel()->setRecord(0, rec);
    }
    return m_curUsr->value("lastOfferNumber").toInt();
}

QString LocalDatabase::userOfferId()
{
    if(!m_curUsr)
    {
        qWarning() << "No user selected!";
        return QString();
    }

    return QString("%1%2/%3")
            .arg(m_curUsr->value("id").toInt()+1)
            .arg(QString::number(userOfferNumber()).rightJustified(3, '0'))
            .arg(QDate::currentDate().year());
}
