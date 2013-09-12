/**
    kOferta - system usprawniajacy proces ofertowania
    Copyright (C) 2011  Kamil "konserw" Strzempowicz, konserw@gmail.com

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

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDate>
#include <QInputDialog>
#include <QList>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QFileDialog>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QCalendarWidget>
#include <QPrintPreviewDialog>
#include <QTextDocument>
#include <QPrinter>
#include <QPrintDialog>
#include <QtDebug>
#include <QMessageBox>

#include "LocalDatabase.h"
#include "WyborTowaru.h"
#include "WyborKlienta.h"
#include "LoadDialog.h"
#include "TowarModel.h"
#include "Towar.h"
#include "TowarDelegate.h"

/*************************
**      GŁÓWNE OKNO     **
*************************/

MainWindow::~MainWindow()
{
    qDebug() << "destruktor mainwindow - start";

    delete ui;
    delete nr_oferty;
    delete data;
    delete calendarWidget;
    delete klient;
    delete m_towarModel;

    qDebug() << "destruktor mainwindow - koniec";
}

MainWindow::MainWindow ():
    QMainWindow(NULL),
    ui(new Ui::MainWindow),
    m_curUser(0) // <------- !!!!
{
    qDebug() << "konstruktor mainwindow";   
/**
  zmienne
 **/
    qDebug() << "inicjalizacja zmiennych";

    ui->setupUi(this);

    nr_oferty = new QString;
    data = new QString(QDate::currentDate().toString("dd.MM.yyyy"));

    calendarWidget = new QCalendarWidget;
    klient = NULL;

/**
  ui
**/
    qDebug() << "user interface";

    ui->tabWidget->setCurrentIndex(0);

    //stan początkowy
    this->setTitle(NULL);
    ui->tab->setEnabled(false);
    ui->tab_2->setEnabled(false);

    ui->menuExport->setEnabled(false);
    ui->actionSave->setEnabled(false);
    ui->actionNR->setEnabled(false);

/**
 Pozostałe informacje
**/

    ui->label_klient->setText(tr("Klient:"));
    ui->pushButton_wyborKlienta->setText(tr("Wybór klienta"));
    ui->plainTextEdit_klient->setReadOnly(true);

    ui->label_zapytanie->setText(tr("Zapytanie:"));
    ui->pushButton_zapytanieData->setText(tr("Kalendarz"));
    ui->checkBox_zapytanieData->setText(tr("Data zapytania:"));
    ui->checkBox_zapytanieData->setChecked(true);
    ui->checkBox_zapytanieNr->setText(tr("Numer zapytania:"));
    ui->checkBox_zapytanieNr->setChecked(false);
    ui->plainTextEdit_zapytanie->setReadOnly(true);

    m_shippingOptions = LocalDatabase::instance()->optionsList(optShipping);
    ui->comboBox_dostawa->insertItems(0, m_shippingOptions.keys());
    ui->plainTextEdit_dostawa->setReadOnly(true);
    ui->label_dostawa->setText(tr("Warunki dostawy:"));

    m_deliveryOptions = LocalDatabase::instance()->optionsList(optDelivery);
    ui->comboBox_termin->insertItems(0, m_deliveryOptions.keys());
    ui->plainTextEdit_termin->setReadOnly(true);
    ui->label_termin->setText(tr("Termin dostawy:"));

    m_paymentOptions = LocalDatabase::instance()->optionsList(optPayment);
    ui->comboBox_platnosc->insertItems(0, m_paymentOptions.keys());
    ui->plainTextEdit_platnosc->setReadOnly(true);
    ui->label_platnosc->setText(tr("Warunki płatności:"));

    m_offerOptions = LocalDatabase::instance()->optionsList(optOffer);
    ui->comboBox_oferta->insertItems(0, m_offerOptions.keys());
    ui->plainTextEdit_oferta->setReadOnly(true);
    ui->label_oferta->setText(tr("Warunki Oferty:"));

    m_towarModel = new TowarModel;
    ui->tableView->setModel(m_towarModel);
    m_towarDelegate = new TowarDelegate(this);
    ui->tableView->setItemDelegate(m_towarDelegate);
    //------------------ co z tym: ??? --------------
    ui->tableView->setDragDropMode(QAbstractItemView::InternalMove);

    ui->label_uwagi->setText(tr("Uwagi:"));
    ui->kursSpinBox->setEnabled(false);

    /**
     connections
    **/
    qDebug() << "połaczenia sygnałów i slotów";

    /*menu:*/
    //plik
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(nowa()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(popLoadDialog()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(zapisz()));
    connect(ui->actionNR, SIGNAL(triggered()), this, SLOT(nowyNumer()));
    connect(ui->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
    //klient
    connect(ui->klientNowy, SIGNAL(triggered()), this, SLOT(dodajKlient()));
    connect(ui->klientEdycja, SIGNAL(triggered()), this, SLOT(edytujKlient()));
    //towar
    connect(ui->towarNowy, SIGNAL(triggered()), this, SLOT(dodajTowar()));
    connect(ui->towarEdycja, SIGNAL(triggered()), this, SLOT(edytujTowar()));
    //export
    connect(ui->actionDo_HTML, SIGNAL(triggered()), this, SLOT(zapisz()));
    connect(ui->actionDo_HTML, SIGNAL(triggered()), this, SLOT(printHtm()));
    connect(ui->actionDo_PDF, SIGNAL(triggered()), this, SLOT(zapisz()));
    connect(ui->actionDo_PDF, SIGNAL(triggered()), this, SLOT(printPdf()));
    connect(ui->actionDruk, SIGNAL(triggered()), this, SLOT(zapisz()));
    connect(ui->actionDruk, SIGNAL(triggered()), this, SLOT(printPrev()));
    //info:
    connect(ui->actionO_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->actionO_kOferta, SIGNAL(triggered()), this, SLOT(about()));

    //opcje wydruku
    connect(ui->pln, SIGNAL(pressed()), this, SLOT(pln_on()));
    connect(ui->eur, SIGNAL(pressed()), this, SLOT(pln_off()));
    connect(ui->kursSpinBox, SIGNAL(valueChanged(double)), m_towarModel, SLOT(setKurs(double)));

    //buttony w tabach
    connect(ui->addTowar, SIGNAL(clicked()), this, SLOT(popWyborTowaru()));
    connect(ui->rabat, SIGNAL(clicked()), this, SLOT(rabat()));
    connect(ui->delw, SIGNAL(clicked()), this, SLOT(del()));

    //Pozostałe informacje - odświerzanie zawartości pól tekstowych
    connect(ui->pushButton_wyborKlienta, SIGNAL(clicked()), this, SLOT(popWyborKlienta()));
    connect(ui->comboBox_dostawa, SIGNAL(currentIndexChanged(QString)), this, SLOT(dostawaRef(QString)));
    connect(ui->comboBox_oferta, SIGNAL(currentIndexChanged(QString)), this, SLOT(ofertaRef(QString)));
    connect(ui->comboBox_platnosc, SIGNAL(currentIndexChanged(QString)), this, SLOT(platnoscRef(QString)));
    connect(ui->comboBox_termin, SIGNAL(currentIndexChanged(QString)), this, SLOT(terminRef(QString)));
    connect(calendarWidget, SIGNAL(clicked(QDate)), this, SLOT(calChanged(QDate)));
    connect(ui->pushButton_zapytanieData, SIGNAL(clicked()), calendarWidget, SLOT(show()));
    connect(ui->lineEdit_zapytanieData, SIGNAL(textChanged(QString)), this, SLOT(zapytanieRef()));
    connect(ui->lineEdit_zapytanieNr, SIGNAL(textChanged(QString)), this, SLOT(zapytanieRef()));
    connect(ui->checkBox_zapytanieData, SIGNAL(toggled(bool)), this, SLOT(checkData(bool)));
    connect(ui->checkBox_zapytanieNr, SIGNAL(toggled(bool)), this, SLOT(checkNr(bool)));

}

void MainWindow::about()
{
    QString s;
    s = "System wspomagający ofertowanie kOferta v. ";
    s += QString::number(VER);
    s += "\n"
         "Głównym elementem systemu jest aplikacja kliencka stanowiąca front-end dla danych znajdujących się w bazie danych. "
         "Baza ta przechowuje nie tylko dane klientów i towarów przedsiębiorstwa, ale także utworzone do tej pory oferty. "
         "Aplikacja kliencka ma także możliwość edycji bazy danych.\n\n"
         "\t\tLicencja:\n"
         "kOferta - system usprawniajacy proces ofertowania\n"
         "Copyright (C) 2011  Kamil 'konserw' Strzempowicz, konserw@gmail.com\n"
         "\n"
         "This program is free software: you can redistribute it and/or modify "
         "it under the terms of the GNU General Public License as published by "
         "the Free Software Foundation, either version 3 of the License, or "
         "(at your option) any later version.\n"
         "\n"
         "This program is distributed in the hope that it will be useful, "
         "but WITHOUT ANY WARRANTY; without even the implied warranty of "
         "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the "
         "GNU General Public License for more details.\n"
         "\n"
         "You should have received a copy of the GNU General Public License "
         "along with this program.  If not, see http://www.gnu.org/licenses/.\n"
         "\n"
         "W programie wykorzystano klasę implementującą szyfrowanie SHA1 "
         "autorstwa Michael D. Leonhard na warunkach licencyjnych opisanych w pliku SHA1_LICENSE\n"
         "\n\n\t\t\tBuild date: " __DATE__;
    QMessageBox::about(this, "O kOferta", s);
}

void MainWindow::setTitle(QString* nr)
{
    QString s = "kOferta v. ";
    s += QString::number(VER);

    if(nr != NULL)
    {
        s += " | oferta nr: ";
        s += *nr;
    }

    this->setWindowTitle(s);
}

void MainWindow::rabat()
{
    bool ok;
    double d = QInputDialog::getDouble(this, "Rabat", "Podaj domyślny rabat [%]:", 0, 0, 100, 2, &ok);
    if(ok)
        m_towarModel->setGlobalRabat(d);
}

void MainWindow::del()
{
    m_towarModel->removeRow(ui->tableView->currentIndex().row());
}

void MainWindow::dostawaRef(QString row)
{
    ui->plainTextEdit_dostawa->setPlainText(m_shippingOptions[row]);
}

void MainWindow::platnoscRef(QString row)
{
    ui->plainTextEdit_platnosc->setPlainText(m_paymentOptions[row]);
}

void MainWindow::terminRef(QString row)
{
    ui->plainTextEdit_termin->setPlainText(m_deliveryOptions[row]);
}

void MainWindow::ofertaRef(QString row)
{
    ui->plainTextEdit_oferta->setPlainText(m_offerOptions[row]);
}

void MainWindow::calChanged(const QDate &d)
{
    ui->lineEdit_zapytanieData->setText(d.toString("dd.MM.yyyy"));
    calendarWidget->close();
    ui->checkBox_zapytanieData->setChecked(true);
}

void MainWindow::zapytanieRef()
{
    QString s;
    s = "W odpowiedzi na zapytanie";
    if(ui->checkBox_zapytanieNr->isChecked())
    {
        s += " numer ";
        s += ui->lineEdit_zapytanieNr->text();
    }
    if(ui->checkBox_zapytanieData->isChecked())
    {
        s += " z dnia ";
        s += ui->lineEdit_zapytanieData->text();
    }

    s += " przedstawiamy ofertę na dostawę następujących produktów:";
    ui->plainTextEdit_zapytanie->setPlainText(s);
}

void MainWindow::checkNr(bool ch)
{
    ui->lineEdit_zapytanieNr->setEnabled(ch);
    if(!ch)
        ui->lineEdit_zapytanieNr->clear();
    this->zapytanieRef();
}

void MainWindow::checkData(bool ch)
{
    ui->lineEdit_zapytanieData->setEnabled(ch);
    if(!ch)
        ui->lineEdit_zapytanieData->clear();
    this->zapytanieRef();
}

void MainWindow::popWyborKlienta()
{
    WyborKlienta* pop = new WyborKlienta(this);
    connect(pop, SIGNAL(selectionChanged(QSqlRecord)), this, SLOT(clientChanged(QSqlRecord)));
    pop->exec();
    delete pop;
}

void MainWindow::popWyborTowaru()
{
    WyborTowaru* pop = new WyborTowaru(this);
    connect(pop, SIGNAL(itemSelected(QString)), m_towarModel, SLOT(ileTowaru(QString)));
    connect(m_towarModel, SIGNAL(iloscTowaru(int)), pop, SLOT(setItemCount(int)));
    connect(pop, SIGNAL(countChanged(QSqlRecord,int)), m_towarModel, SLOT(changeItemCount(QSqlRecord,int)));
    pop->showMaximized();
    pop->exec();
    delete pop;
}

void MainWindow::clientChanged(const QSqlRecord& rec)
{
    delete klient;
    if(rec.isEmpty())
    {
        klient = NULL;
        ui->plainTextEdit_klient->clear();
    }
    else
    {
        klient = new QSqlRecord(rec);
        QString s;
        s = rec.value("tytul").toString();
        s += " ";
        s += rec.value("nazwisko").toString();
        s += "\n";
        s += rec.value("full").toString();
        ui->plainTextEdit_klient->setPlainText(s);
    }
}

void MainWindow::pln_on()
{
    ui->kursSpinBox->setEnabled(true);
    ui->kurs_label->setEnabled(true);
    m_towarModel->setKurs(ui->kursSpinBox->value());
}

void MainWindow::pln_off()
{
    ui->kursSpinBox->setEnabled(false);
    ui->kurs_label->setEnabled(false);
    m_towarModel->setKurs(0);
}

/*************************
**      OFERTA          **
*************************/

void MainWindow::nowyNumer()
{
    QDate d = QDate::currentDate();
    *data = d.toString("dd.MM.yyyy");
    calendarWidget->setSelectedDate(d);
/*
    *nr_oferty = QString::number(currentUser->nrOferty());
    nr_oferty->append("/");
    nr_oferty->append(d.toString("yyyy"));
*/
    LocalDatabase::instance()->setCurrentUser(m_curUser);
    *nr_oferty = LocalDatabase::instance()->userOfferId();
    this->setTitle(nr_oferty);
}

void MainWindow::nowa()
{
    //czyszczenie starych danych
    clientChanged(QSqlRecord());

    this->nowyNumer();

    if(ui->tab->isEnabled()==false)
        this->init();
    else
        m_towarModel->clear();
}

void MainWindow::init()
{
    //włączenie zablokowanych części
    ui->tab->setEnabled(true);
    ui->tab_2->setEnabled(true);

    ui->menuExport->setEnabled(true);
    ui->actionSave->setEnabled(true);
    ui->actionNR->setEnabled(true);

    //inicjacja tabelki
    m_towarModel->clear();
    for(int i=0; i < m_towarModel->columnCount(); i++)
        ui->tableView->setColumnWidth(i, 85);
    ui->tableView->setColumnWidth(1, 410);
    ui->tableView->setColumnWidth(0, 99);
  //  ui->tableView->setSortingEnabled(true);
}

void MainWindow::zapisz()
{
    /*
    QString s;

    if(klient == NULL)
    {
        QMessageBox::warning(this, "brak danych", "Aby zapisanie oferty w bazie danych było możliwe należy wybrać klienta.");
        return;
    }

    int anr = nr_oferty->split("/").first().toInt();

    if(anr == currentUser->nrOferty())
        currentUser->nrOfertyInkrement();

    QString zData;
    if(ui->checkBox_zapytanieData->isChecked())
        zData = ui->lineEdit_zapytanieData->text();
    else zData = QString::null;

    QString zNumer;
    if(ui->checkBox_zapytanieNr->isChecked())
        zNumer =  ui->lineEdit_zapytanieNr->text();
    else
        zNumer = QString::null;

    insert_zapisane(*nr_oferty, klient->value("id").toInt(), *data, currentUser->uid(), zData, zNumer, ui->comboBox_dostawa->currentIndex(), ui->comboBox_termin->currentIndex(), ui->comboBox_platnosc->currentIndex(), ui->comboBox_oferta->currentIndex(), ui->plainTextEdit_uwagi->toPlainText());

    for(int i=0; i < ui->tableWidget->rowCount() - 1; ++i)
        insert_zapisane_towary(*nr_oferty, ui->tableWidget->item(i, 0)->text(), ui->tableWidget->item(i, 5)->text().toDouble(), ui->tableWidget->item(i, 3)->text().toDouble());
*/
    //------------------ zapisywanie! ---------------
}

void MainWindow::popLoadDialog()
{
    LoadDialog* pop = new LoadDialog(this);
    connect(pop, SIGNAL(offerSelected(QSqlRecord, QSqlTableModel)), this, SLOT(loadOffer(QSqlRecord, QSqlTableModel)));
    pop->exec();
    delete pop;
}
void MainWindow::loadOffer(const QSqlRecord& rec, const QSqlTableModel& mod)
{
    *nr_oferty = rec.value("nr_oferty").toString();
    *data = rec.value("data").toString();

    this->init();
    this->setTitle(nr_oferty);

    QSqlQueryModel klientModel;
    klientModel.setQuery(QString("SELECT DISTINCT klient.* FROM klient, zapisane WHERE klient.id = zapisane.id_klienta AND zapisane.nr_oferty = '%1'").arg(rec.value("nr_oferty").toString()));
    clientChanged(klientModel.record(0));

    if(rec.value("zapytanie_data").isNull())
        ui->checkBox_zapytanieData->setChecked(false);
    else
    {
        ui->checkBox_zapytanieData->setChecked(true);
        ui->lineEdit_zapytanieData->setText(rec.value("zapytanie_data").toString());
    }
    if(rec.value("zapytanie_nr").isNull())
        ui->checkBox_zapytanieNr->setChecked(false);
    else
    {
        ui->checkBox_zapytanieNr->setChecked(true);
        ui->lineEdit_zapytanieNr->setText(rec.value("zapytanie_nr").toString());
    }

    ui->comboBox_dostawa->setCurrentIndex(rec.value("dostawa").toInt());
    ui->comboBox_termin->setCurrentIndex(rec.value("termin").toInt());
    ui->comboBox_platnosc->setCurrentIndex(rec.value("platnosc").toInt());
    ui->comboBox_oferta->setCurrentIndex(rec.value("platnosc").toInt());
    ui->plainTextEdit_uwagi->setPlainText(rec.value("uwagi").toString());

    m_towarModel->loadOffer(mod);
}

/*************************
**      WYDRUK          **
*************************/

void MainWindow::printPrev()
{
    htm = false;

    QPrinter* printer = new QPrinter;
    printer->setOutputFormat(QPrinter::NativeFormat);

    QPrintPreviewDialog* preview = new QPrintPreviewDialog(printer, this);
    preview->setWindowFlags(Qt::Window);
    connect(preview, SIGNAL(paintRequested(QPrinter *)), SLOT(print(QPrinter *)));
    preview->exec();

    delete preview;
    delete printer;
}

void MainWindow::printPdf()
{
    QString s;
    s = QFileDialog::getSaveFileName(this, "Zapis pdfa", "", "Dokument PDF (*.pdf)");
    if(s.isEmpty())return;

    QPrinter* printer = new QPrinter;
    printer->setOutputFormat(QPrinter::PdfFormat);
    printer->setOutputFileName(s);

    htm = false;
    print(printer);

    delete printer;
}

void MainWindow::printHtm()
{
    QString s;
    s = QFileDialog::getSaveFileName(this, "Zapis do HTML", "", "Dokument HTML (*.htm)");
    if(s.isEmpty())return;

    QFile file(s);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "plik " << s << " niedostępny";
        QMessageBox::warning(NULL, "error", "Nie udało się uzyskać dostępu do pliku");
        return;
    }

    htm = true;
    QString* sDoc = new QString;
    makeDocument(sDoc);

    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << *sDoc;

    delete sDoc;
}

void MainWindow::print(QPrinter *printer)
{
    const int margin = 5;                        //szerokość marginesu
    printer->setPaperSize(QPrinter::A4);
    printer->setResolution(300);
    printer->setPageMargins(margin, margin, margin, margin, QPrinter::Millimeter);

    htm = false;
    QString* sDoc = new QString;
    makeDocument(sDoc);

    QFont* font = new QFont;
    font->setPointSize(10);
    font->setFamily("Arial");

    QTextDocument* doc = new QTextDocument;
    doc->setDefaultFont(*font);
    doc->setHtml(*sDoc);
    doc->print(printer);

    delete doc;
    delete font;
    delete sDoc;
}

void MainWindow::makeDocument(QString *sDoc)
{
 #ifdef xxx
    if(klient == NULL)
        klient = new QSqlRecord;

    int kolumn = 3;
    QString waluta;
    uint rows = ui->tableWidget->rowCount()-1;

    const int w = 745;                           //szerokosc szkieletu dokumentu
    const int d = (w-5)/2;                       //szerokość kolumny w szkielecie
    const int dw = 140;                          //szerokosc pierwszej kolumny w szkielecie poniżej tabeli
    int z[8];                                    //szerokosc komorek tabeli
    z[0] = 20; //lp
    z[1] = 80; //kod
    //z2 - reszta szerokości
    z[3] = 60; //cena
    z[4] = 40; //rabat
    z[5] = 55; //cena2
    z[6] = 50; //ilosc+jedn
    z[7] = 60; //wartość

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
    *sDoc += ">\n"
             "\t\t\tNumer oferty: <font size=4>";
    *sDoc += *nr_oferty;
    *sDoc += "</font><br>\n"
             "\t\t\tData oferty: ";
    *sDoc += *data;
    *sDoc += "\n"
             "\t\t\t<hr width=100%>\n"
             "\t\t\tDla:<br>\n"
             "\t\t\t";
    *sDoc += klient->value("full").toString();
    *sDoc += "<br>\n"
             "\t\t\t";
    *sDoc += klient->value("adres").toString();
    *sDoc += "<br>\n"
             "\t\t\t";
    *sDoc += klient->value("tytul").toString();
    *sDoc += " ";
    *sDoc += klient->value("imie").toString();
    *sDoc += " ";
    *sDoc += klient->value("nazwisko").toString();
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

    *sDoc += "\t\t\t<b>Marley Polska Sp. z o.o.</b><br>\n"
             "\t\t\tul. Annopol 24<br>\n"
             "\t\t\t03-236 Warszawa<br>\n"
             "\t\t\t<br>\n"
             "\t\t\t";
    /*adres bióra*/
    *sDoc += currentUser->adress().replace("\n", "\n\t\t\t");
    *sDoc += currentUser->mail();
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
            *sDoc += QString::number(ui->tableWidget->item(i, 3)->text().toDouble(), 'f', 1);
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
    *sDoc += ui->plainTextEdit_uwagi->toPlainText().replace("\n", "<br />\n");
    *sDoc += "</td>\n"
             "\t</tr>\n"
             "\t</table>\n"
             "</td></tr>\n";
//Pozdrowienia
    *sDoc += "<tr><td>\n"
             "\t";
    *sDoc += ui->plainTextEdit_oferta->toPlainText();
    *sDoc += "<br>\n"
             "\tŁączymy pozdrowienia.\n"
             "\t<p align = right style = \"margin-right: 100\">\n"
             "\t\tOfertę przygotował";
    if(!currentUser->male()) *sDoc += "a";
    *sDoc += "<br>\n"
            "\t\t";
    *sDoc += currentUser->name();
    *sDoc += "\n"
            "\t</p>\n"
            "</td></tr>\n"
            "</tbody>\n"
            "</table>\n"
            "</body>\n"
            "</html>\n";
#endif
}
