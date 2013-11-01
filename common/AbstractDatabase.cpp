#include "AbstractDatabase.h"

#include <QSqlTableModel>
#include <QtDebug>
#include <QDate>
#include <QtSql>

AbstractDatabase::AbstractDatabase() :
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

AbstractDatabase::~AbstractDatabase()
{
    delete m_db;

    delete m_merchandiseModel;
    delete m_customerModel;
    delete m_usersModel;
    delete m_optionsModel;
    delete m_savedModel;
    delete m_savedOptionsModel;
    delete m_savedMerchandiseModel;
    delete m_infoModel;
}

/********************************
 *      Modele
 */

QSqlTableModel *AbstractDatabase::merchandiseModel()
{
    if(m_merchandiseModel == nullptr)
    {
        m_merchandiseModel = new QSqlTableModel(0, *m_db);
        m_merchandiseModel->setTable("merchandise");
        m_merchandiseModel->select();
        m_merchandiseModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

        QStringList sl;
        sl << QObject::tr("Id") << QObject::tr("Nazwa");
        for(int i=0; i<sl.size(); ++i)
            m_merchandiseModel->setHeaderData(i, Qt::Horizontal, sl[i]);
    }

    return m_merchandiseModel;
}

QSqlTableModel *AbstractDatabase::customerModel()
{
    if(m_customerModel == nullptr)
    {
        m_customerModel = new QSqlTableModel(0, *m_db);
        m_customerModel->setTable("customer");
        m_customerModel->select();
        m_customerModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

        QStringList sl;
        sl << QObject::tr("Id") << QObject::tr("Nazwa") << QObject::tr("Nazwisko");
        for(int i=0; i<sl.size(); ++i)
            m_customerModel->setHeaderData(i, Qt::Horizontal, sl[i]);
    }

    return m_customerModel;
}

QSqlTableModel *AbstractDatabase::usersModel()
{
    if(m_usersModel == nullptr)
    {
        m_usersModel = new QSqlTableModel(0, *m_db);
        m_usersModel->setTable("users");
        m_usersModel->select();
    }

    return m_usersModel;
}
QSqlTableModel *AbstractDatabase::infoModel()
{
    if(m_infoModel == nullptr)
    {
        m_infoModel = new QSqlTableModel(0, *m_db);
        m_infoModel->setTable("info");
        m_infoModel->select();
    }

    return m_infoModel;
}

QSqlTableModel *AbstractDatabase::savedMerchandiseModel()
{
    if(m_savedMerchandiseModel == nullptr)
    {
        m_savedMerchandiseModel = new QSqlTableModel(0, *m_db);
        m_savedMerchandiseModel->setTable("saveMerchandise");
        m_savedMerchandiseModel->select();
    }

    return m_savedMerchandiseModel;
}

QSqlTableModel *AbstractDatabase::savedOptionsModel()
{
    if(m_savedOptionsModel == nullptr)
    {
        m_savedOptionsModel = new QSqlTableModel(0, *m_db);
        m_savedOptionsModel->setTable("savedOptions");
        m_savedOptionsModel->select();
    }

    return m_savedOptionsModel;
}

QSqlTableModel *AbstractDatabase::savedModel()
{
    if(m_savedModel == nullptr)
    {
        m_savedModel = new QSqlTableModel(0, *m_db);
        m_savedModel->setTable("saved");
        m_savedModel->select();
    }

    return m_savedModel;
}

QSqlTableModel *AbstractDatabase::optionsModel()
{
    if(m_optionsModel == nullptr)
    {
        m_optionsModel = new QSqlTableModel(0, *m_db);
        m_optionsModel->setTable("options");
        m_optionsModel->select();
    }

    return m_optionsModel;
}
