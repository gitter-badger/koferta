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

#include "MerchandiseListView.h"
#include "MerchandiseListDelegate.h"
#include "MerchandiseListModel.h"
#include <QtPrintSupport>

MerchandiseListView::MerchandiseListView(QWidget *parent) :
    QTableView(parent)
{
    setItemDelegate(new MerchandiseListDelegate(this));
    setDragDropMode(QAbstractItemView::InternalMove);
    setDropIndicatorShown(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setAcceptDrops(true);

    setSortingEnabled(true);
    this->horizontalHeader()->setSortIndicatorShown(false);
}

void MerchandiseListView::dragEnterEvent(QDragEnterEvent *event)
 {
    if(event->source() == this)
        event->acceptProposedAction();
}

void MerchandiseListView::dropEvent(QDropEvent *event)
{
    QModelIndex indexFrom = indexAt(dragStartPosition);
    QModelIndex indexTo = indexAt(event->pos());

    dynamic_cast<MerchandiseListModel*>(this->model())->moveRow(QModelIndex(), indexFrom.row(), QModelIndex(), indexTo.row());

    event->acceptProposedAction();
}

void MerchandiseListView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        dragStartPosition = event->pos();

    QTableView::mousePressEvent(event);
}
