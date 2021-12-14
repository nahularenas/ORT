#include "iostream"
using namespace std;

class Ejercicio
{
public:
    int puntaje;
    int peso;
    int linea;

    Ejercicio(int pu, int pe, int l) : puntaje(pu), peso(pe), linea(l) {}
};

void maximoPuntaje(int pesoM, int lineasM, int cantEj, Ejercicio **&listaEj, int ejActual, int solActual, int &solOptima)
{
    if (cantEj == ejActual)
    {
        if (solActual > solOptima)
            solOptima = solActual;
    }
    else
    {
        // No uso al elemento actual
        maximoPuntaje(pesoM, lineasM, cantEj, listaEj, ejActual + 1, solActual, solOptima);
        // Intento usar al elemento actual
        Ejercicio *ej = listaEj[ejActual];
        if (ej->peso < pesoM && ej->linea < lineasM)
        {
            pesoM -= ej->peso;
            lineasM -= ej->linea;
            solActual += ej->puntaje;
            maximoPuntaje(pesoM, lineasM, cantEj, listaEj, ejActual + 1, solActual, solOptima);
        }
    }
}

int main()
{
    int cantidadA, pesoMB, pesoL;
    cin >> cantidadA;
    cin >> pesoMB;
    cin >> pesoL;
    Ejercicio **listaEj = new Ejercicio *[cantidadA];
    for (size_t i = 0; i < cantidadA; i++)
    {
        int peso, lineas, puntaje;
        cin >> peso;
        cin >> lineas;
        cin >> puntaje;
        listaEj[i] = new Ejercicio(puntaje, peso, lineas);
    }
    int solOptima = -1;
    maximoPuntaje(pesoMB, pesoL, cantidadA, listaEj, 0, 0, solOptima);
    cout << solOptima;
    for (size_t i = 0; i < cantidadA; i++)
    {
        delete listaEj[i];
    }
    delete[] listaEj;
    return 0;
}