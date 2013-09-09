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
