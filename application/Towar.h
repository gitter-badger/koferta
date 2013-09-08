#ifndef TOWAR_H
#define TOWAR_H

#include <QString>

class QSqlRecord;

/*!
 * \brief Klasa reprezentująca towar w ofercie
 */
class Towar
{
public:
    explicit Towar();
    Towar(const QSqlRecord& rec);

    double cenaPln(double kurs) const;
    
    QString kod() const;
    void setKod(const QString &kod);

    QString nazwa() const;
    void setNazwa(const QString &nazwa);

    double cenaKat() const;
    void setCenaKat(double cenaKat);

    double rabat() const;
    void setRabat(double rabat);

    double ilosc() const;
    void setIlosc(double ilosc);

    bool metr() const;
    void setMetr(bool metr);

    double cena() const;
    double wartosc() const;

    double cena(double kurs) const;
    double wartosc(double kurs) const;

protected:
    QString m_kod;
    QString m_nazwa;
    double  m_cenaKat;
    bool    m_metr;

    double  m_rabat;
    double  m_ilosc;    
};

#endif // TOWAR_H
