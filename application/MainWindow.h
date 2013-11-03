/**
  Główne okno programu
  **/
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>

class MerchandiseListModel;
class QSqlTableModel;
class QModelIndex;
class QTextDocument;
class QTableWidgetItem;
class cUser;
class QSqlRecord;
class QCalendarWidget;
class QDate;
class MerchandiseListDelegate;
class QPrinter;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();                              //aktualny użytkownik przekazywany jako parametr
    ~MainWindow();

public slots:
    void popWyborKlienta();
    void popWyborTowaru();

    void loadOffer(const QSqlRecord &rec, const QSqlTableModel &mod);              //wczytuje ofertę o połączone z dialogiem wczytywanie

    //obsługa głównej tabeli
    void rabat();                                       //ustawia rabat dla wszystkich pozycji jednocześnie
    void del();                                         //usuwanie wiersza z tabeli

    //odświerzanie texteditów drugiej zakładce
    void dostawaRef(QString);
    void platnoscRef(QString);
    void terminRef(QString);
    void ofertaRef(QString);
    void zapytanieRef();
    void calChanged(const QDate&);                      //zmiana nastąpiła w kalendarzu, wprowadzenie jej do dateedita
    void checkNr(bool);
    void checkData(bool);
    void clientChanged(const QSqlRecord&);              //ustawia wybranego klienta - połączone z sygnałem z dialogu klient

    //opcje wydruku
    void pln_on();                                      //włącza przeliczanie euro na pln
    void pln_off();                                     //wyłącza przeliczanie euro na pln

    //wydruk
    void printPrev();                                   //podgląd wydruku
    void printPdf();                                    //export do pdf
    void printHtm();                                    //zapis jako htm
    void print(QPrinter *printer);                      //"drukowanie" dokumentu do podglądu lub pdf
    void makeDocument(QString *sDoc);                   //tworzy dokument jako kod htm w QTextDocument

/*menu*/
    //menu plik
    void nowa();
    void zapisz();
    void popLoadDialog();
    void nowyNumer();
    //exit

    //help
    void about();                                       //wyświetla informacje o programie
    //o qt - wbudowane

private:
    Ui::MainWindow *ui;

    //obsługa głównej tabeli
    void sum();                                         //przelicza sumę wszystkich pozycji
    void przelicz(uint);                                //przelicza koszt towaru z zadanego wiersza
    double ev(unsigned row, unsigned col);              //odczytuje wartość numeryczną z komórki o podanych koordynatach
    void tabupd();                                      //przeliczenie wartości w całej tabeli po zmianie waluty

    //pomocnicze funkcje
    void setTitle(QString*);                            //ustawia tytuł okna
    void init();                                        //odblokowanie interfejsu i inicjacja tabeli

    //wewnętrzne zmienne
    QString* nr_oferty;
    QString* data;
    bool htm;

    MerchandiseListModel* m_towarModel;

    QCalendarWidget* calendarWidget;
    QSqlRecord* klient;

    int m_curUser;

    QHash<QString, QString> m_shippingOptions;
    QHash<QString, QString> m_offerOptions;
    QHash<QString, QString> m_paymentOptions;
    QHash<QString, QString> m_deliveryOptions;

};

#endif // MAINWINDOW_H
