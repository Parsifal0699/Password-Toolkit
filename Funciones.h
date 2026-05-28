#pragma once 
#include <string>
using namespace std;
#include <iostream>
#include <vector>
#include <string_view>

string Generar(int);

vector<char> leerArchivoCompleto(const string&);

bool comprobarLineas(string_view,string_view);

bool verificarPwned(const string& contrasena); 

string GenerarPassphrase(int);