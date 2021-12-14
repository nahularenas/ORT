#include "Definiciones.h"

int main()
{
    int filas, columnas;
    cin >> filas;
    cin >> columnas;
    int **matriz = new int *[filas + 2];
    Grafo *g = new Grafo(filas * columnas, false);
    Lista<par> *l = new Lista<par>();
    for (int i = 0; i < filas + 2; i++)
    {
        matriz[i] = new int[columnas + 2];
        for (int j = 0; j < columnas + 2; j++)
        {
            if (j == 0 || j == columnas + 1 || i == 0 || i == filas + 1)
            {
                matriz[i][j] = 0;
            }
            else
            {
                int vertice;
                cin >> vertice;
                matriz[i][j] = vertice;
                if (vertice != 0)
                {
                    g->insertarVertice(vertice);
                    if (vertice > 0)
                        l->insertarFin(par(vertice, 0));
                }
            }
        }
    }
    for (size_t i = 1; i <= filas; i++)
    {
        for (size_t j = 1; j <= columnas; j++)
        {
            if (matriz[i][j] != 0)
            {
                if (matriz[i - 1][j] != 0)
                {
                    g->insertarArista(matriz[i][j], matriz[i - 1][j], 1);
                }
                if (matriz[i + 1][j] != 0)
                {
                    g->insertarArista(matriz[i][j], matriz[i + 1][j], 1);
                }
                if (matriz[i][j - 1] != 0)
                {
                    g->insertarArista(matriz[i][j], matriz[i][j - 1], 1);
                }
                if (matriz[i][j + 1] != 0)
                {
                    g->insertarArista(matriz[i][j], matriz[i][j + 1], 1);
                }
            }
        }
    }
    cout << g->cambioAdy(l);

    for (size_t i = 0; i < filas+2; i++)
    {
        delete[] matriz[i];
    }
    delete[] matriz;
    delete g;
    delete l;
    return 0;
}