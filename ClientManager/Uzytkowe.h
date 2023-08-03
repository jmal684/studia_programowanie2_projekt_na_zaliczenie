#pragma once
#include <string>
#include <map>
#include <vector>

using std::string;
using std::map;
using std::vector;

int WalidatorWyboru(const int poczatekZakresu, const int koniecZakresu);
int WylosujLiczbe(const int& poczatekZakresu, const int& koniecZakresu);
string LosujImie();
string LosujNazwisko();

bool WalidacjaDanych(string* fragmenty);
bool WalidacjaDanych(vector<string>& fragmenty);
bool SprawdzTyp(string& slowo, const int tryb=0);

void KopiujKluczeMapy(vector<string>& klucze, map<string, int>& mapa);