#include "Database.h"
#include "AbstractDatabase.h"
#include "Merchandise.h"

#include <QSqlTableModel>
#include <QSqlRecord>

Database::Database()
{
}

/**************************
 *  modele
 */

QSqlTableModel* Database::customerModel()
{
    return db()->customerModel();
}

QSqlTableModel* Database::merchandiseModel()
{
    return db()->customerModel();
}

/*******************************
 *      Users table
 */

QHash<int, QString> Database::userNames()
{
    QSqlTableModel* usersModel = db()->usersModel();
    usersModel->setFilter("");
    QHash<int, QString> hash;
    for(int i=0; i < usersModel->rowCount(); ++i)
    {
        QSqlRecord rec = usersModel->record(i);
        hash.insert(rec.value("id").toInt(), rec.value("name").toString());
    }
    return hash;
}

/*******************************
 *      Options table
 */

QHash<QString, QString> Database::optionsList(eOptionType type)
{
    QSqlTableModel* optionsModel = db()->optionsModel();
    optionsModel->setFilter(QString("type = %1").arg(type));
    QHash<QString, QString> hash;
    for(int i=0; i < optionsModel->rowCount(); ++i)
    {
        QSqlRecord rec = optionsModel->record(i);
        hash.insert(rec.value("short").toString(), rec.value("long").toString());
    }
    return hash;
}

/*******************************
 *      Merchandise table
 */

Merchandise *Database::merchandise(int id)
{
    QSqlTableModel* merchModel = db()->merchandiseModel();
    merchModel->setFilter(QString("id = %1").arg(id));
    QSqlRecord r = merchModel->record();
    Merchandise* t = new Merchandise(id, r.value("code").toString(), r.value("desc").toString(), r.value("price").toDouble(), r.value("unit").toChar() == 'm');
    merchModel->setFilter("");
    return t;
}
