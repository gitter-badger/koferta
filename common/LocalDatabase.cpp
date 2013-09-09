#include "LocalDatabase.h"
#include <QtSql>
#include <QSqlTableModel>

LocalDatabase* LocalDatabase::m_instance = nullptr;

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

LocalDatabase::LocalDatabase() :
    m_userModel(nullptr)
{
    m_db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    m_db->setDatabaseName(filePath(".sqlite"));

    if(m_db->open())
    {
        qDebug() << "SQLite Local Database file open";
    }
    else
    {
        qFatal("Cannot open SQLite Local Database");
    }
}

LocalDatabase* LocalDatabase::instance()
{
    if(m_instance == nullptr)
        m_instance = new LocalDatabase();
    return m_instance;
}

QSqlTableModel *LocalDatabase::userModel()
{
    if(m_userModel == nullptr)
    {
        m_userModel = new QSqlTableModel();
        m_userModel->setTable("users");
        m_userModel->select();
    }

    return m_userModel;
}
