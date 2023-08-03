#pragma once
#define _CRTDBG_MAP_ALLOC
#include "Klient.h"
#include "Pracownik.h"
#include "Wyplaty.h"
#include <string>
#include <vector>
#include <fstream>
#include <memory>



using std::string;
using std::vector;
using std::unique_ptr;
using std::shared_ptr;

class Baza
{
private:
	class Wlasnosci {
	private:
		string nazwa;
		int iloscRekordow;

	public:
		friend class Baza;
		Wlasnosci(string naz, int il)
		{
			nazwa = naz;
			iloscRekordow = il;
		}
	};

	vector<unique_ptr<Klient>> rekordy;
	vector<unique_ptr<Pracownik>> pracownicy;
	vector<shared_ptr<Osoba>> osoby;

	unique_ptr<Wlasnosci> wlasnosci;

public:
	//Konstruktory, destruktory
	Baza(const int ilRek, const string nazwaBazy);
	Baza(const Baza& b);

	//Settery
	void setIloscRekordow(int nowaIlosc);
	
	//Gettery
	const string& getNazwaBazy() const;
	const int& getIloscRekordow() const;
	vector<unique_ptr<Klient>>& getKlienci();
	vector<unique_ptr<Pracownik>>& getPracownicy();
	vector<shared_ptr<Osoba>>& getOsoby();

	//Klienci		
	void InicTablicyKlientow(const int& iloscRekordow, const string& nazwaBazy);
	Klient GenerujLosowegoKlienta();
	void DodajKlienta();
	void UsunKlienta();
	void ModyfikujKlienta();
	void StanBmi();
	void WyswietlStanBmi(const vector<int>& niedowaga, const vector<int>& poprawnaWaga, const vector<int>& nadwaga,int odstepMiedzyKolumnami = 10 );
	void ZapiszKlientow();

	//Pracownicy
	void InicTablicyPracownikow(const int& iloscRekordow, const string& nazwaBazy);
	Pracownik GenerujLosowegoPracownika();
	void DodajPracownka();
	void UsunPracownika();
	void ModyfikujWyplaty();
	void OdczytajWyplaty();
	void ZapiszWyplaty();
	void ZapiszPracownikow();

	//wektor - wszyscy
	void InicWektora();
	void DodajRekord();
	void UsunRekord();
	void ZapiszWektor();

	//Przeciazone operatory
	Baza& operator=(const Baza& right);
	Klient* operator[](int index);
};


