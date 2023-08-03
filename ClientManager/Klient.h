#pragma once
#include "Osoba.h"
#include <iostream>


using std::ostream;

class Klient: public Osoba
{
private:
	int waga;
	int wzrost;
	double bmi;

public:
	Klient() = default;
	Klient(string tp, string im, string naz, int wg, int wz) : Osoba(tp, im, naz), waga(wg), wzrost(wz), bmi(ObliczBmi(wg,wz)) {};
	void WyswietlDane(int odstep, int wersja = 1) override;

	void setWaga(const int w);
	void setWzrost(const int wz);
	void setBmi();	
	double ObliczBmi();
	double ObliczBmi(int wag, int wzrost);

	const int& getWaga() const;
	const int& getWzrost() const;
	const double& getBmi() const;
	
	friend ostream& operator<<(ostream& os, const Klient& kl);

};

