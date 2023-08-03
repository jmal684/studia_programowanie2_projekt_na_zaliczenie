#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include "Struktura.h"
#include "Pliki.h"
#include "Uzytkowe.h"
#include <iomanip>
#include <iostream>
#include <crtdbg.h>
#include <iterator>
#include <algorithm>


using std::cout;
using std::endl;
using std::setw;

void ClientManager() {
	int wybor = 0;
	int stan = 0;
	bool dziala = true;
	do
	{
		system("CLS");
		cout << "1. Zaladuj baze" << endl;
		cout << "2. Wyjscie" << endl;

		wybor = WalidatorWyboru(1, 2);

		switch (wybor)
		{
		case 1:
			do
			{
				stan = MenuWyborBazy();
			} while (stan != 0);
			break;
			 
		case 2:
			dziala = false;
			break;
		default:
			break;
		}
	} while (dziala);

	
	exit(0);
}
int MenuWyborBazy() {
	int wybor = 0;
	int stan = 0;
	unique_ptr<Baza>pracownicy;
	unique_ptr<Baza>klienci;
	unique_ptr<Baza> wszyscy;
	//* klienci = nullptr;
	//Baza* pracownicy = nullptr;
	//Baza* wszyscy = nullptr;


	system("CLS");
	cout << "Wybierz baze:" << endl;
	cout << "1. Klienci" << endl;
	cout << "2. Pracownicy" << endl;
	cout << "3. Wszyscy" << endl;
	cout << "4. Cofnij"<<endl;

	wybor = WalidatorWyboru(1, 4);
	switch (wybor)
	{
	case 1:
		ZaladujBaze(klienci,"klienci.txt");
		do
		{
			stan = MenuKlienci(klienci.get());
		} while (stan!=0);
		return 0;
		break;
	case 2:
		ZaladujBaze(pracownicy, "pracownicy.txt");
		do
		{
			stan = MenuPracownicy(pracownicy.get());
		} while (stan!=0);
		return 0;
		break;
	case 3:
		ZaladujBaze(wszyscy, "wszyscy");
		do
		{
			stan = MenuWszyscy(wszyscy.get());
		} while (stan!=0);
		return 0;
		break;
	case 4:
		return 0;
		break;
	default:
		break;
	}

}
int MenuKlienci(Baza* baza) {
	int wybor = 0;
	system("CLS");
	cout << "Baza: " << baza->getNazwaBazy() << endl;
	
	WyswietlTablice(baza, baza->getIloscRekordow());

	cout << "=======================================" << endl;
	cout << "1. Dodanie klienta" << endl;
	cout << "2. Usuniecie klienta" << endl;
	cout << "3. Modyfikowanie informacji klienta" << endl;
	cout << "4. Stan BMI klientow" << endl;
	cout << "5. Wyjdz i zapisz" << endl;

	wybor = WalidatorWyboru(1, 5);
	switch (wybor)
	{
	case 1:
		baza->DodajKlienta();
		return 1;
		break;
	case 2:
		baza->UsunKlienta();
		return 1;
		break;
	case 3:
		baza->ModyfikujKlienta();
		return 1;
		break;
	case 4:
		baza->StanBmi();
		return 1;
	case 5:
		baza->ZapiszKlientow();
		//ZwolnijBaze(baza);
		return 0;
		break;
	default:
		break;
	}
}
int MenuPracownicy(Baza* pracownicy) {
	int wybor = 0;
	system("CLS");
	cout << "Baza: " << pracownicy->getNazwaBazy() << endl;

	WyswietlTablice(pracownicy->getPracownicy(), pracownicy->getIloscRekordow(),15);

	cout << "=======================================" << endl;
	cout << "1. Dodanie pracownika" << endl;
	cout << "2. Usuniecie pracownika" << endl;	
	cout << "3. Modyfikowanie wyplat" << endl;
	cout << "4. Wyjdz i zapisz" << endl;

	wybor = WalidatorWyboru(1, 4);
	switch (wybor)
	{
	case 1:
		pracownicy->DodajPracownka();
		return 1;
		break;
	case 2:
		pracownicy->UsunPracownika();
		return 1;
		break;
	case 3:
		pracownicy->ModyfikujWyplaty();
		return 1;
		break;
	case 4:
		pracownicy->ZapiszPracownikow();
		pracownicy->ZapiszWyplaty();
		//ZwolnijBaze(pracownicy);
		return 0;
		break;
	default:
		break;
	}
}
int MenuWszyscy(Baza* wszyscy) {
	int wybor = 0;
	system("CLS");
	cout << "Baza: " << wszyscy->getNazwaBazy() << endl;
	cout << endl;
	WyswietlTablice(wszyscy->getOsoby(), 20);
	cout << "=======================================" << endl;
	cout << "1. Dodaj rekord" << endl;
	cout << "2. Usun rekord" << endl;
	cout << "3. Wyjdz" << endl;
	wybor = WalidatorWyboru(1, 4);
	switch (wybor)
	{
	case 1:
		wszyscy->DodajRekord();	
		return 1;
		break;
	case 2:
		wszyscy->UsunRekord();
		return 1;
		break;
	case 3:
		wszyscy->ZapiszWektor();	
		return 0;
		break;
	default:
		break;
	}
}
void ZaladujBaze(unique_ptr<Baza>& baza, const string nazwaBazy) {
	int iloscRekordow = getIloscLinijek(nazwaBazy);
	baza = std::make_unique<Baza>(iloscRekordow, nazwaBazy);
}

