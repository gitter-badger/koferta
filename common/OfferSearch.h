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
       
#ifndef SZUKAJOFERTY_H
#define SZUKAJOFERTY_H

#include <QWidget>
#include <QHash>

class QSqlRelationalTableModel;
class QModelIndex;
class QDate;
class QSqlRecord;

namespace Ui {
    class OfferSearch;
}

class OfferSearch : public QWidget
{
    Q_OBJECT
    
public:
    explicit OfferSearch(QWidget *parent = 0);
    ~OfferSearch();

public slots:
    void select(const QModelIndex &);
    void refId(const QString&);
    void refClient(const QString &);
    void refDate(const QDate&);
    void refUser(const QString &);

signals:
    void selectionChanged(const QSqlRecord&);

private:
    QSqlRelationalTableModel* model;
    Ui::OfferSearch *ui;

    QHash<int, QString> m_names;
};

#endif // SZUKAJOFERTY_H
