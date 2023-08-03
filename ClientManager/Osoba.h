#pragma once
#include <string>
#include <iomanip>
#include <iostream>
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"
#define RED   "\x1B[31m"

using std::string;
using std::setw;
using std::cout;

class Osoba
{
private:
	string imie;
	string nazwisko;
	string typ;

public:
	virtual void WyswietlDane(int odstep, int wersja = 1) {
		cout << setw(odstep) << imie << setw(odstep) << nazwisko;
	}
	


	Osoba() = default;
	Osoba(string tp, string im, string naz) :typ(tp), imie(im), nazwisko(naz){};

	void setImie(string im);
	void setNazwisko(string naz);
	void setTyp(string tp);

	const string& getImie() const;
	const string& getNazwisko() const;
	const string& getTyp() const;
};

