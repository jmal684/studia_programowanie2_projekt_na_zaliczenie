#include "Baza.h"
#include "Pliki.h"
#include "Uzytkowe.h"
#include <iostream>
#include <iomanip>

#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

using std::cerr;
using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::setw;
using std::left;
using std::stof;
using std::make_unique;
using std::make_shared;


std::map<string, int>Wyplaty::wyplaty;

//Konstruktory, Destruktory
Baza::Baza(const int ilRek, const string nazwaBazy) {

	if (nazwaBazy == "klienci.txt")
	{

		InicTablicyKlientow(ilRek, nazwaBazy);
		wlasnosci = make_unique<Wlasnosci>(nazwaBazy, ilRek);
	}
	else if(nazwaBazy == "pracownicy.txt")
	{
	
		OdczytajWyplaty();
		InicTablicyPracownikow( ilRek, nazwaBazy);	
		wlasnosci = make_unique<Wlasnosci>(nazwaBazy, ilRek);
	}
	else
	{
		OdczytajWyplaty();
		InicWektora();	
		wlasnosci = make_unique<Wlasnosci>(nazwaBazy, ilRek);
	}

}
Baza::Baza(const Baza& b) {
	for (int i = 0; i<rekordy.size(); i++)
	{
		rekordy.push_back(make_unique<Klient>(*b.rekordy[i].get()));
	}
	for (int i = 0; i < pracownicy.size(); i++)
	{
		pracownicy.push_back(make_unique<Pracownik>(*b.pracownicy[i].get()));
	}
	for (int i = 0; i < osoby.size(); i++)
	{
		osoby.push_back(make_shared<Osoba>(*b.osoby[i].get()));
	}
	wlasnosci = make_unique<Wlasnosci>(*b.wlasnosci.get());
}



//Settery
void Baza::setIloscRekordow(int nowaIlosc) {
	wlasnosci->iloscRekordow = nowaIlosc;
}

//Gettery
const int& Baza::getIloscRekordow() const {
	return wlasnosci->iloscRekordow;
}
const string& Baza::getNazwaBazy() const {
	return wlasnosci->nazwa;
}
vector<unique_ptr<Klient>>& Baza::getKlienci()  {
	return rekordy;
}
vector<unique_ptr<Pracownik>>& Baza::getPracownicy() {
	return pracownicy;
}
vector<shared_ptr<Osoba>>& Baza::getOsoby() {
	return osoby;
}

