#include "AbstractDatabase.h"

#include <QSqlTableModel>
//#include <QSqlRecord>
#include <QtDebug>
#include <QDate>
#include <QtSql>

// AbstractDatabase* AbstractDatabase::m_instance = nullptr;


AbstractDatabase::AbstractDatabase(QObject *parent) :
    QObject(parent),
    m_db(nullptr),
    m_merchandiseModel(nullptr),
    m_customerModel(nullptr),
    m_usersModel(nullptr),
    m_optionsModel(nullptr),
    m_savedModel(nullptr),
    m_savedOptionsModel(nullptr),
    m_savedMerchandiseModel(nullptr),
    m_infoModel(nullptr)
{
}


/*******************************
 *      Database user related
 */

QString AbstractDatabase::remoteDbUserName()
{
    if(usersModel()->filter().isEmpty())
    {
        qWarning() << "No user selected!";
        return QString();
    }

    return usersModel()->record(0).value("remoteName").toString();
}

QString AbstractDatabase::remoteDbUserPass()
{
    if(usersModel()->filter().isEmpty())
    {
        qWarning() << "No user selected!";
        return QString();
    }

    return usersModel()->record(0).value("remotePass").toString();
}

/********************************
 *      Modele
 */

QSqlTableModel *AbstractDatabase::merchandiseModel()
{
    if(m_merchandiseModel == nullptr)
    {
        m_merchandiseModel = new QSqlTableModel(this, *m_db);
        m_merchandiseModel->setTable("merchandise");
        m_merchandiseModel->select();
    }

    return m_merchandiseModel;
}

QSqlTableModel *AbstractDatabase::customerModel()
{
    if(m_customerModel == nullptr)
    {
        m_customerModel = new QSqlTableModel(this, *m_db);
        m_customerModel->setTable("customer");
        m_customerModel->select();

        QStringList sl;
        sl << tr("Id") << tr("Nazwa") << tr("Nazwisko");
        for(int i=0; i<sl.size(); ++i)
            m_customerModel->setHeaderData(i, Qt::Horizontal, sl[i]);
    }

    return m_customerModel;
}

QSqlTableModel *AbstractDatabase::usersModel()
{
    if(m_usersModel == nullptr)
    {
        m_usersModel = new QSqlTableModel(this, *m_db);
        m_usersModel->setTable("users");
        m_usersModel->select();
    }

    return m_usersModel;
}
QSqlTableModel *AbstractDatabase::infoModel()
{
    if(m_infoModel == nullptr)
    {
        m_infoModel = new QSqlTableModel(this, *m_db);
        m_infoModel->setTable("info");
        m_infoModel->select();
    }

    return m_infoModel;
}

QSqlTableModel *AbstractDatabase::savedMerchandiseModel()
{
    if(m_savedMerchandiseModel == nullptr)
    {
        m_savedMerchandiseModel = new QSqlTableModel(this, *m_db);
        m_savedMerchandiseModel->setTable("saveMerchandise");
        m_savedMerchandiseModel->select();
    }

    return m_savedMerchandiseModel;
}

QSqlTableModel *AbstractDatabase::savedOptionsModel()
{
    if(m_savedOptionsModel == nullptr)
    {
        m_savedOptionsModel = new QSqlTableModel(this, *m_db);
        m_savedOptionsModel->setTable("savedOptions");
        m_savedOptionsModel->select();
    }

    return m_savedOptionsModel;
}

QSqlTableModel *AbstractDatabase::savedModel()
{
    if(m_savedModel == nullptr)
    {
        m_savedModel = new QSqlTableModel(this, *m_db);
        m_savedModel->setTable("saved");
        m_savedModel->select();
    }

    return m_savedModel;
}

QSqlTableModel *AbstractDatabase::optionsModel()
{
    if(m_optionsModel == nullptr)
    {
        m_optionsModel = new QSqlTableModel(this, *m_db);
        m_optionsModel->setTable("options");
        m_optionsModel->select();
    }

    return m_optionsModel;
}

/*******************************
 *      Users table
 */

void AbstractDatabase::setCurrentUser(int id)
{
    usersModel()->setFilter(QString("id = %1").arg(id));
}

QString AbstractDatabase::userName()
{
    if(usersModel()->filter().isEmpty())
    {
        qWarning() << "No user selected!";
        return QString();
    }

    return usersModel()->record(0).value("name").toString();
}

QString AbstractDatabase::userMail()
{
    if(usersModel()->filter().isEmpty())
    {
        qWarning() << "No user selected!";
        return QString();
    }

    return usersModel()->record(0).value("mail").toString();
}

QString AbstractDatabase::userAdress()
{
    if(usersModel()->filter().isEmpty())
    {
        qWarning() << "No user selected!";
        return QString();
    }

    return usersModel()->record(0).value("address").toString();
}

int AbstractDatabase::userOfferNumber()
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

QString AbstractDatabase::userOfferId()
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

QHash<int, QString> AbstractDatabase::userNames()
{
    usersModel()->setFilter("");
    QHash<int, QString> hash;
    for(int i=0; i < m_usersModel->rowCount(); ++i)
    {
        QSqlRecord rec = m_usersModel->record(i);
        hash.insert(rec.value("id").toInt(), rec.value("name").toString());
    }
    return hash;
}

/*******************************
 *      Options table
 */

QHash<QString, QString> AbstractDatabase::optionsList(eOptionType type)
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
