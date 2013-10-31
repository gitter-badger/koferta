#include "LocalDatabase.h"
#include <QtDebug>

template<class dbType>
AbstractDatabase* LocalDatabase<dbType>::m_instance = nullptr;

template<class dbType>
AbstractDatabase* LocalDatabase<dbType>::instance()
{
    if(m_instance == nullptr)
    {
        qDebug() << "making new instance of local database";
        m_instance = new dbType();
    }
    return m_instance;
}

template<class dbType>
QSqlTableModel *LocalDatabase<dbType>::customerModel()
{
    return instance()->customerModel();
}

template<class dbType>
QSqlTableModel *LocalDatabase<dbType>::merchandiseModel()
{
    return instance()->merchandiseModel();
}

template<class dbType>
QString LocalDatabase<dbType>::remoteDbUserName()
{
    return instance()->remoteDbUserName();
}

template<class dbType>
QString LocalDatabase<dbType>::remoteDbUserPass()
{
    return instance()->remoteDbUserPass();
}

template<class dbType>
void LocalDatabase<dbType>::setCurrentUser(int id)
{
    return instance()->setCurrentUser(id);
}

template<class dbType>
QString LocalDatabase<dbType>::userOfferId()
{
    return instance()->userOfferId();
}

template<class dbType>
QHash<QString, QString> LocalDatabase<dbType>::optionsList(AbstractDatabase::eOptionType type)
{
    return instance()->optionsList(type);
}

