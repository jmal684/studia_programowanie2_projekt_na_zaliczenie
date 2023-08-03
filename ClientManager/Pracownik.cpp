#include "Pracownik.h"
#include <iomanip>
#include <iostream>

using std::setw;
using std::cout;
using std::endl;


Pracownik::~Pracownik() {
	
	 wyplata = nullptr;
}

void Pracownik::WyswietlDane(int odstep, int wersja) {
	switch (wersja)
	{
	case 1:
		Osoba::WyswietlDane(odstep); cout << setw(odstep) << stanowisko << setw(odstep) << *wyplata << endl;
		break;
	case 2:
		Osoba::WyswietlDane(odstep); cout << setw(odstep) << "pracownik" << endl;
		break;
	default:
		break;
	}
	
}


void Pracownik::setWyplata(int* w) {
	wyplata = w;
}
void Pracownik::setStanowisko(string p) {
	stanowisko = p;
}

// int* Pracownik::getWyplata()  {
//	return wyplata;
//}
const string& Pracownik::getStanowisko() const {
	return stanowisko;
}

ostream& operator<<(ostream& os, const Pracownik& pr) {
	os<< pr.getTyp() << ";" << pr.getImie() << ";" << pr.getNazwisko() << ";" << pr.getStanowisko()<< "\n";
	return os;
}