//Klienci
void Baza::InicTablicyKlientow(const int& iloscRekordow, const string& nazwaBazy) {
	std::ifstream odczyt(nazwaBazy);
	string linijka;
	vector<string> fragmenty;
	double pomiar;



	if (!odczyt.is_open())
	{
		cerr << "Brak pliku"<<endl;
	}
	else
	{

		while (std::getline(odczyt, linijka)) {
			cout << linijka << endl;
			Podziel(fragmenty, linijka, ';', 5);

			//tablica[rekord]->setTyp(fragmenty[0]);
			//tablica[rekord]->setImie(fragmenty[1]);
			//tablica[rekord]->setNazwisko(fragmenty[2]);
			//tablica[rekord]->setWaga(stof(fragmenty[3]));
			//tablica[rekord]->setWzrost(stof(fragmenty[4]));
			//tablica[rekord]->setBmi();
			rekordy.push_back(make_unique<Klient>(fragmenty[0], fragmenty[1], fragmenty[2], stof(fragmenty[3]), stof(fragmenty[4])));
			fragmenty.clear();			
		
		}
		odczyt.close();		
	}
}
Klient Baza::GenerujLosowegoKlienta() {
	int przedzialWagowy[2] = { 50, 150 };
	int przedzialWzrostu[2] = { 150, 200 };
	/*int indeksLosowaneImie = WylosujLiczbe(1, 9); 
	int indeksLosowaneNazwisko = WylosujLiczbe(1, 9); 
	string imiona[10] = { "Jan", "Beata", "Kacper", "Bozena", "Amadeusz", "Karolina", "Grzegorz", "Amelia", "Cyprian", "Ewelina" };
	string nazwiska[10] = { "Nowak", "Parmezan", "Karo", "Kaszmir", "Patyk", "Gouda", "Zaba", "Wiadro", "Krecha", "Szynka" };*/

	Klient klient;
	klient.setTyp("k");
	klient.setImie(LosujImie());
	klient.setNazwisko(LosujNazwisko());
	klient.setWaga(WylosujLiczbe(przedzialWagowy[0], przedzialWagowy[1]));
	klient.setWzrost(WylosujLiczbe(przedzialWzrostu[0], przedzialWzrostu[1]));
	klient.setBmi();

	return klient;
}
void Baza::DodajKlienta() {
	int il = getIloscRekordow();

	Klient klient = GenerujLosowegoKlienta();
	
	rekordy.push_back(make_unique<Klient>(klient.getTyp(), klient.getImie(), klient.getNazwisko(), klient.getWaga(), klient.getWzrost()));
	rekordy.back()->setBmi();
	setIloscRekordow(il + 1);

	system("CLS");
	cout << "Dodano klienta nr: " << getIloscRekordow() << endl;
	system("pause");
}
void Baza::UsunKlienta() {
	//TODO Mozliwosc wyboru usuwanego rekordu
	int il = getIloscRekordow();

	if (il > 0)
	{
	
		int idUsuwanegoKlienta = WylosujLiczbe(1, rekordy.size());



		system("CLS");
		cout << "Usunieto klienta: " << rekordy[idUsuwanegoKlienta-1]->getImie() << " " << rekordy[idUsuwanegoKlienta-1]->getNazwisko() << endl;
		setIloscRekordow(il - 1);
		system("pause");
		rekordy.erase(rekordy.begin() + (idUsuwanegoKlienta - 1));
	}
	else
	{
		system("CLS");
		cerr << "Nie mozna usunac klienta: lista jest pusta." << endl;
		system("pause");
	}
}
void Baza::ModyfikujKlienta() {
	//TODO Lista jest pusta
	int idModyfikowanegoRekordu = 0;
	int il = getIloscRekordow();
	bool poprawnieWprowadzoneDane = false;
	string informacje = "";
	vector<string> fragmenty;

	cout << "Wpisz ID klienta, ktorego chcesz edytowac (0 aby cofnac): " << endl;
	idModyfikowanegoRekordu = WalidatorWyboru(0, il) - 1;
	if (idModyfikowanegoRekordu>=0)
	{
		system("cls");
		cout << "Podaj ponownie informacje (imie,nazwisko,waga,wzrost)" << endl;
		cin.ignore();

		do
		{
			cout << "-> ";
			getline(cin, informacje);
			Podziel(fragmenty, informacje, ',');
			if (WalidacjaDanych(fragmenty) == false)
			{
				cout << "Blad: Wprowadzono niepoprawne dane." << endl;
			}
			else
			{
				poprawnieWprowadzoneDane = true;
			}

		} while (!poprawnieWprowadzoneDane);

		rekordy[idModyfikowanegoRekordu]->setTyp("k");
		rekordy[idModyfikowanegoRekordu]->setImie(fragmenty[0]);
		rekordy[idModyfikowanegoRekordu]->setNazwisko(fragmenty[1]);
		rekordy[idModyfikowanegoRekordu]->setWaga(std::stof(fragmenty[2]));
		rekordy[idModyfikowanegoRekordu]->setWzrost(std::stof(fragmenty[3]));


		cout << "Pomyslnie nadpisano klienta nr: " << idModyfikowanegoRekordu + 1 << endl;	

		system("pause");
	}



}
void Baza::StanBmi() {
	const float zakresPoprawnejWagi[2] = { 18.5f, 24.9f };
	vector<int> niedowaga;
	vector<int> poprawnaWaga;
	vector<int> nadwaga;

	for (int i = 0; i < getIloscRekordow(); i++)
	{
		if (rekordy[i]->getBmi() < zakresPoprawnejWagi[0])
		{
			niedowaga.push_back(i);
		}
		else if (rekordy[i]->getBmi() > zakresPoprawnejWagi[1])
		{
			nadwaga.push_back(i);
		}
		else {
			poprawnaWaga.push_back(i);
		}
	}

	WyswietlStanBmi(niedowaga, poprawnaWaga, nadwaga);
}
void Baza::WyswietlStanBmi(const vector<int>& niedowaga, const vector<int>& poprawnaWaga, const vector<int>& nadwaga, int odstepMiedzyKolumnami ) {
	system("cls");
	cout << "========== STAN BMI KLIENTOW ==========" << endl;
	cout << endl;
	cout << setw(odstepMiedzyKolumnami) << std::left << "Imie" << setw(odstepMiedzyKolumnami) << "Nazwisko" << setw(odstepMiedzyKolumnami) << "BMI" << setw(odstepMiedzyKolumnami) << "Stan" << endl;
	cout << endl;

	for (auto i : niedowaga)
	{
		cout << setw(odstepMiedzyKolumnami) << std::left << rekordy[i]->getImie() << setw(odstepMiedzyKolumnami) << rekordy[i]->getNazwisko() << setw(odstepMiedzyKolumnami) << rekordy[i]->getBmi() << setw(odstepMiedzyKolumnami) << "NIEDOWAGA" << endl;
	}

	for (auto i: poprawnaWaga)
	{
		cout << setw(odstepMiedzyKolumnami) << std::left << rekordy[i]->getImie() << setw(odstepMiedzyKolumnami) << rekordy[i]->getNazwisko() << setw(odstepMiedzyKolumnami) << rekordy[i]->getBmi() << setw(odstepMiedzyKolumnami) << "POPRAWNE" << endl;
	}

	for (auto i: nadwaga)
	{
		cout << setw(odstepMiedzyKolumnami) << std::left << rekordy[i]->getImie() << setw(odstepMiedzyKolumnami) << rekordy[i]->getNazwisko() << setw(odstepMiedzyKolumnami) << rekordy[i]->getBmi() << setw(odstepMiedzyKolumnami) << "NADWAGA" << endl;
	}

	system("pause");
}
void Baza::ZapiszKlientow() {
	std::ofstream plik(getNazwaBazy());
	if (!plik.is_open())
	{
		cerr << "BLAD: Brak pliku." << endl;
	}
	else
	{
		for (int i = 0; i < getIloscRekordow(); i++)
		{
			plik << *rekordy[i];
		}
		plik.close();

	}
}

