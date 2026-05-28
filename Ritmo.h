#pragma once
#include <string>
using namespace std;

class RitmoCracker {
public:
    void Menu(int num_beats, int bpm);

private:
    string guardado;
    string CapturarPatron(int num_beats, int bpm);
    int ContarCoincidencias(const string& a, const string& b);
};