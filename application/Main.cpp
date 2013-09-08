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

#include <QApplication>
#include <QTextCodec>
#include <exception>
#include <QDate>
#include "MainWindow.h"
#include <QtDebug>

#define QT_NO_DEBUG_OUTPUT

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

#ifndef QT_NO_DEBUG_OUTPUT
#ifdef WIN32
    QString fileName = QCoreApplication::applicationFilePath().replace(".exe", ".log");
#else
    QString fileName = QCoreApplication::applicationFilePath() + ".log";
#endif
    QFile *log = new QFile(fileName);
    if (log->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        out = new QTextStream(log);
     //   out->setCodec(QTextCodec::codecForName("UTF-8"));
        qInstallMsgHandler(logOutput);
    }
    else
    {
        qDebug() << "Error opening log file '" << fileName << "'. All debug output redirected to console.";
    }
#endif
    int result;

    MainWindow w;
    w.showMaximized();

    qDebug() << "wchodzę do głównej pętli";

    try
    {
        result = a.exec();
    }
    catch (std::exception& e)
    {
        qCritical() << "[Mainwindow] Standard exception: " << e.what();
    }
    catch(...)
    {
        qCritical() << "[Mainwindow] Unknown exception";
    }

    qDebug() << "koniec programu, status: " << result;

    return result;
}
