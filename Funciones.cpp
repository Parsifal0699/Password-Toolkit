#include <string>
#include <random>
using namespace std;
#include <string_view>
#include <vector>
#include <fstream>
#include <iostream>

string Generar(int largo) {
    const string letras = "abcdefghijklmnopqrstuvwxyz";
    const string mayusculas = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string simbolos = "!@#$%^&*()-_=+[]{};:,.?/|<>~`";
    const string nums = "0123456789";
    random_device rd;
    seed_seq seed{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
    mt19937 gen(seed);

    uniform_int_distribution<int> distLet(0,letras.size() - 1);
    uniform_int_distribution<int> distMay(0,mayusculas.size() - 1);
    uniform_int_distribution<int> distSim(0,simbolos.size() - 1);
    uniform_int_distribution<int> distNum(0,nums.size() - 1);
    uniform_int_distribution<int> distPos(0,largo - 1);
    uniform_int_distribution<int> distTipo(0, 3);
    int uno = distPos(gen);
    int dos = distPos(gen);
    int tres = distPos(gen);
    while (dos == uno) {
        dos = distPos(gen);
    }
    while (tres == uno || tres == dos) {
        tres = distPos(gen);
    }

    string contra(largo, ' ');
    for (int i = 0; i < largo; i++) {
        if (i == uno) {
            contra[i] = mayusculas[distMay(gen)];
        }
        else if (i == dos) {
            contra[i] = simbolos[distSim(gen)];
        }
        else if (i == tres) {

            contra[i] = nums[distNum(gen)];
        }
        else {
            int tipo = distTipo(gen);
            if (tipo == 0) {
                contra[i] = letras[distLet(gen)];
            }
            else if (tipo == 1) {
                contra[i] = mayusculas[distMay(gen)];
            }
            else if (tipo == 2) {
                contra[i] = nums[distNum(gen)];
            }
            else {
                contra[i] = simbolos[distSim(gen)];
            }
        
        }
    }

    return contra;
}

vector<char> leerArchivoCompleto(const string& nombre){
    ifstream archivo(nombre, ios::binary | ios::ate); //Empieza al final del archivo
    if (!archivo) {
        throw runtime_error("No se pudo abrir el archivo");
    }
    streamsize tamano = archivo.tellg(); //Dice en que posición está el cursor //Dice cuanto pesa el archivo
    archivo.seekg(0, ios::beg);  //Devuelve el cursor al inicio
    vector<char> buffer(tamano); //Crea el vector del tamaño exacto del archivo
    if (!archivo.read(buffer.data(), tamano)) { //Lee el archivo y lo mete al buffer //data envía al inicio del vector
        throw runtime_error("Error al leer el archivo");
    }
    return buffer;
}

bool comprobarLineas(string_view datos, string_view objetivo){
    size_t inicio = 0; 
    size_t fin;
           //Busca desde el inicio de la palabra el salto de linea mientras encuentre saltos de linea 
    while ((fin = datos.find('\n', inicio)) != string_view::npos) {
        string_view linea = datos.substr(inicio, fin - inicio); //Agarra toda esa linea
        if (linea == objetivo) { //Revisa si esa linea es la contraseña
            cout << "Contrasena encontrada: " << linea << endl;
            return true;  
        }
        inicio = fin + 1; //Saltamos a la siguiente linea luego del /n 
    }
    //Todavia quedan datos:
    if (inicio < datos.size()) { //Cuando no detecte /n en la última linea, esto hace que lea esa última linea
        string_view linea = datos.substr(inicio);
        if (linea == objetivo) {
            cout << "Contrasena encontrada: " << linea << endl;
            return true;
        }
    }
    return false;
}

bool verificarPwned(const string& contrasena) {  
    vector<char> datos = leerArchivoCompleto("rockyou.txt");
    string_view contenido(datos.data(), datos.size());//La dirección de memoria donde empieza y el tamaño del contenido
    return comprobarLineas(contenido, contrasena);
}


string GenerarPassphrase(int num_palabras) {
    vector<char> buffer = leerArchivoCompleto("wordlist.txt");
    string_view datos(buffer.data(), buffer.size());

    vector<string> palabras;
    size_t inicio = 0, fin;
    while ((fin = datos.find('\n', inicio)) != string_view::npos) {
        palabras.push_back(string(datos.substr(inicio, fin - inicio))); //Agrega cada palabra como índice al vector palabras
        inicio = fin + 1;
    }
    string resultado;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, palabras.size() - 1);
    for (int i = 0; i < num_palabras; i++) {

        if (i > 0) {
         resultado += "-";
        }
        resultado += palabras[dist(gen)];
    }
    return resultado;
}