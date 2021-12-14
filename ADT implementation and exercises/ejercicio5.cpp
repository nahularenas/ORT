#include "Definiciones.h"

int main()
{
    int tope;
    cin >> tope;
    Grafo* g = new Grafo(tope, true);
    for (size_t i = 0; i < tope; i++)
    {
        g->insertarVertice(i+1);
    }
    
    int cantidadAristas;
    cin >> cantidadAristas;
    for (size_t i = 0; i < cantidadAristas; i++)
    {
        int desde, hasta, ponderacion;
        cin >> desde;
        cin >> hasta;
        cin >> ponderacion;
        g->insertarArista(desde, hasta, ponderacion);
    }
    int cantidadComparaciones;
    cin >> cantidadComparaciones;
    for (size_t i = 0; i < cantidadComparaciones; i++)
    {
        int desde;
        cin >> desde;
        g->dijkstra(desde);
    }
    delete g;
    return 0;
}