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

#include "Wydruk.h"

#include <QPrintPreviewDialog>
#include <QTextDocument>
#include <QPrinter>
#include <QPrintDialog>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QFileDialog>
#include <QSqlQuery>

#include "Macros.h"
#include "ui_mainwindow.h"
#include "User.h"


cWydruk::~cWydruk()
{
    delete sDoc;
    delete printer;
    delete font;
    delete doc;
}

cWydruk::cWydruk(Ui::MainWindow* _ui, QString* data, int* klient, QString* numer)
{
    sDoc = new QString;

    ui = _ui;
    _numer = numer;
    _klient = klient;
    _data = data;

    //szerokosc komorek tabeli
    z[0] = 20; //lp
    z[1] = 80; //kod
    //z2 dynamicznie
    z[3] = 60; //cena
    z[4] = 40; //rabat
    z[5] = 55; //cena2
    z[6] = 50; //ilosc+jedn
    z[7] = 60; //wartość

    printer = new QPrinter;
    printer->setPaperSize(QPrinter::A4);
    printer->setResolution(300);
    printer->setPageMargins(margin, margin, margin, margin, QPrinter::Millimeter);

    font = new QFont;
    font->setPointSize(10);
    font->setFamily("Arial");

    doc = new QTextDocument;
    doc->setDefaultFont(*font);
}

void cWydruk::print(QPrinter *p)
{
    sDoc->clear();
    doc->clear();

    this->make();

    doc->setHtml(*sDoc);
    doc->print(p);
}

void cWydruk::prev()
{
    emit zapisz();
    htm = false;
    printer->setOutputFormat(QPrinter::NativeFormat);

    preview = new QPrintPreviewDialog(printer, this);
    preview->setWindowFlags ( Qt::Window );
    connect(preview, SIGNAL(paintRequested(QPrinter *)), SLOT(print(QPrinter *)));
    preview->exec();
    delete preview;
}

void cWydruk::do_pdf()
{
    emit zapisz();
    htm = false;

    QString s;

    printer->setOutputFormat(QPrinter::PdfFormat);
    s = QFileDialog::getSaveFileName(this, "Zapis pdfa", "", "Dokument PDF (*.pdf)");
    if(s.isEmpty())return;
    printer->setOutputFileName(s);
    print(printer);
}

void cWydruk::do_htm()
{
    emit zapisz();
    htm = true;

    QString s;
    s = QFileDialog::getSaveFileName(this, "Zapis do HTML", "", "Dokument HTML (*.htm)");
    if(s.isEmpty())return;

    QFile file(s);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        DEBUG << "plik " << s << " niedostępny";
        QMessageBox::warning(NULL, "error", "Nie udało się uzyskać dostępu do pliku");
        return;
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");
    this->make();
    in << *sDoc;
}



