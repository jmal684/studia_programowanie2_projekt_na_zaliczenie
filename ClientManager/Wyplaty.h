#pragma once
#include <map>
#include <string>

using std::string;
class Wyplaty
{
public:
	static std::map<string, int> wyplaty;
	
};

class OdZDoA {
	bool operator() (string a, string b) {
		return b > a;
	}
};


