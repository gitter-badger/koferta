#ifndef PSQLDATABASE_H
#define PSQLDATABASE_H

#include "AbstractDatabase.h"

class PsqlDatabase : public AbstractDatabase
{
    Q_OBJECT
public:
    explicit PsqlDatabase(QObject *parent = 0);


signals:
    
public slots:
    
};

#endif // PSQLDATABASE_H
