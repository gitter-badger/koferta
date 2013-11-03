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
#include "ui_SzukajTowaru.h"
#include "WyborTowaru.h"
#include "WyborTowaruModel.h"
#include "MerchendiseSelectionDelegate.h"
#include "LocalDatabase.h"
#include <QSqlRecord>
#include <QSqlTableModel>

WyborTowaru::WyborTowaru(const QHash<int, double> &hash, QWidget *parent) :
    SzukajTowaru(new WyborTowaruModel(hash, parent), parent)
{
    m_merchandiseModel = localDatabase()->merchandiseModel();
    m_model->setSourceModel(m_merchandiseModel);
    MerchendiseSelectionDelegate* delegate = new MerchendiseSelectionDelegate(this);
    ui->tableView->setItemDelegate(delegate);

    connect(delegate, &MerchendiseSelectionDelegate::itemCountChanged, this, &WyborTowaru::itemCountChanged);
}

WyborTowaru::~WyborTowaru()
{

}
