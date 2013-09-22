#include "sqlitedatabase.h"
#include "functions.h"
#include <QtSql>
#include <QtDebug>

SQLiteDatabase::SQLiteDatabase(QObject *parent) :
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

QString SQLiteDatabase::dbUserName()
{
    return QString();
}

QString SQLiteDatabase::dbPass()
{
    return QString();
}



