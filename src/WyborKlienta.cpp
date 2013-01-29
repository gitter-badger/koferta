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

#include "WyborKlienta.h"
#include "ui_WyborKlienta.h"

#include <QSqlQuery>
#include "Macros.h"


cWyborKlienta::cWyborKlienta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WyborKlienta)
{
    ui->setupUi(this);

    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->ok, SIGNAL(clicked()), this, SLOT(ok()));
}

cWyborKlienta::~cWyborKlienta()
{
    delete ui;
}

void cWyborKlienta::ok()
{
    int r = ui->widget->selectedClient();
    if (r != -1)
    {
        emit id_klienta(r);
        this->close();
    }
}

