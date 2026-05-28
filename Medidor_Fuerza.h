#pragma once
using namespace std;
#include <iostream>
#include <string>

struct Resultado {
	short puntaje;
	string nivel;

};


class Medidor_Fuerza
{
public:
	Resultado analizar(const string&);
};

