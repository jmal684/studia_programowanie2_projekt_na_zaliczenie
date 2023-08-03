#include "Uzytkowe.h"
#include <random>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;
using std::cin;



int WalidatorWyboru(const int poczatekZakresu, const int koniecZakresu) {
	int wybor;
	string dana;
	do
	{
		cout << "-> ";
		cin >> dana;

		if (SprawdzTyp(dana, 0))
		{
			wybor = std::stoi(dana);
			if (wybor < poczatekZakresu || wybor > koniecZakresu) cerr << "Blad: Podana wartosc jest poza dostepnym zakresem" << endl;
			else break;
		}
		else cerr << "Blad: Podana wartosc nie jest liczba" << endl;
	} while (true);

	return wybor;
}

int WylosujLiczbe(const int& poczatekZakresu, const int& koniecZakresu) {
	std::random_device seed;
	std::mt19937 engine(seed());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(poczatekZakresu, koniecZakresu);
	return dist6(engine);
}
string LosujImie() {
	string imiona[10] = { "Jan", "Beata", "Kacper", "Bozena", "Amadeusz", "Karolina", "Grzegorz", "Amelia", "Cyprian", "Ewelina" };
	return imiona[WylosujLiczbe(1, 10)-1];
}
string LosujNazwisko() {
	string nazwiska[10] = { "Nowak", "Parmezan", "Karo", "Kaszmir", "Patyk", "Gouda", "Zaba", "Wiadro", "Krecha", "Szynka" };
	return nazwiska[WylosujLiczbe(1, 10)-1];
}

bool WalidacjaDanych(string* fragmenty) {
	bool czyPusta = false;
	for (int i = 0; i < 4; i++)
	{
		if (empty(fragmenty[i]))
		{
			czyPusta = true;
			break;
		}
	}
	if (czyPusta)
	{
		return false;
	}
	else
	{
		if (SprawdzTyp(fragmenty[0], 1) == false || SprawdzTyp(fragmenty[1], 1) == false || SprawdzTyp(fragmenty[2]) == false || SprawdzTyp(fragmenty[3]) == false)
		{
			return false;
		}
		fragmenty[0][0] = toupper(fragmenty[0][0]);
		fragmenty[1][0] = toupper(fragmenty[1][0]);
		return true;
	}

}
bool WalidacjaDanych(vector<string>& fragmenty) {
	bool czyPusta = false;
	for (int i = 0; i < 4; i++)
	{
		if (empty(fragmenty[i]))
		{
			czyPusta = true;
			break;
		}
	}
	if (czyPusta)
	{
		return false;
	}
	else
	{
		if (SprawdzTyp(fragmenty[0], 1) == false || SprawdzTyp(fragmenty[1], 1) == false || SprawdzTyp(fragmenty[2]) == false || SprawdzTyp(fragmenty[3]) == false)
		{
			return false;
		}
		fragmenty[0][0] = toupper(fragmenty[0][0]);
		fragmenty[1][0] = toupper(fragmenty[1][0]);
		return true;
	}
}

bool SprawdzTyp(string& slowo, const int tryb) {
	//tryb 0 - sprawdzenie czy jest liczba, tryb 1 = sprawdzenie czy jest slowem
	if (tryb == 0)
	{
		for (size_t i = 0; i < slowo.length(); i++)
		{
			if (isdigit(slowo[i]) == 0)
			{
				return false;
				break;
			}
		}
		return true;
	}
	else if (tryb == 1) {
		for (size_t i = 0; i < slowo.length(); i++)
		{
			if (isdigit(slowo[i]) > 0)
			{
				return false;
				break;
			}
		}
		return true;
	}
}

void KopiujKluczeMapy(vector<string>& klucze, map<string, int>& mapa) {
	for (const auto &i: mapa)
	{
		klucze.push_back(i.first);
	}
}