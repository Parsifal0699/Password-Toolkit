#pragma once
using namespace std;
#include <string>
#include <iostream>

class Cracker
{
public:
    bool Brute(string& c_objetivo, string actual, short max_longitud);  
    void Dict(string& c_objetivo);

private:
    string letras = "abcdefghijklmnopqrstuvwxyz";
    string nums = "0123456789";
    string simb = "!@#$%^&*()-_=+[]{};:,.?/|<>~`";
};