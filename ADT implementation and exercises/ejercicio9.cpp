#include "iostream"
using namespace std;

class Edificio
{
public:
    int inicio;
    int fin;
    int altura;

    Edificio(int i, int f, int h) : inicio(i), fin(f), altura(h) {}
};

class Coordenada
{
public:
    int x, y;
    Coordenada(int x, int y) : x(x), y(y){}
};


void coordeinador(Coordenada* s, Coordenada** res, int &cantRes){
    
    if(cantRes > 0 && res[cantRes-1]->x == s->x){
        if(res[cantRes-1]->y < s->y){
            res[cantRes-1]->y = s->y;
        }
    }else if(cantRes > 0 && res[cantRes-1]->y == s->y){
        return;
    }else{
        res[cantRes] = s;
        cantRes++;
    }
}

Coordenada** mergeSilueta(Coordenada** s1, int& cantS1, Coordenada** s2, int& cantS2, int& largoSilueta){
    Coordenada** res = new Coordenada*[cantS1+cantS2];
    int cant = 0;
    int i = 0;
    int j = 0;
    int h1 = 0;
    int h2 = 0;
    Coordenada* max;
    while(i < cantS1 && j < cantS2){
        if(s1[i]->x < s2[j]->x){
            h1 = s1[i]->y;
            int max = (h1 < h2)? h2 : h1;
            coordeinador(new Coordenada(s1[i]->x, max), res, cant);
            i++;
        }else if(s1[i]->x == s2[j]->x){
            h1 = s1[i]->y;
            h2 = s2[j]->y;
            int max = (h1 < h2)? h2 : h1;
            coordeinador(new Coordenada(s2[j]->x, max), res, cant);
            i++;
            j++;
        }else{
            h2 = s2[j]->y;
            int max = (h1 < h2)? h2 : h1;
            coordeinador(new Coordenada(s2[j]->x, max), res, cant);
            j++;
        }
    }

    while (i < cantS1) {
        coordeinador(s1[i], res, cant);
        i++;
    }
    while (j < cantS2) {
        coordeinador(s2[j], res, cant);
        j++;
    }
    largoSilueta = cant;
    return res;
}

Coordenada** dAndQ (Edificio **& edif, int desde, int hasta, int &largoSilueta){
    if(desde == hasta){
        Coordenada* ini = new Coordenada(edif[desde]->inicio, edif[desde]->altura);
        Coordenada* fin = new Coordenada(edif[desde]->fin, 0);
        Coordenada** res = new Coordenada*[2];
        res[0]=ini;
        res[1]=fin;
        largoSilueta += 2;
        return res;
    }
    int largoI = 0;
    int largoD = 0;
    Coordenada** llamadaI = dAndQ(edif, desde, (hasta+desde)/2, largoI);
    Coordenada** llamadaD = dAndQ(edif, (hasta+desde)/2 + 1, hasta, largoD);
    Coordenada** res = mergeSilueta(llamadaI, largoI, llamadaD, largoD, largoSilueta);
    delete[] llamadaD;
    delete[] llamadaI;
    return res;
}

int main()
{
    int cantEdif;
    int maximoFinal = 0;
    cin >> cantEdif;
    Edificio **arrEdif = new Edificio *[cantEdif];
    for (size_t i = 0; i < cantEdif; i++)
    {
        int x1, x2, y;
        cin >> x1;
        cin >> x2;
        cin >> y;
        arrEdif[i] = new Edificio(x1, x2, y);
    }
    int total = 0;
    Coordenada** cr = dAndQ (arrEdif, 0, cantEdif-1, total);
    for (size_t i = 0; i < total; i++)
    {
        cout << cr[i]->x << ' ' << cr[i]->y <<endl;
        delete cr[i];
    }

    delete[] cr;

    for (size_t i = 0; i < cantEdif; i++)
    {
        delete arrEdif[i];
    }
    delete[] arrEdif;

    return 0;
}