#include "LocalDatabase.h"
#include "functions.h"
#include <QtSql>
#include <QSqlTableModel>
#include <QDate>

LocalDatabase* LocalDatabase::m_instance = nullptr;

LocalDatabase::LocalDatabase() :
    m_merchandiseModel(nullptr),
    m_customerModel(nullptr),
    m_usersModel(nullptr),
    m_optionsModel(nullptr),
    m_savedModel(nullptr),
    m_savedOptionsModel(nullptr),
    m_savedMerchandiseModel(nullptr),
    m_infoModel(nullptr)
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

QString LocalDatabase::userName()
{
    return usersModel()->record(0).value("name").toString();
}

QString LocalDatabase::userMail()
{
    return usersModel()->record(0).value("mail").toString();
}

QString LocalDatabase::userAdress()
{
    return usersModel()->record(0).value("address").toString();
}

int LocalDatabase::userOfferNumber()
{
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
    QSqlRecord rec = usersModel()->record(0);
    return QString("%1%2/%3")
            .arg(rec.value("id").toInt()+1)
            .arg(QString::number(userOfferNumber()).rightJustified(3, '0'))
            .arg(QDate::currentDate().year());
}

QHash<int, QString> LocalDatabase::userNames()
{
    m_usersModel->setFilter("");
    QHash<int, QString> hash;
    for(int i=0; i < m_usersModel->rowCount(); ++i)
    {
        QSqlRecord rec = m_usersModel->record(i);
        hash.insert(rec.value("id").toInt(), rec.value("name").toString());
    }
    return hash;
}

void LocalDatabase::setCurrentUser(int id)
{
    usersModel()->setFilter(QString("id = %1").arg(id));
}

QSqlTableModel *LocalDatabase::merchandiseModel()
{
    if(m_merchandiseModel == nullptr)
    {
        m_merchandiseModel = new QSqlTableModel(this, *m_db);
        m_merchandiseModel->setTable("merchandise");
        m_merchandiseModel->select();
    }

    return m_merchandiseModel;
}

QSqlTableModel *LocalDatabase::customerModel()
{
    if(m_customerModel == nullptr)
    {
        m_customerModel = new QSqlTableModel(this, *m_db);
        m_customerModel->setTable("customer");
        m_customerModel->select();
    }

    return m_customerModel;
}

QHash<QString, QString> LocalDatabase::optionsList(eOptionType type)
{
    m_optionsModel->setFilter(QString("type = %1").arg(type));
    QHash<QString, QString> hash;
    for(int i=0; i<m_optionsModel->rowCount(); ++i)
    {
        QSqlRecord rec = m_optionsModel->record(i);
        hash.insert(rec.value("short").toString(), rec.value("long").toString());
    }
    return hash;
}

QSqlTableModel *LocalDatabase::usersModel()
{
    if(m_usersModel == nullptr)
    {
        m_usersModel = new QSqlTableModel(this, *m_db);
        m_usersModel->setTable("users");
        m_usersModel->select();
    }

    return m_usersModel;
}
QSqlTableModel *LocalDatabase::infoModel()
{
    if(m_infoModel == nullptr)
    {
        m_infoModel = new QSqlTableModel(this, *m_db);
        m_infoModel->setTable("info");
        m_infoModel->select();
    }

    return m_infoModel;
}

QSqlDatabase *LocalDatabase::db()
{
    return m_db;
}

QSqlTableModel *LocalDatabase::savedMerchandiseModel()
{
    if(m_savedMerchandiseModel == nullptr)
    {
        m_savedMerchandiseModel = new QSqlTableModel(this, *m_db);
        m_savedMerchandiseModel->setTable("saveMerchandise");
        m_savedMerchandiseModel->select();
    }

    return m_savedMerchandiseModel;
}

QSqlTableModel *LocalDatabase::savedOptionsModel()
{
    if(m_savedOptionsModel == nullptr)
    {
        m_savedOptionsModel = new QSqlTableModel(this, *m_db);
        m_savedOptionsModel->setTable("savedOptions");
        m_savedOptionsModel->select();
    }

    return m_savedOptionsModel;
}

QSqlTableModel *LocalDatabase::savedModel()
{
    if(m_savedModel == nullptr)
    {
        m_savedModel = new QSqlTableModel(this, *m_db);
        m_savedModel->setTable("saved");
        m_savedModel->select();
    }

    return m_savedModel;
}

QSqlTableModel *LocalDatabase::optionsModel()
{
    if(m_optionsModel == nullptr)
    {
        m_optionsModel = new QSqlTableModel(this, *m_db);
        m_optionsModel->setTable("options");
        m_optionsModel->select();
    }

    return m_optionsModel;
}