void WyswietlTablice(Baza*& baza, const int& iloscRekordow, int odstepMiedzyKolumnami) {
	if (iloscRekordow > 0)
	{
		cout << setw(odstepMiedzyKolumnami) << std::left << "ID" << setw(odstepMiedzyKolumnami) << "Imie" << setw(odstepMiedzyKolumnami) << "Nazwisko" << setw(odstepMiedzyKolumnami) << "Waga" << setw(odstepMiedzyKolumnami) << "Wzrost" << endl;
		cout << endl;
		for (int i = 0; i < iloscRekordow; i++)
		{
			cout << setw(odstepMiedzyKolumnami) << std::left << i + 1 << setw(odstepMiedzyKolumnami);
			baza->operator[](i)->WyswietlDane(odstepMiedzyKolumnami);

			//cout << setw(odstepMiedzyKolumnami) << std::left << i + 1 << setw(odstepMiedzyKolumnami) << tablica[i]->getImie() << setw(odstepMiedzyKolumnami) << setw(odstepMiedzyKolumnami) << tablica[i]->getNazwisko() << setw(odstepMiedzyKolumnami) << setw(odstepMiedzyKolumnami) << tablica[i]->getWaga() << setw(odstepMiedzyKolumnami) << tablica[i]->getWzrost() << endl;

		}
	}
	else {
		cout << "Lista jest pusta" << endl;
	}
}
void WyswietlTablice(const vector<unique_ptr<Pracownik>>& tablica, const int& iloscRekordow, int odstepMiedzyKolumnami) {
	if (iloscRekordow > 0)
	{
		cout << setw(odstepMiedzyKolumnami) << std::left << "ID" << setw(odstepMiedzyKolumnami) << "Imie" << setw(odstepMiedzyKolumnami) << "Nazwisko" << setw(odstepMiedzyKolumnami) << "Stanowisko" <<setw(odstepMiedzyKolumnami)<< "Wyplata" << endl;
		cout << endl;
		for (int i = 0; i < iloscRekordow; i++)
		{
			cout << setw(odstepMiedzyKolumnami) << std::left << i + 1 << setw(odstepMiedzyKolumnami);
			tablica[i]->WyswietlDane(odstepMiedzyKolumnami);
		}
	}
	else {
		cout << "Lista jest pusta" << endl;
	}
}
void WyswietlTablice(vector<shared_ptr<Osoba>>& osoby, int odstepMiedzyKolumnami) {
	auto iloscWGrupach = [](vector<shared_ptr<Osoba>>& os) {
		int iloscKlientow=0, iloscPracownikow=0;
		for (vector<shared_ptr<Osoba>>::iterator i = os.begin(); i<os.end(); i++)
		{
			if (i->get()->getTyp() == "k") iloscKlientow++;
			else iloscPracownikow++;
		}
		cout << "Ilosc klientow: " << iloscKlientow << "  Ilosc pracownikow " << iloscPracownikow << endl;
	};
	auto odAdoZ = [](shared_ptr<Osoba> osoba1, shared_ptr<Osoba> osoba2) {return osoba1->getTyp() < osoba2->getTyp(); };

	std::sort(osoby.begin(), osoby.end(), odAdoZ);
	iloscWGrupach(osoby);
	
	if (osoby.size() > 0)
	{
		int id = 1;
		cout << setw(odstepMiedzyKolumnami) << std::left << "ID" <<setw(odstepMiedzyKolumnami)<< "Imie" << setw(odstepMiedzyKolumnami) << "Nazwisko" << setw(odstepMiedzyKolumnami) << "Typ" << endl;
		cout << endl;
		for (auto const & i: osoby)
		{
			cout << setw(odstepMiedzyKolumnami) << std::left << id << setw(odstepMiedzyKolumnami);
			i->WyswietlDane(odstepMiedzyKolumnami,2);
			id++;
		}
	}
	else {
		cout << "Lista jest pusta" << endl;
	}
}



