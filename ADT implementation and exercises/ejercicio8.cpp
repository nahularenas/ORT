#include "Definiciones.h"

int main()
{
    int tope;
    cin >> tope;
    Grafo* g = new Grafo(tope, false);
    for (size_t i = 0; i < tope; i++)
    {
        g->insertarVertice(i+1);
    }
    
    int cantidadAristas;
    cin >> cantidadAristas;
    for (size_t i = 0; i < cantidadAristas; i++)
    {
        int desde, hasta;
        cin >> desde;
        cin >> hasta;
        g->insertarArista(desde, hasta, 1);
    }
    cout << g->compConexas();
    delete g;
    return 0;
}