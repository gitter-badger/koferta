/********************************************************************************
** Form generated from reading UI file 'SzukajTowaru.ui'
**
** Created: Sun Sep 8 20:20:59 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SZUKAJTOWARU_H
#define UI_SZUKAJTOWARU_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SzukajTowaru
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QRadioButton *radioButton_id;
    QRadioButton *radioButton_name;
    QLineEdit *lineEdit;
    QTableView *tableView;

    void setupUi(QWidget *SzukajTowaru)
    {
        if (SzukajTowaru->objectName().isEmpty())
            SzukajTowaru->setObjectName(QString::fromUtf8("SzukajTowaru"));
        SzukajTowaru->resize(455, 420);
        verticalLayout = new QVBoxLayout(SzukajTowaru);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(SzukajTowaru);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        radioButton_id = new QRadioButton(SzukajTowaru);
        radioButton_id->setObjectName(QString::fromUtf8("radioButton_id"));
        radioButton_id->setChecked(true);

        horizontalLayout->addWidget(radioButton_id);

        radioButton_name = new QRadioButton(SzukajTowaru);
        radioButton_name->setObjectName(QString::fromUtf8("radioButton_name"));

        horizontalLayout->addWidget(radioButton_name);


        verticalLayout->addLayout(horizontalLayout);

        lineEdit = new QLineEdit(SzukajTowaru);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        tableView = new QTableView(SzukajTowaru);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);


        retranslateUi(SzukajTowaru);

        QMetaObject::connectSlotsByName(SzukajTowaru);
    } // setupUi

    void retranslateUi(QWidget *SzukajTowaru)
    {
        SzukajTowaru->setWindowTitle(QApplication::translate("SzukajTowaru", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SzukajTowaru", "TextLabel", 0, QApplication::UnicodeUTF8));
        radioButton_id->setText(QApplication::translate("SzukajTowaru", "Id", 0, QApplication::UnicodeUTF8));
        radioButton_name->setText(QApplication::translate("SzukajTowaru", "Nazwa", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SzukajTowaru: public Ui_SzukajTowaru {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SZUKAJTOWARU_H
