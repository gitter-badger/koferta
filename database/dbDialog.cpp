#include "dbDialog.h"
#include "ui_dbDialog.h"
#include "LocalDatabase.h"
#include "NowyTowar.h"
#include "NowyKlient.h"

dbDialog::dbDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dbDialog)
{
    ui->setupUi(this);

    ui->tab->setWindowTitle(tr("Towar"));
    ui->tab_2->setWindowTitle(tr("Klient"));

//    ui->merch_tableView->setModel(); <-- foreign database!

    connect(ui->merch_add, SIGNAL(clicked()), this, SLOT(dodajTowar()));
    connect(ui->customer_add, SIGNAL(clicked()), this, SLOT(dodajKlient()));

/*
    //dodawanie opcji do kombosów
    connect(ui->pushButton_dostawa, SIGNAL(clicked()), this, SLOT(dostawaNew()));
    connect(ui->pushButton_oferta, SIGNAL(clicked()), this, SLOT(ofertaNew()));
    connect(ui->pushButton_platnosc, SIGNAL(clicked()), this, SLOT(platnoscNew()));
    connect(ui->pushButton_termin, SIGNAL(clicked()), this, SLOT(terminNew()));
*/
}

dbDialog::~dbDialog()
{
    delete ui;
}

/* TOWAR */

void dbDialog::dodajTowar()
{
    NowyTowar* nowyTowar = new NowyTowar(this);
    nowyTowar->exec();
    delete nowyTowar;
}
/*
void dbDialog::edytujTowar()
{
    EdycjaTowaru* okno = new EdycjaTowaru(this);
    okno->exec();
    delete okno;
}
*/

/* KLIENT */

void dbDialog::dodajKlient()
{
    NowyKlient* nowyKlient = new NowyKlient(this);
    nowyKlient->exec();
    delete nowyKlient;
}
/*
void dbDialog::edytujKlient()
{
    EdycjaKlienta* okno = new EdycjaKlienta(this);
    okno->exec();
    delete okno;
}
*/
