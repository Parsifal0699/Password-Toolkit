#include <iostream>
#include <string>
#include <cstring>
#include "Funciones.h"
#include "Medidor_Fuerza.h"
#include "Cracker.h"
using namespace std;
#include <chrono>
#include "Ritmo.h"

int main(int numargumentos, char* argv[])
{
    if (numargumentos < 2)
    {
        cout << "Error.\n";
        cout << "  programa gen <longitud>\n";
        cout << "  programa check <contrasena>\n";
        cout << "  programa brute\n";
        cout << "  programa dict\n";
        cout << "programa pwn <contrasena>\n";
        return 1;
    }
    if (strcmp(argv[1], "gen") == 0) //Generar
    {
        int longitud = 0;
        try
        {
            longitud = stoi(argv[2]);
        }
        catch (...)
        {
            cout << "Error, la longitud tiene que ser un numero";
            return 1;
        }
        if (longitud < 6 || longitud > 64)
        {
            cout << "Error: la longitud debe ser >= 6 y <= 64\n";
            return 1;
        }
        cout << "Contrasena generada = " << Generar(longitud) << endl;
        return 0;
    }
    else if (strcmp(argv[1], "check") == 0)  //Revisar
    {
        string contra = argv[2];
        Medidor_Fuerza medidor;
        Resultado r = medidor.analizar(contra);

        cout << "Puntaje = " << r.puntaje <<  " / 100"  << endl;
        cout << "Nivel = " << r.nivel << endl;
        return 0;
    }
    else if (strcmp(argv[1], "brute") == 0) //Crackear por fuerza bruta
    {
        Cracker c;
        string cont = "";
        cout << "Ingresa tu contrasena" << endl;
        getline(cin, cont);
        auto inicio_t = chrono::high_resolution_clock::now();

        
        for (short longitud = 1; longitud <= cont.length(); longitud++) {
            if (c.Brute(cont, "", longitud)) {  
                return 0;
            }
        }
        auto fin_t = chrono::high_resolution_clock::now();
        double segundos = chrono::duration<double>(fin_t - inicio_t).count();
        cout << "Tiempo: " << segundos << " segundos" << endl;
        return 0;
    }
    else if (strcmp(argv[1], "dict") == 0){
        Cracker c;
        string cont = "";
        cout << "Ingresa tu contrasena" << endl;
        getline(cin , cont);
        
        auto inicio_t = chrono::high_resolution_clock::now();
        c.Dict(cont);
        auto fin_t = chrono::high_resolution_clock::now();
        double segundos = chrono::duration<double>(fin_t - inicio_t).count();
        cout << "Tiempo: " << segundos << " segundos" << endl;
    }
    else if (strcmp(argv[1], "pwn") == 0 ){
        string contrasena = argv[2];
        if (verificarPwned(contrasena)) {
        cout << " La contrasena '" << contrasena << "' ha sido filtrada\n";
        cout << "Se recomienda no usarla.\n";
        } 
       
    }
    else if (strcmp(argv[1], "dice") == 0) {
    int num = 0;
    cout << "Cuantas palabras? ";
    cin >> num;
    cout << "Passphrase: " << GenerarPassphrase(num) << endl;
    } 
    
    else if (strcmp(argv[1], "ritmo") == 0) {
    RitmoCracker r;
    r.Menu(8, 100); 
    }

    else
    {
        cout << "Error, comando invalido." << endl;
        return 1;
    }
}