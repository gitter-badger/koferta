#include "AbstractDatabase.h"

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QtDebug>

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
 *      User related
 */

void AbstractDatabase::setCurrentUser(int id)
{
    usersModel()->setFilter(QString("id = %1").arg(id));
}

QString AbstractDatabase::psqlPass()
{
    if(usersModel()->filter().isEmpty())
    {
        qWarning() << "No user selected!";
        return QString();
    }

    return usersModel()->record(0).value("psqlPass").toString();
}

QString AbstractDatabase::psqlName()
{
    if(usersModel()->filter().isEmpty())
    {
        qWarning() << "No user selected!";
        return QString();
    }

    return usersModel()->record(0).value("psqlName").toString();
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