void cWydruk::make(){
    QString s;
    QSqlQuery q;
    QString waluta;
    int kolumn = 3;
    cUser* _u;
    int uid;

    uid = QString(_numer->at(0)).toInt() -1;
    _u = new cUser(uid);


    z[2] = w - z[0] - z[7];
    if(ui->kol_kod->isChecked())
    {
        z[2] -= z[1];
        kolumn++;
    }
    if(ui->kol_cenaKat->isChecked())
    {
        z[2] -= z[3];
        kolumn++;
    }
    if(ui->kol_rabat->isChecked())
    {
        z[2] -= z[4];
        kolumn++;
    }
    if(ui->kol_cena->isChecked())
    {
        z[2] -= z[5];
        kolumn++;
    }
    if(ui->kol_ilosc->isChecked())
    {
        z[2] -= z[6];
        kolumn++;
    }
    z[2] -= kolumn*4;

    if(ui->eur->isChecked()) waluta= "€";
    else waluta = "zł";

    uint rows = ui->tableWidget->rowCount()-1;

    s = "SELECT DISTINCT full, adres, tytul, imie, nazwisko FROM klient WHERE id=";
    s += QString::number(*_klient);

    EXEC(s);

    q.next();

    *sDoc = "<html>\n"
            "<head>\n"
            "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"></head>\n"
            "<title>Oferta</title>\n"
            "</head>\n"
            "<body>\n"
            "<table cellspacing=3>\n"
         /*NAGŁÓWEK*/
            "<thead>\n"
            "<tr><td>\n"
            "\t<table>\n"
            "\t<tr>\n"
            "\t\t<td colspan=3><hr width=100%></td>\n"
            "\t</tr>\n"
            "\t<tr>\n"
            "\t\t<td valign=top width=";
    *sDoc += QString::number(d);
    *sDoc += ">\n";

    *sDoc += "\t\t\tNumer oferty: <font size=4>";
    *sDoc += *_numer;
    *sDoc += "</font><br>\n"
             "\t\t\tData oferty: ";
    *sDoc += *_data;
    *sDoc += "\n"
            "\t\t\t<hr width=100%>\n"
            "\t\t\tDla:<br>\n"
            "\t\t\t";
    *sDoc += q.value(0).toString();
    *sDoc += "<br>\n"
            "\t\t\t";
    *sDoc += q.value(1).toString();
    *sDoc += "<br>\n"
            "\t\t\t";
    *sDoc += q.value(2).toString();
    *sDoc += " ";
    *sDoc += q.value(3).toString();
    *sDoc += " ";
    *sDoc += q.value(4).toString();
    *sDoc += "\n"
            "\t\t</td>\n";
    /*linia pionowa*/
    *sDoc += "\t\t<td width=1 bgcolor=#000000>\n"
            "\t\t\t<br />\n"
            "\t\t</td>\n";
    /*OD*/
    *sDoc += "\t\t<td width=";
    *sDoc += QString::number(d);
    *sDoc += ">\n"
            "\t\t\t";
    if(htm)
        *sDoc += "<img src=logo.jpg align=center><br>\n";
    else
        *sDoc += "<img src=:/log align=center><br>\n";
    *sDoc +=
             "\t\t\t<b>Marley Polska Sp. z o.o.</b><br>\n"
             "\t\t\tul. Annopol 24<br>\n"
             "\t\t\t03-236 Warszawa<br>\n"
             "\t\t\t<br>\n"
             "\t\t\t";
    /*adres bióra*/
    *sDoc += _u->adress().replace("\n", "\n\t\t\t");
    *sDoc += _u->mail();
    *sDoc += "\n"
            "\t\t</td>\n"
            "\t</tr>\n"
            "\t<tr>\n"
            "\t\t<td colspan=3><hr width=100%></td>\n"
            "\t</tr>\n"
            "\t</table>\n"
            "</td></tr>\n"
            "</thead>\n"
   /*Właściwa oferta*/
            "<tbody>\n"
            "<tr><td>\n"
            "\t";
    *sDoc += ui->plainTextEdit_zapytanie->toPlainText();
    *sDoc += "<br />\n"
            "</td></tr>\n"
            "<tr><td>\n";
 //tabela
    *sDoc += "\t<font face=\"Arial Narrow\" size=2>\n"
             "\t<table cellspacing=3>\n"
             "\t<thead><tr>\n"
             "\t\t<td width=";
    *sDoc += QString::number(z[0]);
    *sDoc += ">LP</td>\n";
    if(ui->kol_kod->isChecked())
    {
        *sDoc += "\t\t<td width=";
        *sDoc += QString::number(z[1]);
        *sDoc += ">Kod</td>\n";
    }
    if(ui->kol_towar->isChecked())
    {
        *sDoc += "\t\t<td width=";
        *sDoc += QString::number(z[2]);
        *sDoc += ">Specyfikacja</td>\n";
    }
    if(ui->kol_ilosc->isChecked())
    {
        *sDoc += "\t\t<td width=";
        *sDoc += QString::number(z[6]);
        *sDoc += " align = right>Ilość</td>\n";
    }
    if(ui->kol_cenaKat->isChecked())
    {
        *sDoc += "\t\t<td width=";
        *sDoc += QString::number(z[3]);
        *sDoc += " align = right>Cena kat. ";
        *sDoc += waluta;
        *sDoc += "</td>\n";
    }
    if(ui->kol_rabat->isChecked())
    {
        *sDoc += "\t\t<td width=";
        *sDoc += QString::number(z[4]);
        *sDoc += " align = right>Rabat</td>\n";
    }
    if(ui->kol_cena->isChecked())
    {
        *sDoc += "\t\t<td width=";
        *sDoc += QString::number(z[5]);
        *sDoc += " align = right>Cena ";
        *sDoc += waluta;
        *sDoc += "</td>\n";
    }
    *sDoc += "\t\t<td width=";
    *sDoc += QString::number(z[7]);
    *sDoc += " align = right>Wartość ";
    *sDoc += waluta;
    *sDoc += "</td>\n"
          "\t</tr></thead>\n";

    for(uint i=0; i<rows; ++i){
        *sDoc += "\t<tr>\n\t\t<td>";
        *sDoc += QString::number(i+1);
        *sDoc += "</td>\n";
        if(ui->kol_kod->isChecked())
        {
            *sDoc += "\t\t<td>";
            *sDoc += ui->tableWidget->item(i, 0)->text();
            *sDoc += "</td>\n";
        }
        if(ui->kol_towar->isChecked())
        {
            *sDoc += "\t\t<td>";
            *sDoc += ui->tableWidget->item(i, 1)->text();
            *sDoc += "</td>\n";
        }
        if(ui->kol_ilosc->isChecked())
        {
            *sDoc += "\t\t<td align=right>";
            *sDoc += ui->tableWidget->item(i, 5)->text();
            *sDoc += " ";
            *sDoc += ui->tableWidget->item(i, 6)->text();
            *sDoc += "</td>\n";
        }
        if(ui->kol_cenaKat->isChecked())
        {
            *sDoc += "\t\t<td align = right>";
            *sDoc += ui->tableWidget->item(i, 2)->text();
            *sDoc += "</td>\n";
        }
        if(ui->kol_rabat->isChecked())
        {
            *sDoc += "\t\t<td align = right>";
            *sDoc += ui->tableWidget->item(i, 3)->text();
            *sDoc += "%</td>\n";
        }
        if(ui->kol_cena->isChecked())
        {
            *sDoc += "\t\t<td align = right>";
            *sDoc += ui->tableWidget->item(i, 4)->text();
            *sDoc += "</td>\n";
        }
        *sDoc += "\t\t<td align = right>";
        *sDoc += ui->tableWidget->item(i, 7)->text();
        *sDoc += "</td>\n"
                 "\t</tr>\n";
    }
    *sDoc += "\t<tr>\n"
            "\t\t<td colspan=";
    *sDoc += QString::number(kolumn-1);
    *sDoc += " align=right>Razem ";
    *sDoc += waluta;
    *sDoc += ":</td>\n"
            "\t\t<td align=right>";
    *sDoc += ui->tableWidget->item(rows, 7)->text();
    *sDoc += "</td>\n"
            "\t</tr>\n"
            "\t</table></font>\n"
            "</td></tr>\n"
            "<tr><td>\n"
            "\tPodane ceny nie zawierają podatku VAT<br>\n"
            "</td></tr>\n"
//warunki
            "<tr><td>\n"
            "\t<table cellspacing=3>\n"
            "\t<tr>\n\t\t<td width=";
    *sDoc += QString::number(dw);
    *sDoc += ">"
             "Warunki dostawy:</td>\n"
             "\t\t<td width=";
    *sDoc += QString::number(w-dw-3);
    *sDoc += ">";
    *sDoc += ui->plainTextEdit_dostawa->toPlainText();
    *sDoc += "</td>\n\t</tr>\n"
             "\t<tr>\n"
             "\t\t<td>Termin dostawy:</td>\n"
             "\t\t<td>";
    *sDoc += ui->plainTextEdit_termin->toPlainText();
    *sDoc += "</td>\n"
             "\t</tr>\n"
             "\t<tr>\n"
             "\t\t<td>Warunki plałatności:</td>\n"
             "\t\t<td>";
    *sDoc += ui->plainTextEdit_platnosc->toPlainText();
    *sDoc += "</td>\n"
             "\t</tr>\n"
            "\t<tr>\n"
            "\t\t<td>Uwagi:</td>\n"
            "\t\t<td>";
   *sDoc += ui->plainTextEdit_uwagi->toPlainText();
   *sDoc += "</td>\n"
            "\t</tr>\n"
            "\t</table>\n"
            "</td></tr>\n";
//Pozdro600
    *sDoc += "<tr><td>\n"
            "\t";
    *sDoc += ui->plainTextEdit_oferta->toPlainText();
    *sDoc += "<br>\n"
             "\tŁączymy pozdrowienia.\n"
             "\t<p align = right style = \"margin-right: 100\">\n"
             "\t\tOfertę przygotował";
    if(!_u->male()) *sDoc += "a";
    *sDoc += "<br>\n"
            "\t\t";
    *sDoc += _u->name();
    *sDoc += "\n"
            "\t</p>\n"
            "</td></tr>\n"
            "</tbody>\n"
            /*
    //STOPKA
             "<tfoot><tr><td>\n"
             "\tS T O P K A\n"
             "</td></tr></tfoot>\n"
                     */
            "</table>\n"
            "</body>\n"
            "</html>\n";
}
