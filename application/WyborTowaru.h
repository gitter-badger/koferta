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

#ifndef WYBORTOWARU_H
#define WYBORTOWARU_H

#include <QDialog>

class QSqlRecord;

namespace Ui {
class WyborTowaru;
}

class WyborTowaru : public QDialog
{
    Q_OBJECT
    
public:
    explicit WyborTowaru(QWidget *parent = 0);
    ~WyborTowaru();

public slots:
    void refresh(const QSqlRecord &);
    void spin(int);
    void setItemCount(int amount);

signals:
    void countChanged(const QSqlRecord &, int);
    void itemSelected(QString kod);
    
private:
    Ui::WyborTowaru *ui;
    QSqlRecord* rec;
    static const QString m_info;
};

#endif // WYBORTOWARU_H