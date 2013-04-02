#include <QtCore/QCoreApplication>
#include <QString>
#include <QTextCodec>
#include <QStringList>
#include "foo.h"
#include <QDirIterator>

const QString ip = "192.168.1.90";



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
        else
            action = help;
        ar.removeFirst();
    }

    if(ar.contains("-h") || ar.contains("--help") || ar.contains("/?"))
        action = help;

    if(action == help)
    {
        qDebug() << "dbTools towar/klient [-h] [-d] [-r path] [file1.csv ...]";
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

    qDebug() << "\n##############################################";
    qDebug() << "Zakończono pracę. Błedne wpisy w plikach:";
    foreach(s, sl)
        qDebug() << s;

    qDebug() << "Przetworzono plików: " << files;
    qDebug() << "W sumie błędnych wpisów: " << sl.size();
    return 0;
}
