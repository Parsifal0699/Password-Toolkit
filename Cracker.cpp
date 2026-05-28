#include "Cracker.h"
#include "Funciones.h"
using namespace std;
#include <string>
#include <iostream>
#include <fstream>

bool Cracker::Brute(string& c_objetivo, string actual, short max_longitud)
{
    if (c_objetivo == actual) {
        cout << "La contrasena es:  " << actual << endl;
        return true;
    }
    if (actual.length() >= max_longitud) {
        return false;
    }
    for (char letra : letras) {  
        if (Brute(c_objetivo, actual + letra, max_longitud)) {
            return true;
        }
    }
    return false;
}

void Cracker::Dict(string &c_objetivo)
{
    vector<char> buffer = leerArchivoCompleto("rockyou.txt");
    string_view datos(buffer.data(), buffer.size()); //El string_view guarda todo el archivo
    if (!comprobarLineas(datos, c_objetivo)) {
        cout << "Contraseña no encontrada en el diccionario." << endl;
    }
}
