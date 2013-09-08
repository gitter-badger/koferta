#include <QtCore/QCoreApplication>
#include <QString>
#include <QTextCodec>
#include <QStringList>
#include "foo.h"
#include <QDirIterator>

const QString ip = "localhost";// "192.168.1.90";

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    //parsing args

    actions action;
    QStringList ar = a.arguments();
    ar.removeFirst();

    if(ar.size() == 0)
        action = help;
    else
    {
        if(ar[0] == "towar")
            action = towar;
        else if(ar[0] == "klient")
            action = klient;
        else if(ar[0] == "user")
            action = usr;
        else
            action = help;
        ar.removeFirst();
    }

    if(ar.contains("-h") || ar.contains("--help") || ar.contains("/?"))
        action = help;

    if(action == help)
    {
        qDebug() << "dbTools action [-h] [-d] [-r path] [file1.csv ...]";
        qDebug() << "actions:\ttowar, klient, user";
        qDebug() << "-h --help\tPrint this help and exit";
        qDebug() << "-d\t\tDry run - check syntax, not inserting into base";
        qDebug() << "-r path\t\tRecursive - scans path for all .csv files";
        return 0;
    }

    bool dryRun = false;
    bool recursive = false;

    if(ar.contains("-d"))
        dryRun = true;
    if(ar.contains("-r"))
        recursive = true;

    //connect to db

    if(!dryRun)
        if(!connect(ip))
            return 1;

    //process files

    QString s;
    QStringList sl;
    QString path;
    int files=0;

    //all .csv from folder recursively
    if(recursive)
    {
        foreach(s, ar)
        {
           if(s[0] == '-')
               continue;
           path = s;
           break;
        }
        QDirIterator it(path, QDirIterator::NoIteratorFlags);
        while (it.hasNext())
        {
            s = it.next();
            if(s.contains(".csv"))
            {
                files++;
                import(s, sl, action, dryRun);
            }
        }
    }
    else //take file names from commandline args
    {
        foreach(s, ar)
        {
            if(s[0] == '-')
                continue;
            files++;
            import(s, sl, action, dryRun);
        }
    }

    qDebug() << "\nPrzetworzono plików: " << files;
    qDebug() << "Błędnych wpisów: " << sl.size();
    qDebug() << "Błedne wpisy:";
    qDebug() << "Plik\t\t| Linia\t| Błąd";
    foreach(s, sl)
        qDebug() << s;

    return 0;
}
