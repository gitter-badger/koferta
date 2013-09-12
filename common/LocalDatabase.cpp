#include "LocalDatabase.h"
#include "functions.h"

#include <QtSql>
#include <QDate>
#include <QtDebug>

LocalDatabase* LocalDatabase::m_instance = nullptr;

LocalDatabase::LocalDatabase(QObject *parent) :
    AbstractDatabase(parent)
{
    m_db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    m_db->setDatabaseName(filePath(".sqlite"));

    if(m_db->open())
    {
        qDebug() << "SQLite Local Database file open. File path:" << m_db->databaseName();
    }
    else
    {
        qFatal("Cannot open SQLite Local Database");
    }
}

LocalDatabase* LocalDatabase::instance()
{
    if(m_instance == nullptr)
        m_instance = new LocalDatabase();
    return m_instance;
}

QHash<QString, QString> LocalDatabase::optionsList(eOptionType type)
{
    optionsModel()->setFilter(QString("type = %1").arg(type));
    QHash<QString, QString> hash;
    for(int i=0; i < optionsModel()->rowCount(); ++i)
    {
        QSqlRecord rec = optionsModel()->record(i);
        hash.insert(rec.value("short").toString(), rec.value("long").toString());
    }
    return hash;
}

/*******************************
 *      User related
 */

QString LocalDatabase::userName()
{
    if(usersModel()->filter().isEmpty())
    {
        qWarning() << "No user selected!";
        return QString();
    }

    return usersModel()->record(0).value("name").toString();
}

QString LocalDatabase::userMail()
{
    if(usersModel()->filter().isEmpty())
    {
        qWarning() << "No user selected!";
        return QString();
    }

    return usersModel()->record(0).value("mail").toString();
}

QString LocalDatabase::userAdress()
{
    if(usersModel()->filter().isEmpty())
    {
        qWarning() << "No user selected!";
        return QString();
    }

    return usersModel()->record(0).value("address").toString();
}

int LocalDatabase::userOfferNumber()
{
    if(usersModel()->filter().isEmpty())
    {
        qWarning() << "No user selected!";
        return -1;
    }

    QSqlRecord rec = usersModel()->record(0);
    if(rec.value("lastOfferYear").toInt() != QDate::currentDate().year())
    {
        rec.field("lastOfferNumber").setValue(QVariant(0));
        rec.field("lastOfferYear").setValue(QVariant(QDate::currentDate().year()));
        //rec.replace(rec.indexOf("lastOfferNumber"), QSqlField());
     //   usersModel()->setRecord(0, rec);
    }
    return rec.value("lastOfferNumber").toInt();
}

QString LocalDatabase::userOfferId()
{
    if(usersModel()->filter().isEmpty())
    {
        qWarning() << "No user selected!";
        return QString();
    }

    QSqlRecord rec = usersModel()->record(0);
    return QString("%1%2/%3")
            .arg(rec.value("id").toInt()+1)
            .arg(QString::number(userOfferNumber()).rightJustified(3, '0'))
            .arg(QDate::currentDate().year());
}
