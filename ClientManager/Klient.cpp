#include "Klient.h"
#include <iomanip>

using std::setw;
using std::cout;
using std::endl;

void Klient::WyswietlDane(int odstep, int wersja) {
	switch (wersja)
	{
	case 1:
		Osoba::WyswietlDane(odstep); cout << setw(odstep) << waga << setw(odstep) << wzrost << endl;
		break;
	case 2:
		Osoba::WyswietlDane(odstep); cout << setw(odstep) << "klient"<< endl;
		break;
	default:
		break;
	}
	
}

void Klient::setWaga(const int w) {
	waga = w;
}
void Klient::setWzrost(const int wz) {
	wzrost = wz;
}

void Klient::setBmi() {	
	bmi = ObliczBmi();
}
double Klient::ObliczBmi() {
	return ((waga) / pow(wzrost, 2)) * 10000;
}
double Klient::ObliczBmi(int wag, int wzrost) {
	return((wag) / pow(wzrost, 2)) * 10000;
}


const int& Klient::getWaga() const {
	return waga;
}
const int& Klient::getWzrost()  const {
	return wzrost;
}

const double& Klient::getBmi() const {
	return bmi;
}
ostream& operator<<(ostream& os, const Klient& kl) {
	os <<kl.getTyp()<<";"<< kl.getImie() << ";" << kl.getNazwisko() << ";" << kl.waga << ";" << kl.wzrost << "\n";
	return os;
}