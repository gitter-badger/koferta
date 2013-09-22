#include "LocalDatabase.h"

template<class dbType>
AbstractDatabase* LocalDatabase<dbType>::m_instance = nullptr;

template<class dbType>
AbstractDatabase* LocalDatabase<dbType>::instance()
{
    if(m_instance == nullptr)
        m_instance = new dbType();
    return m_instance;
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

