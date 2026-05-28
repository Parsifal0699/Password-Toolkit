#include "Medidor_Fuerza.h"
using namespace std;
#include <iostream>
#include <string>
#include <cctype>
#include <fstream>

Resultado Medidor_Fuerza::analizar(const string& contra)
{
	Resultado re;
	short puntos = 0;
	short contador = 0;
	//Verificar que la contraseña no esté vacía
	if (contra.length() == 0) {
		cout << "NO PUEDES NO TENER CONTRASENA";
		re.puntaje = 0;
		re.nivel = "No existe contrasena*";
		return re;
	}
	//Verificar si es una contraseña común
	ifstream file("10k-common-passwords.txt");
	if (file.is_open())
	{
		string linea;
		while (getline(file, linea))
		{
			if (!linea.empty() && linea.back() == '\r')
			{
				linea.pop_back();
			}

			if (linea == contra)
			{
				Resultado re;
				re.puntaje = 0;
				return re;
			}
		}
	}
	//Largo contraseña
	if (contra.length() < 6) {
		puntos += 0;
	}
	else if ( contra.length() < 10 ) {
		puntos += 5;
	}
	else if ( contra.length() < 12) {
		puntos += 10;
	}
	else {
		puntos += 25;
	}

	//Si contiene por lo menos una mayúscula, numero o simbolo
	for (char c :  contra) {
		if (isupper(c))
		{
			puntos += 2;
		}
		if (isdigit(c)) {
			puntos += 3;
		}
		if (ispunct(c)) {
			puntos += 4;
		}
	}
	//verificar caracteres repetidos
	for (int i = 1; i < contra.length(); i++) {
        if (contra[i] == contra[i - 1]) {
         puntos -= 5;
        }
      }
      
      
	//verificar pares repetidos
	for (int i = 2; i < contra.length() - 1; i++) {
        if (contra[i] == contra[i - 2] && contra[i + 1] == contra[i - 1]) {
        puntos -= 5;
         }
      }
      //verifica secuencias
	for (int i = 1; i < contra.length(); i++) {
        if (contra[i] == contra[i - 1] + 1) {
        puntos -= 5;
        }
      } 

	if (puntos < 0)
	{
		puntos = 0;
	}

	re.puntaje = puntos;

	
	if (re.puntaje < 25)
	{
		re.nivel = "Debil";
	}
	else if (re.puntaje < 50)
	{
		re.nivel = "Regular";
	}
	else if (re.puntaje < 75)
	{
		re.nivel = "Fuerte";
	}
	else
	{
		re.nivel = "Muy fuerte";
	}


	return re;
}
