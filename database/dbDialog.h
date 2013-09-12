#ifndef DBDIALOG_H
#define DBDIALOG_H

#include <QDialog>

namespace Ui {
class dbDialog;
}

class dbDialog : public QDialog
{
    Q_OBJECT

public:
    explicit dbDialog(QWidget *parent = 0);
    ~dbDialog();

public slots:
    //klient
    void dodajKlient();                                 //wyświetla dialog dodający klienta - cDodajKlient
 //   void edytujKlient();                                //wyświetla dialog edycji klientów

    //towar
    void dodajTowar();                                  //wyświetlenie dialogu  dodającego towar - cDodajTowar
  //  void edytujTowar();                                 //wyświetla dialog edycji towarów

private:
    Ui::dbDialog *ui;
};

#endif // DBDIALOG_H
