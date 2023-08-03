#pragma once
#define _CRTDBG_MAP_ALLOC
#include "Baza.h"
#include <memory>

using std::unique_ptr;



void ClientManager();
int MenuWyborBazy();
int MenuKlienci(Baza* baza);
int MenuPracownicy(Baza* pracownicy);
int MenuWszyscy(Baza* wszyscy);

void ZaladujBaze(unique_ptr<Baza>&baza, const string nazwaBazy);
void WyswietlTablice(Baza*& baza, const int& iloscRekordow, int odstepMiedzyKolumnami=10);
void WyswietlTablice(const vector<unique_ptr<Pracownik>>& tablica, const int& iloscRekordow, int odstepMiedzyKolumnami = 10);
void WyswietlTablice(vector<shared_ptr<Osoba>>& osoby, int odstepMiedzyKolumnami = 10);

