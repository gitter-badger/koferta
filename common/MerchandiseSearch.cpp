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

#include <QSqlTableModel>
#include <QSqlRecord>
#include <QTableView>
#include <QHeaderView>
#include "MerchandiseSearchModel.h"
#include "MerchandiseSearch.h"
#include "ui_MerchandiseSearch.h"

MerchandiseSearch::MerchandiseSearch(MerchandiseSearchModel* model, QWidget *parent) :
    QDialog(parent),
    m_model(model),
    ui(new Ui::MerchandiseSearch)
{
    ui->setupUi(this);

    ui->label->setText(tr("Filtr:"));
    ui->radioButton_id->setText(tr("Id produktu"));
    ui->radioButton_id->setChecked(true);
    ui->radioButton_name->setText(tr("Nazwa produktu"));
/*
    localDatabase()->merchandiseModel()->setFilter("");

    ui->tableView->setModel(localDatabase()->merchandiseModel());

    ui->tableView->hideColumn(2);
    ui->tableView->hideColumn(3);

    ui->tableView->setSortingEnabled(true);

    ui->tableView->resizeColumnToContents(0);
 //   ui->tableView->resizeColumnToContents(1);


    QHeaderView* hdr = ui->tableView->horizontalHeader();
 //   hdr->setResizeMode(0, QHeaderView::ResizeToContents);
    hdr->setSectionResizeMode(1, QHeaderView::Stretch);
*/
    m_model->setFilter("");
    ui->tableView->setModel(m_model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);//:NoEditTriggers);

    connect(ui->radioButton_id, SIGNAL(clicked()), this, SLOT(ref2()));
    connect(ui->radioButton_name, SIGNAL(clicked()), this, SLOT(ref2()));
    connect(ui->lineEdit, SIGNAL(textEdited(QString)), this, SLOT(ref(QString)));
    connect(ui->pushButton_close, &QPushButton::clicked, this, &MerchandiseSearch::close);
/*
    QItemSelectionModel *sm = ui->tableView->selectionModel();
    connect(sm, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(currentRowChanged(QModelIndex,QModelIndex)));
    connect(ui->tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(select(QModelIndex)));
*/
}

MerchandiseSearch::~MerchandiseSearch()
{
    delete ui;
  //  delete m_model;
}
/*
void SzukajTowaru::select(const QModelIndex& idx)
{
    QSqlRecord r = m_model->record(idx.row());
    if(!r.isEmpty())
        emit selectionChanged(r);
}
*/
void MerchandiseSearch::ref2()
{
    ref(ui->lineEdit->text());
}

void MerchandiseSearch::ref(const QString & in)
{/*
    QString s;
    if(ui->radioButton_id->isChecked())
        s = "id like '";
    else
        s = "nazwa like '";
    s += in;
    s += "%'";
    */
    m_model->setFilter(QString("%1 like '%2%'").arg(ui->radioButton_id->isChecked() ? "id" : "nazwa").arg(in));
}
/*
void SzukajTowaru::currentRowChanged(const QModelIndex &cur, const QModelIndex &prev)
{
    Q_UNUSED(prev);
    select(cur);
}
*/
