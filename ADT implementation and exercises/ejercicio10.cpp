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

int max(int x, int y){
    return (x > y)? x : y;
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

    int ***matDP = new int **[cantidadA];

    for (int i = 0; i < cantidadA; i++)
    {
        matDP[i] = new int *[pesoL + 1];
    }

    for (int i = 0; i < cantidadA; i++)
    {
        for (int j = 0; j <= pesoL; j++)
        {
            matDP[i][j] = new int[pesoMB + 1];
            matDP[i][j][0] = 0;
        }
    }

    for (int i = 0; i < cantidadA; i++)
    {
        for (int k = 0; k <= pesoMB; k++)
        {
            matDP[i][0][k] = 0;
        }
    }


    for (int j = 1; j <= pesoL; j++)
    {
        for (size_t k = 1; k <= pesoMB; k++)
        {
            matDP[0][j][k] = (j < listaEj[0]->linea || k < listaEj[0]->peso) ? 0 : listaEj[0]->puntaje;
        }
    }

    for (int i = 1; i < cantidadA; i++)
    {
        for (size_t j = 1; j <= pesoL; j++)
        {
            for (size_t k = 1; k <= pesoMB; k++)
            {
                if (j < listaEj[i]->linea || k < listaEj[i]->peso)
                {
                    matDP[i][j][k] = matDP[i - 1][j][k];
                }
                else
                {
                    matDP[i][j][k] = max(matDP[i - 1][j][k], matDP[i - 1][j - listaEj[i]->linea][k - listaEj[i]->peso] + listaEj[i]->puntaje); 
                }
            }
        }
    }

    cout << matDP[cantidadA-1][pesoL][pesoMB];

    for (size_t i = 0; i < cantidadA; i++)
    {
        delete listaEj[i];
        for (int j = 0; j <= pesoL; j++)
        {
            delete[] matDP[i][j]; 
        }
        delete[] matDP[i];
    }
    delete[] listaEj;
    delete[] matDP;


    return 0;
}