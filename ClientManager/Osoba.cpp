#include "Osoba.h"


void Osoba::setImie(string im) {
	imie = im;
}
void Osoba::setNazwisko(string naz) {
	nazwisko = naz;
}
void Osoba::setTyp(string tp) {
	typ = tp;
}


const string& Osoba::getImie() const {
	return imie;
}
const string& Osoba::getNazwisko() const {
	return nazwisko;
}
const string& Osoba::getTyp() const {
	return typ;
}