#include "Pliki.h"
#include <fstream>
#include <iostream>;

using std::cout;
using std::cerr;
using std::endl;
using std::getline;


int getIloscLinijek(const string nazwaPliku) {
	std::ifstream plik(nazwaPliku);
	string linijka;
	double pomiar;
	int iloscLinijek = 0;


	if (!plik.is_open())
	{
		cerr << "BLAD: Brak pliku."<<endl;
	}
	else
	{
		//if (!(plik >> pomiar))
		//{
		//	cerr << "BLAD: Otwarcie pliku nie powiodlo sie."<<endl;
		//	exit(0);
		//}

		while (std::getline(plik, linijka)) {
			iloscLinijek++;
		}

		plik.close();

		return iloscLinijek;
	}
}

void Podziel(string*& fragmenty,string linia, const char separator, const int iloscInformacji) {
	fragmenty = new string[iloscInformacji];
	int pozycjaPrzecinka = 0;
	int indeks = 0;

	while (true)
	{
		pozycjaPrzecinka = linia.find(separator, 0);
		if (pozycjaPrzecinka == -1)
		{
			fragmenty[indeks] = linia.substr();
			break;
		}

		fragmenty[indeks] = linia.substr(0, pozycjaPrzecinka);
		linia = linia.substr(pozycjaPrzecinka + 1);
		indeks++;
	}

	
}

void Podziel(vector<string>& fragmenty, string linia, const char separator, const int iloscInformacji) {
	int pozycjaPrzecinka = 0;
	int indeks = 0;

	while (true)
	{
		pozycjaPrzecinka = linia.find(separator, 0);
		if (pozycjaPrzecinka == -1)
		{				
			fragmenty.push_back(linia.substr());
			break;
		}

		fragmenty.push_back(linia.substr(0, pozycjaPrzecinka));
		linia = linia.substr(pozycjaPrzecinka + 1);
		indeks++;
	}

}