//Pracownicy
void Baza::InicTablicyPracownikow(const int& iloscRekordow, const string& nazwaBazy) {
	std::ifstream odczyt(nazwaBazy);
	string linijka;
	vector<string> fragmenty;
	double pomiar;


	if (!odczyt.is_open())
	{
		cerr << "Brak pliku"<<endl;
	}
	else
	{

		while (getline(odczyt, linijka)) {
			cout << linijka << endl;
			Podziel(fragmenty, linijka, ';', 4);

			pracownicy.push_back(make_unique<Pracownik>(fragmenty[0], fragmenty[1], fragmenty[2], fragmenty[3], &Wyplaty::wyplaty.at(fragmenty[3])));
			fragmenty.clear();

		}
		odczyt.close();


	}
}
Pracownik Baza::GenerujLosowegoPracownika() {
	vector<string>stanowiska;	
	KopiujKluczeMapy(stanowiska, Wyplaty::wyplaty);
	
	Pracownik pracownik;
	pracownik.setTyp("p");
	pracownik.setImie(LosujImie());
	pracownik.setNazwisko(LosujNazwisko());
	pracownik.setStanowisko(stanowiska[WylosujLiczbe(0,stanowiska.size()-1)]);

	return pracownik;

}
void Baza::DodajPracownka() {
	int il = getIloscRekordow();

	Pracownik pracownik = GenerujLosowegoPracownika();

	
	pracownicy.push_back(make_unique<Pracownik>(pracownik.getTyp(), pracownik.getImie(), pracownik.getNazwisko(), pracownik.getStanowisko(),&Wyplaty::wyplaty.at(pracownik.getStanowisko())));
	setIloscRekordow(il + 1);

	system("CLS");
	cout << "Dodano pracownika nr: " << getIloscRekordow() << endl;
	system("pause");
}
void Baza::UsunPracownika() {
	int il = getIloscRekordow();

	if (il > 0)	{

		int idUsuwanegoPracownika = WylosujLiczbe(1, pracownicy.size());

		system("CLS");
		cout << "Usunieto pracownika: " << pracownicy[idUsuwanegoPracownika-1]->getImie() << " " << pracownicy[idUsuwanegoPracownika-1]->getNazwisko() << endl;

		setIloscRekordow(il - 1);
		system("pause");
		pracownicy.erase(pracownicy.begin() + (idUsuwanegoPracownika - 1));
	}
	else
	{
		system("CLS");
		cerr << "Nie mozna usunac pracownika: lista jest pusta." << endl;
		system("pause");
	}
}
void Baza::ModyfikujWyplaty() {
	int wybor = 0;
	string nowaWyplata;
	vector<string>zawody2;
	
	KopiujKluczeMapy(zawody2, Wyplaty::wyplaty);

	system("CLS");
	for (int i = 0; i < zawody2.size(); i++)
	{
		cout << i + 1 << ". " << zawody2[i] << ": " << Wyplaty::wyplaty.at(zawody2[i])<<endl;
	}
	wybor = WalidatorWyboru(1, zawody2.size()) - 1;	
	
	while (true)
	{
		cout << "Podaj nowa wyplate: ";
		cin >> nowaWyplata;
		if (SprawdzTyp(nowaWyplata))
		{
			Wyplaty::wyplaty.at(zawody2[wybor]) = std::stoi(nowaWyplata);
			break;
		}
		cout << "Blad: Zle podano wyplate" << endl;
	}
	system("CLS");
	cout << "Pomyslnie zmodyfikowano wyplate dla stanowiska " << zawody2[wybor]<<endl;
}
void Baza::OdczytajWyplaty() {
	std::ifstream odczyt("wyplaty.txt");
	string linijka;
	
	vector<string> fragmenty;
	if (!odczyt.is_open())
	{
		std::cerr << "Brak pliku\n";
	}
	else
	{
		while (getline(odczyt, linijka)) {
			
			Podziel(fragmenty, linijka, ';', 2);
			Wyplaty::wyplaty.insert({ fragmenty[0], std::stoi(fragmenty[1]) });
			fragmenty.clear();
			
			
		}

		odczyt.close();		
	}
}
void Baza::ZapiszWyplaty() {
	std::ofstream odczyt("wyplaty.txt");
	if (!odczyt.is_open())
	{
		cerr << "BLAD: Brak pliku." << endl;
	}
	else {
		for (const auto &i: Wyplaty::wyplaty)
		{
			odczyt << i.first << ";" << i.second << "\n";
		}
	}
}
void Baza::ZapiszPracownikow() {
	std::ofstream plik(getNazwaBazy());

	if (!plik.is_open())
	{
		cerr << "BLAD: Brak pliku." << endl;
	}
	else
	{
		for (int i = 0; i < getIloscRekordow(); i++)
		{
			//plik << rekordy[i]->getImie() << ";" << rekordy[i]->getNazwisko() << ";" << rekordy[i]->getWaga() << ";" << rekordy[i]->getWzrost() << "\n";
			plik << *pracownicy[i];
		}
		plik.close();

	}
}

