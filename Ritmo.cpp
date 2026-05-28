#include "Ritmo.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#ifdef _WIN32
#include <portaudio.h>
extern "C" __declspec(dllimport) int __stdcall Beep(unsigned long, unsigned long);
#endif
using namespace std;

const int SAMPLE_RATE = 44100;
const int FRAMES = 512;
const float UMBRAL = 0.85f;
const int INTENTOS_MAX = 3;
bool aplauso_detectado = false;

#ifdef _WIN32
static int callback(const void* input, void*, unsigned long frames, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags, void*) {
    
    const float* samples = (const float*) input;
    if (!samples) return paContinue;

    float volumen_max = 0;
    for (unsigned long i = 0; i < frames; i++) {
        float v = fabs(samples[i]);
        if (v > volumen_max) volumen_max = v;
    }
    if (volumen_max > UMBRAL) aplauso_detectado = true;
    return paContinue;
}
#endif

int RitmoCracker::ContarCoincidencias(const string& a, const string& b) {
    int coincidencias = 0;
    for (int i = 0; i < (int)a.length(); i++) {
        if (a[i] == b[i]) coincidencias++;
    }
    return coincidencias;
}

string RitmoCracker::CapturarPatron(int num_beats, int bpm) {
#ifdef _WIN32
    int ms_por_beat = 60000 / bpm;
    int subdivisiones = num_beats * 2;
    int ms_por_sub = ms_por_beat / 2;
    string patron = "";

    Pa_Initialize();
    PaStream* stream;
    Pa_OpenDefaultStream(&stream, 1, 0, paFloat32, SAMPLE_RATE, FRAMES, callback, nullptr);
    Pa_StartStream(stream);

    Beep(600, 100);
    cout << "1" << endl;
    this_thread::sleep_for(chrono::milliseconds(ms_por_beat));
    Beep(600, 100);
    cout << "2" << endl;
    this_thread::sleep_for(chrono::milliseconds(ms_por_beat));
    Beep(600, 100);
    cout << "3" << endl;
    this_thread::sleep_for(chrono::milliseconds(ms_por_beat));
    Beep(600, 100);
    cout << "4" << endl << endl;
    this_thread::sleep_for(chrono::milliseconds(ms_por_beat));

    for (int i = 0; i < subdivisiones; i++) {
        aplauso_detectado = false;
        if (i % 2 == 0) {
            Beep(1000, 100);
            cout << "Beat " << (i/2 + 1) << "/" << num_beats << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(ms_por_sub));
        if (aplauso_detectado) {
            patron += "1";
            cout << " *" << endl;
        }
        else patron += "0";
    }

    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();
    return patron;
#else
    string patron;
    cout << "Escribe tu patron (16 caracteres, 1=golpe 0=silencio)" << endl;
    cout << "Ejemplo: 1010001010000000" << endl;
    cin >> patron;
    return patron;
#endif
}

void RitmoCracker::Menu(int num_beats, int bpm) {
    int total_casillas = num_beats * 2;
    int minimo_coincidencias = (total_casillas * 85) / 100;
    while (true) {
        int opcion;
        cout << endl;
        cout << "1. Guardar contrasena" << endl;
        cout << "2. Probar contrasena" << endl;
        cout << "3. Borrar contrasena" << endl;
        cout << "4. Salir" << endl;
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            cout << endl << "\t\tAplaude en los beats que quieras" << endl << endl;
            guardado = CapturarPatron(num_beats, bpm);
            cout << "Contrasena guardada" << endl;
        }
        else if (opcion == 2) {
            if (guardado.empty()) {
                cout << "No hay contrasena guardada" << endl;
                continue;
            }
            cout << endl << "Usa tu contrasena de audio para acceder" << endl;
            bool accedio = false;
            for (int intento = 1; intento <= INTENTOS_MAX; intento++) {
                cout << endl << "Intento " << intento << "/" << INTENTOS_MAX << endl << endl;
                string actual = CapturarPatron(num_beats, bpm);
                int coincidencias = ContarCoincidencias(guardado, actual);
                if (coincidencias >= minimo_coincidencias) {
                    cout << "\t\tAccediste" << endl;
                    accedio = true;
                    break;
                }
                else cout << "\t\tNo coincide" << endl;
            }
            if (!accedio) cout << "No tienes acceso" << endl;
        }
        else if (opcion == 3) {
            if (guardado.empty()) cout << "No hay contrasena guardada" << endl;
            else {
                guardado = "";
                cout << "Contrasena borrada" << endl;
            }
        }
        else if (opcion == 4) break;
    }
}