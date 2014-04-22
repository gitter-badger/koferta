/**
    kOferta - system usprawniajacy proces ofertowania
    Copyright (C) 2011  Kamil 'konserw' Strzempowicz, konserw@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
#include <QtDebug>
#include <QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <exception>
#include <QtSql>
#include <QMessageBox>
#include <QObject>
#include "functions.h"
#include "Logger.h"
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    if(Logger::instance()->setFilePath(filePath(".log")))
        qInstallMessageHandler(Logger::logHandler);
    else
        qWarning() << "Unable to create log file! Logging to std::cerr.";

    qDebug() << "loading translation files";
/*
    QTranslator qtTranslator;
    qtTranslator.load("qt" + QLocale::system().name());
    app.installTranslator(&qtTranslator);
*/
    QString translationFile = QString("kOferta_%1").arg(QLocale::system().name());
    QTranslator myappTranslator;
    if(myappTranslator.load(translationFile))
        app.installTranslator(&myappTranslator);
    else
        qWarning() << "could not load translations from file" << translationFile;

    qDebug() << "checking sql driver";

    if(!QSqlDatabase::drivers().contains("QMYSQL"))
    {
        QMessageBox::critical(nullptr, QObject::tr("Błąd"), QObject::tr("Bład sterownika bazy danych!\nNastąpi zamknięcie programu."));
        qCritical() << "invalid driver";

        qDebug() << "library paths: ";
        QStringList list = qApp->libraryPaths();
        for(int i=0; i<list.size(); i++)
            qDebug() << "\t" << list[i];

        qDebug() << "aviable drivers: ";
        list = QSqlDatabase::drivers();
        for(int i=0; i<list.size(); i++)
            qDebug() << "\t" << list[i];

        return 2;
    }

    MainWindow w;
    w.showMaximized();

    qDebug() << "launching application";

    try
    {
        return app.exec();
    }
    catch (std::exception& e)
    {
        qCritical() << "[Mainwindow] Standard exception: " << e.what();
    }
    catch(...)
    {
        qCritical() << "[Mainwindow] Unknown exception";
    }
    return 1;
}
