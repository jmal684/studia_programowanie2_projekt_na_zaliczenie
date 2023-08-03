#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

int getIloscLinijek(const string nazwaPliku);

void Podziel(string*& fragmenty,string linia, const char separator, const int iloscInformacji = 4);
void Podziel(vector<string>&fragmenty, string linia, const char separator, const int iloscInformacji = 4);