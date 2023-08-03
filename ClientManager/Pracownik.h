#pragma once
#include "Osoba.h"
#include <memory>
using std::ostream;
using std::unique_ptr;

class Pracownik: public Osoba
{
private:
	
	int * wyplata;
	string stanowisko;

public:
	Pracownik() = default;
	Pracownik(string tp, string im, string naz, string st, int* wp) : Osoba(tp, im, naz), stanowisko(st), wyplata(wp) {};
	~Pracownik();

	void WyswietlDane(int odstep, int wersja =1) override;

	void setWyplata(int* w);
	void setStanowisko(string p);


	const string& getStanowisko() const;

	friend ostream& operator<<(ostream& os, const Pracownik& pr);


};


