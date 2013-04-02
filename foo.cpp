#include "foo.h"
#include <QtSql>
#include <mysql/mysql.h>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <unistd.h>

bool connect(const QString &ip)
{
    QString pp;
    pp = "Enter root password for MySql database on ";
    pp += ip;
    pp += ":\n";
    char* cPass = getpass(pp.toStdString().c_str());
    QString pass(cPass);
    if(pass.isEmpty())
    {
        DEBUG << "no password!";
        return false;
    }

    QSqlDatabase* d = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL"));
    d->setHostName(ip);
    d->setPort(3306);
    d->setConnectOptions("CLIENT_SSL=1;CLIENT_IGNORE_SPACE=1");
    d->setUserName("root");
    d->setPassword(pass);
    d->setDatabaseName("kOferta");

    QVariant v = d->driver()->handle();
    if (v.isValid() && qstrcmp(v.typeName(), "MYSQL*")==0)
    {
        MYSQL *handle = static_cast<MYSQL *>(v.data());
        if (handle != NULL)
        {
            mysql_ssl_set(handle, ":/client-key",
                ":/client-cert", ":/ca-cacert",
                NULL, NULL);
        }
    }
    else
    {
        QStringList list;
        DEBUG << "invalid driver\n"
         << "library paths: ";
        list = qApp->libraryPaths();
        for(int i=0; i<list.size(); i++)
            qDebug() << "\t\t\t" << list[i];

        DEBUG << "aviable drivers: ";
        list = QSqlDatabase::drivers();
        for(int i=0; i<list.size(); i++)
            qDebug() << "\t\t\t" << list[i];
        return false;
    }

    if (!d->open())
    {
        DEBUG << "Błąd: nie można się połączyć z bazą!";
        qDebug() << "\t\t\t connName: " << d->connectionName();
        qDebug() << "\t\t\t driver: " << d->driverName();
        qDebug() << "\t\t\t opcje " << d->connectOptions();
        qDebug() << "\t\t\t host: " << d->hostName();
        qDebug() << "\t\t\t last error: " << d->lastError().text();
        return false;
    }

    return true;
}

void import(const QString& fileName, QStringList& sl, actions action, bool dryRun)
{
    switch(action)
    {
    case towar:
        importTowar(fileName, sl, dryRun);
        break;
    case klient:
        importKlient(fileName, sl, dryRun);
        break;
    case help:
        break;
    }
}

void importTowar(const QString& fileName, QStringList& sl, bool dryRun)
{
    static QStringList keys;
    QString key;
    QStringList list;
    QString sRead;
    QString cena;
    QDebug dbg(QtDebugMsg);
    QString s;
    double dCena;
    bool f;
    QSqlQuery q;
    QVariantList ids, nazwy, ceny, j;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        if(!file.exists())DEBUG <<  "cennik nie iesnieje";
        else DEBUG <<  "cennik niedostępny";
        return;
    }

    qDebug() << "\n#############################################################################";
    qDebug() <<  "#\tPrzetwarzanie pliku:" << fileName << "\t#";
    qDebug() << "#############################################################################\n";

    QTextStream in(&file);
    in.setCodec("UTF-8");

    for(unsigned i=0; !in.atEnd(); ++i)
    {
        sRead = in.readLine();
        list = sRead.split("|");
        if(list.size() < 3)
        {
            sl << QString("%1\t| %2\tZa mało kolumn").arg(fileName, QString::number(i+1));
            continue;
        }

        key = list[1];
        if(keys.contains(key))
        {
            sl << QString("%1\t| %2\tDuplikat klucza: %3").arg(fileName, QString::number(i+1), key);
            continue;
        }
        keys << key;

        cena =  list[2];
        cena.remove(' ');
        cena.replace(',', '.');
        dCena = cena.toDouble(&f);
        if(!f)
        {
            sl << QString("%1\t| %2\tZła cena: %3").arg(fileName, QString::number(i+1), cena);
            continue;
        }

        if(list.size() > 3 && (list[3] == "mb." || list[3] == "m" || list[3] == "metr"))
            s = "mb.";
        else
            s = "szt.";

        dbg <<  "\rPrzetworzono lini:\t" << i+1;

        if(!dryRun)
        {
            nazwy << list[0];
            ceny << dCena;
            j << s;
        }
    }

    dbg << "\n";

    if(dryRun)
        return;

    q.prepare("INSERT INTO towar (id, nazwa, cena, jednostka) VALUES (:id, :nazwa, :cena, :j) ON DUPLICATE KEY UPDATE nazwa=VALUES(nazwa), cena=VALUES(cena), jednostka=VALUES(jednostka)");
    q.bindValue(":id", ids);
    q.bindValue(":nazwa", nazwy);
    q.bindValue(":cena", ceny);
    q.bindValue(":j", j);

    if (!q.execBatch())
         DEBUG << q.lastError();

    return;
}

void importKlient(const QString& fileName, QStringList& sl, bool dryRun)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        if(!file.exists()) DEBUG <<  "klienci nie iesnieje";
        else DEBUG <<  "klienci niedostępny";
        return;
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");

    QStringList list;
    QString sRead;
    QString adres;
    QSqlQuery q;
    QDebug dbg(QtDebugMsg);
    QVariantList skrot, full, tytul, imie, nazwisko, adresy;

    for(unsigned i=0; !in.atEnd(); ++i)
    {
        dbg <<  "\rPrzetwarzam linię:\t" << i+1;

        sRead = in.readLine();
        list = sRead.split("|");
        if(list.size() < 8)
        {
            sl << QString("%1\t| %2\tZa mało kolumn").arg(fileName, QString::number(i+1));
            continue;
        }

        if(dryRun)
            continue;

        adres = list[5];
        adres += "<br>\n";
        adres += list[6];
        adres += " ";
        adres += list[7];

        skrot << list[4];
        full << list[3];
        tytul << list[0];
        imie << list[1];
        nazwisko << list[2];
        adresy << adres;
    }

    dbg << "\n";

    if(dryRun)
        return;

    q.prepare("INSERT INTO klient (short, full, tytul, imie, nazwisko, adres)  VALUES (:short, :full, :tytul, :imie, :nazwisko, :adres)");
    q.bindValue(":short", skrot);
    q.bindValue(":full", full);
    q.bindValue(":tytul", tytul);
    q.bindValue(":imie", imie);
    q.bindValue(":nazwisko", nazwisko);
    q.bindValue(":adres", adresy);

    if (!q.execBatch())
         DEBUG << q.lastError();

    return;
}
