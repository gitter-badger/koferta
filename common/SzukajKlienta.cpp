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
#include "SzukajKlienta.h"
#include "ui_SzukajKlienta.h"
#include <QSqlTableModel>
#include <QSqlRecord>

SzukajKlienta::SzukajKlienta(QSqlTableModel *model, QWidget *parent) :
    QWidget(parent),
    m_model(model),
    ui(new Ui::SzukajKlienta)
{
    ui->setupUi(this);

    ui->radioButton_nazwa->setText(tr("Filtruj po nazwie"));
    ui->radioButton_nazwa->setChecked(true);
    ui->radioButton_nazwisko->setText(tr("Filtruj po nazwisku"));

    m_model->setFilter("");

    ui->tableView->setModel(m_model);
    ui->tableView->hideColumn(0);
    for(int i=2; i<5; ++i)
        ui->tableView->hideColumn(i);
    ui->tableView->hideColumn(6);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->resizeColumnToContents(3);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->lineEdit, SIGNAL(textEdited(QString)), this, SLOT(ref(const QString&)));
    connect(ui->radioButton_nazwa, SIGNAL(clicked()), this, SLOT(ref2()));
    connect(ui->radioButton_nazwisko, SIGNAL(clicked()), this, SLOT(ref2()));
    connect(ui->tableView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(selectionChanged(const QModelIndex&)));
}

SzukajKlienta::~SzukajKlienta()
{
    delete ui;
}

void SzukajKlienta::ref2()
{
    ref(ui->lineEdit->text());
}

void SzukajKlienta::ref(const QString& in)
{
    QString s;
    if(ui->radioButton_nazwa->isChecked())
        s = "short like '";
    else
        s = "nazwisko like '";
    s += in;
    s += "%'";
    m_model->setFilter(s);
}
