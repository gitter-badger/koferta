#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H

#include "AbstractDatabase.h"

class SQLiteDatabase : public AbstractDatabase
{
    Q_OBJECT
public:
    explicit SQLiteDatabase(QObject *parent = 0);

    QString dbUserName();
    QString dbPass();
    
signals:
    
public slots:
    
};

#endif // SQLITEDATABASE_H