//wszyscy - wektor
void Baza::InicWektora() {
	std::ifstream odczytKlientow("klienci.txt");
	std::ifstream odczytPracownikow("pracownicy.txt");
	string linijka;
	vector<string> fragmenty;
	double pomiar;
	int rekord = 0;

	if (!odczytKlientow.is_open())
	{
		cerr << "Brak pliku" << endl;
	}
	else
	{
		while (getline(odczytKlientow, linijka))
		{
			if (linijka[0] == 'p')
			{
				Podziel(fragmenty, linijka, ';', 4);
				osoby.push_back(make_shared<Pracownik>(fragmenty[0], fragmenty[1], fragmenty[2], fragmenty[3], &Wyplaty::wyplaty.at(fragmenty[3])));
				fragmenty.clear();

			}
			else if (linijka[0] == 'k')
			{
				Podziel(fragmenty, linijka, ';', 5);
				osoby.push_back(make_shared<Klient>(fragmenty[0], fragmenty[1], fragmenty[2], stof(fragmenty[3]), stof(fragmenty[4])));
				fragmenty.clear();
			}
		}

		odczytKlientow.close();

		while (getline(odczytPracownikow, linijka))
		{
			if (linijka[0] == 'p')
			{
				Podziel(fragmenty, linijka, ';', 4);
				osoby.push_back(make_shared<Pracownik>(fragmenty[0], fragmenty[1], fragmenty[2], fragmenty[3], &Wyplaty::wyplaty.at(fragmenty[3])));
				fragmenty.clear();

			}
			else if (linijka[0] == 'k')
			{
				Podziel(fragmenty, linijka, ';', 5);
				osoby.push_back(make_shared<Klient>(fragmenty[0], fragmenty[1], fragmenty[2], stof(fragmenty[3]), stof(fragmenty[4])));
				fragmenty.clear();
			}
		}

		odczytPracownikow.close();
		

	}
}
void Baza::DodajRekord() {
	Klient klient;
	Pracownik pracownik;
	int wybor = 0;
	system("cls");
	cout << "Wybierz typ:" << endl;
	cout << "1. Klient" << endl;
	cout << "2. Pracownik" << endl;
	wybor = WalidatorWyboru(1, 2);

	switch (wybor)
	{
	case 1:
		 klient = GenerujLosowegoKlienta();
		osoby.push_back(make_shared<Klient>(klient.getTyp(), klient.getImie(), klient.getNazwisko(), klient.getWaga(), klient.getWzrost()));
		system("CLS");
		cout << "Pomyslnie dodano klienta." << endl;
		break;
	case 2:
		pracownik = GenerujLosowegoPracownika();

		osoby.push_back(make_shared<Pracownik>(pracownik.getTyp(), pracownik.getImie(), pracownik.getNazwisko(), pracownik.getStanowisko(), &Wyplaty::wyplaty.at(pracownik.getStanowisko())));
		cout << "Pomyslnie dodano pracownika." << endl;
		break;
		
	default:
		break;
	}
}
void Baza::UsunRekord() {
	if (osoby.size()>0)
	{
		int idUsuwanegoRekordu = WylosujLiczbe(1, osoby.size());
		system("cls");
		cout << "Usunieto rekord: ";
		osoby[idUsuwanegoRekordu - 1]->WyswietlDane(10, 2);
		system("pause");
		osoby.erase(osoby.begin() + (idUsuwanegoRekordu - 1));
	}
	else
	{
		system("cls");
		cerr << "BLAD: Nie mozna usunac rekordu, lista jest pusta" << endl;
		system("pause");
	}

	
	
}
void Baza::ZapiszWektor() {	

	std::ofstream odczytKlienci("klienci.txt");
	std::ofstream odczytPracownicy("pracownicy.txt");

	if (!odczytKlienci.is_open() || !odczytPracownicy.is_open())
	{
		cerr << "BLAD: Brak jednego z plikow" << endl;
	}
	else
	{
		for (auto &i : osoby)
		{
			if (shared_ptr<Klient>klient = std::dynamic_pointer_cast<Klient>(i))
			{
				odczytKlienci << *klient;
			
			}
			else if (shared_ptr<Pracownik> pracownik = std::dynamic_pointer_cast<Pracownik>(i))
			{
				odczytPracownicy << *pracownik;
				
		
			}
		}

	}
	odczytKlienci.close();
	odczytPracownicy.close();


	
	

}


//Przeciazaone operatory
Baza& Baza::operator=(const Baza& right) {
	if (&right != this)
	{
		this->Baza::~Baza();
		this->Baza::Baza(right);
	}
	return *this;
}
Klient* Baza::operator[](int index) { //TODO cos z tym zrobic
	//TODO: zamienic na sam &
// Klient& Baza::operator[](int index) {
	return rekordy[index].get();
}

