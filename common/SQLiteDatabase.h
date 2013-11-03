#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H

#include "AbstractDatabase.h"

class SQLiteDatabase : public AbstractDatabase
{
public:
    explicit SQLiteDatabase();
    

private:
    SQLiteDatabase(const SQLiteDatabase& other): AbstractDatabase(other)
    { static_assert(1, "Database object copying not implemented"); }
    SQLiteDatabase& operator=(const SQLiteDatabase& /*other*/)
    { static_assert(1, "Database object copying not implemented"); }
};

#endif // SQLITEDATABASE_H
