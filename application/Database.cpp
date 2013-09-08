#include "Database.h"
#include <QtSql>
#include <QSqlTableModel>

Database* Database::m_instance = nullptr;

/*!
 * \brief filePath wyznacza bezwzględną ścieżka do pliku o nazwie jak plik wykonywalny z rozszerzeniem podanym jako parametr
 * \param suffix Rozszerzenie pliku (podawać z kropką)
 * \return QString zawierający ścieżkę bezwzględą z natywnymi separatorami
 */
QString filePath(const char* suffix)
{
    QString path = QCoreApplication::applicationFilePath();
#ifdef WIN32
    path = path.replace(".exe", suffix);
#else
    path = path + suffix;
#endif
    return QDir::toNativeSeparators(path);
}

Database::Database() :
    m_userModel(nullptr)
{
    m_db = new QSqlDatabase("QSQLITE");
    m_db.setDatabaseName(path(".sqlite"));

    if(m_db->open())
    {
        qDebug() << "SQLite database file open";
    }
    else
    {
        qFatal("Cannot open SQLite database");
    }
}

Database* Database::instance()
{
    if(m_instance == nullptr)
        m_instance = new Database();
    return m_instance;
}

QSqlTableModel *Database::userModel() const
{
    if(m_userModel == nullptr)
    {
        m_userModel = new QSqlTableModel(this);
        m_userModel->setTable("users");
        m_userModel->select();
    }

    return m_userModel;
}
