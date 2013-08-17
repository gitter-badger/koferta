#include "Towar.h"

Towar::Towar(QObject *parent) :
    QObject(parent)
{

}

QString Towar::kod() const
{
    return m_kod;
}

void Towar::setKod(const QString &kod)
{
    m_kod = kod;
}

QString Towar::nazwa() const
{
    return m_nazwa;
}

void Towar::setNazwa(const QString &nazwa)
{
    m_nazwa = nazwa;
}

double Towar::cenaKat() const
{
    return m_cenaKat;
}

void Towar::setCenaKat(double cenaKat)
{
    m_cenaKat = cenaKat;
}

double Towar::rabat() const
{
    return m_rabat;
}

void Towar::setRabat(double rabat)
{
    m_rabat = rabat;
}

double Towar::ilosc() const
{
    return m_ilosc;
}

void Towar::setIlosc(double ilosc)
{
    m_ilosc = ilosc;
}

bool Towar::metr() const
{
    return m_metr;
}

void Towar::setMetr(bool metr)
{
    m_metr = metr;
}

double Towar::cena() const
{
    return m_cenaKat * (100 - m_rabat) /100;
}

double Towar::wartosc() const
{
    return m_ilosc * cena();
}

double Towar::cena(double kurs) const
{
    return kurs * m_cenaKat * (100 - m_rabat) /100;
}

double Towar::wartosc(double kurs) const
{
    return m_ilosc * cena(kurs);
}

