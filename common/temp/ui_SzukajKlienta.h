/********************************************************************************
** Form generated from reading UI file 'SzukajKlienta.ui'
**
** Created: Sun Sep 8 20:20:59 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SZUKAJKLIENTA_H
#define UI_SZUKAJKLIENTA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SzukajKlienta
{
public:
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton_nazwa;
    QRadioButton *radioButton_nazwisko;
    QLineEdit *lineEdit;
    QTableView *tableView;

    void setupUi(QWidget *SzukajKlienta)
    {
        if (SzukajKlienta->objectName().isEmpty())
            SzukajKlienta->setObjectName(QString::fromUtf8("SzukajKlienta"));
        SzukajKlienta->resize(301, 393);
        verticalLayout = new QVBoxLayout(SzukajKlienta);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        radioButton_nazwa = new QRadioButton(SzukajKlienta);
        radioButton_nazwa->setObjectName(QString::fromUtf8("radioButton_nazwa"));

        verticalLayout->addWidget(radioButton_nazwa);

        radioButton_nazwisko = new QRadioButton(SzukajKlienta);
        radioButton_nazwisko->setObjectName(QString::fromUtf8("radioButton_nazwisko"));

        verticalLayout->addWidget(radioButton_nazwisko);

        lineEdit = new QLineEdit(SzukajKlienta);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        tableView = new QTableView(SzukajKlienta);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);


        retranslateUi(SzukajKlienta);

        QMetaObject::connectSlotsByName(SzukajKlienta);
    } // setupUi

    void retranslateUi(QWidget *SzukajKlienta)
    {
        SzukajKlienta->setWindowTitle(QApplication::translate("SzukajKlienta", "Form", 0, QApplication::UnicodeUTF8));
        radioButton_nazwa->setText(QApplication::translate("SzukajKlienta", "RadioButton", 0, QApplication::UnicodeUTF8));
        radioButton_nazwisko->setText(QApplication::translate("SzukajKlienta", "RadioButton", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SzukajKlienta: public Ui_SzukajKlienta {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SZUKAJKLIENTA_H
