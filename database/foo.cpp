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
        qDebug() << "no password!";
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
        qDebug() << "invalid driver\n"
         << "library paths: ";
        list = qApp->libraryPaths();
        for(int i=0; i<list.size(); i++)
            qDebug() << "\t\t\t" << list[i];

        qDebug() << "aviable drivers: ";
        list = QSqlDatabase::drivers();
        for(int i=0; i<list.size(); i++)
            qDebug() << "\t\t\t" << list[i];
        return false;
    }

    if (!d->open())
    {
        qDebug() << "Błąd: nie można się połączyć z bazą!";
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
    qDebug() << "\n#############################################################################";
    qDebug() <<  "#\tPrzetwarzanie pliku:" << fileName << "\t#";
    qDebug() << "#############################################################################";

    switch(action)
    {
    case towar:
        importTowar(fileName, sl, dryRun);
        break;
    case klient:
        importKlient(fileName, sl, dryRun);
        break;
    case usr:
        importUser(fileName, sl, dryRun);
        break;
    case help:
        break;
    }
}

void importUser(const QString& fileName, QStringList& sl, bool dryRun)
{
    QStringList list;
    QSqlQuery q;
    QString s;
    QString sRead;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        if(!file.exists())qDebug() <<  "cennik nie iesnieje";
        else qDebug() <<  "cennik niedostępny";
        return;
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");

    unsigned i=0;
    while(!in.atEnd())
    {
        ++i;

        sRead = in.readLine();
        list = sRead.split(" ");
        if(list.size() < 2)
        {
            sl << QString("%1\t| %2\tZa mało kolumn").arg(fileName, QString::number(i));
            continue;
        }

        s = list[0];
        s.truncate(12);
        s.replace("ł", "l");
        s.replace("ą", "a");
        s.replace("ę", "e");
        s.replace("ó", "o");
        s.replace("ś", "s");
        s.replace("ż", "z");
        s.replace("ź", "z");
        s.replace("ć", "c");
        s.replace("ń", "n");
        s = "kOf_" + s;

        if(dryRun)
            continue;
/*
        q.prepare(QString("CREATE USER '%1'@'%' IDENTIFIED BY '%2'").arg(s, list[1]));
        if(!q.exec())
            qDebug() << q.lastError();
*/
        q.prepare(QString("GRANT SELECT, INSERT, UPDATE, DELETE ON kOferta.* TO '%1'@'%' IDENTIFIED BY '%2' REQUIRE SSL").arg(s, list[1]));
        if(!q.exec())
            qDebug() << q.lastError();

        qDebug() << "Dodano użytkownika:\t" << s;
    }
}

void importTowar(const QString& fileName, QStringList& sl, bool dryRun)
{
    static QStringList keys;
    QString key;
    QStringList list;
    QString sRead;
    QString cena;

    QString s;
    double dCena;
    bool f;
    QSqlQuery q;
    QVariantList ids, nazwy, ceny, j;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        if(!file.exists())qDebug() <<  "cennik nie iesnieje";
        else qDebug() <<  "cennik niedostępny";
        return;
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");

    unsigned i=0;
    while(!in.atEnd())
    {
        ++i;

        sRead = in.readLine();
        list = sRead.split("|");
        if(list.size() < 3)
        {
            sl << QString("%1\t| %2\tZa mało kolumn").arg(fileName, QString::number(i));
            continue;
        }

        key = list[1];
        if(keys.contains(key))
        {
            sl << QString("%1\t| %2\tDuplikat klucza: %3").arg(fileName, QString::number(i), key);
            continue;
        }
        keys << key;

        cena =  list[2];
        if(cena.isEmpty())
            dCena = 0;
        else
        {
       //     qDebug() << "przed konwersją: " << cena;
            cena.remove(' ');
            cena.remove('.');
            cena.remove(',');
            //cena.replace(',', '.');
            cena.insert(cena.size()-2, '.');
         //   qDebug() << "po konwersji: " << cena;
            dCena = cena.toDouble(&f);
            if(!f)
            {
                sl << QString("%1\t| %2\tZła cena: %3").arg(fileName, QString::number(i), cena);
                continue;
            }
        }

        if(list.size() > 3 && (list[3] == "mb." || list[3] == "m" || list[3] == "metr"))
            s = "mb.";
        else
            s = "szt.";

        if(!dryRun)
        {
            ids << key;
            nazwy << list[0];
            ceny << dCena;
            j << s;
        }
    }

    qDebug() <<  "Przetworzono lini:\t" << i;


    if(dryRun)
        return;

    int size = ids.size();
    if(size != nazwy.size() || size != ceny.size() || size != j.size())
    {
        qDebug() << "Błąd długości wektorów danych, długości:";
        qDebug() << QString("%1\t%2\t%3\t%4").arg(QString::number(size), QString::number(nazwy.size()), QString::number(ceny.size()), QString::number(j.size()));
        return;
    }

    q.prepare("INSERT INTO towar (id, nazwa, cena, jednostka) VALUES (:id, :nazwa, :cena, :j) ON DUPLICATE KEY UPDATE nazwa=VALUES(nazwa), cena=VALUES(cena), jednostka=VALUES(jednostka)");
    q.bindValue(":id", ids);
    q.bindValue(":nazwa", nazwy);
    q.bindValue(":cena", ceny);
    q.bindValue(":j", j);

    qDebug() << "Wysyłanie zapytania do bazy danych...";

    if (!q.execBatch())
         qDebug() << q.lastError();

    if(q.numRowsAffected() == -1)
        qDebug() << "Error?";
    else if(q.numRowsAffected() == 0)
        qDebug() << "Brak nowych wpisów";
    else
        qDebug() << "Dodano wpisy";
}

void importKlient(const QString& fileName, QStringList& sl, bool dryRun)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        if(!file.exists()) qDebug() <<  "klienci nie iesnieje";
        else qDebug() <<  "klienci niedostępny";
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
         qDebug() << q.lastError();
    if(q.numRowsAffected() == -1)
        qDebug() << "Error?";
    else if(q.numRowsAffected() == 0)
        qDebug() << "Brak nowych wpisów";
    else
        qDebug() << "Dodano wpisy";
}
