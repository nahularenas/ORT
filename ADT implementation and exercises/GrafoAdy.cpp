#include "Definiciones.h"

NodoG::NodoG(int v, int p)
{
    vertice = v;
    peso = p;
}

NodoG::NodoG()
{
    vertice = 0;
    peso = 0;
}

bool operator==(const NodoG &a, const NodoG &b)
{
    return a.vertice == b.vertice;
}

bool operator<(const NodoG &a, const NodoG &b)
{
    return a.peso < b.peso;
}

bool operator>(const NodoG &a, const NodoG &b)
{
    return a.peso > b.peso;
}

bool operator<=(const NodoG &a, const NodoG &b)
{
    return a.peso < b.peso || a.peso == b.peso;
}

bool operator>=(const NodoG &a, const NodoG &b)
{
    return a.peso > b.peso || a.peso == b.peso;
}

Grafo::Grafo(int tope, bool dirigido)
{
    this->tope = tope;
    cant = 0;
    esDrigido = dirigido;
    vertices = new Lista<NodoG> *[tope];
    huecos = new Lista<int>;
    for (size_t i = 0; i < tope; i++)
    {
        vertices[i] = NULL;
        huecos->insertarFin(i);
    }
    internoExterno = new int[tope];
    externoAInterno = new Hash<int>(tope);
}

Grafo::~Grafo()
{
    for (int i = 0; i < tope; i++)
    {
        delete vertices[i];
    }
    delete[] vertices;
    delete[] internoExterno;
    delete externoAInterno;
}

void Grafo::insertarVertice(int v)
{
    if (huecos->largo() != 0)
    {
        int pos = huecos->obtenerPpio();
        huecos->borrarPpio();
        externoAInterno->insert(v, pos);
        internoExterno[pos] = v;
        vertices[pos] = new Lista<NodoG>();
        cant++;
    }
}

// Pre: existeVertice(vOri) && existeVertice(vDes)
void Grafo::insertarArista(int vOri, int vDes, int peso = 1)
{
    int pos = externoAInterno->find(vOri);
    int des = externoAInterno->find(vDes);
    NodoG n(des, peso);
    vertices[pos]->insertarPpio(n);
    if (!esDrigido)
    {
        NodoG e(pos, peso);
        vertices[des]->insertarPpio(n);
    }
}

// Pre: existeVertice(vOri) && existeVertice(vDes) && existeArista(vOri, vDes)
void Grafo::borrarArista(int vOri, int vDes)
{
    int pos = externoAInterno->find(vOri);
    int des = externoAInterno->find(vDes);
    NodoG n(des, 1);
    vertices[pos]->borrarElem(n);
    if (!esDrigido)
    {
        NodoG e(pos, 1);
        vertices[des]->borrarElem(n);
    }
}

bool Grafo::existeVertice(int v)
{
    return externoAInterno->exist(v);
}

// Pre: existeVertice(v)
void Grafo::borrarVertice(int v)
{
    int pos = externoAInterno->find(v);
    externoAInterno->deleteNode(v);
    huecos->insertarFin(pos);
    vertices[pos]->vaciar();
    delete vertices[pos];
    vertices[pos] = NULL;
    cant--;
}

bool Grafo::existeArista(int vOri, int vDes)
{
    int pos = externoAInterno->find(vOri);
    int bus = externoAInterno->find(vDes);
    NodoG n(bus, 1);
    return vertices[pos]->existeElem(n);
}

int Grafo::largo()
{
    return cant;
}

int *Grafo::ordenTopo()
{
    int *entrada = new int[tope];
    for (int i = 0; i < tope; i++) // O(v);
        entrada[i] = 0;

    for (int i = 0; i < tope; i++) // O(v+e);
    {
        if (vertices[i] != NULL)
        {
            NodoLista<NodoG> *it = vertices[i]->obtenerNodos();
            while (it != NULL)
            {
                entrada[it->dato.vertice]++;
                it = it->sig;
            }
        }
    }

    Lista<int> *solitarios = new Lista<int>();
    for (int i = 0; i < tope; i++) // O(v);
    {
        if (vertices[i] != NULL && entrada[i] == 0)
        {
            solitarios->insertarFin(i);
        }
    }

    int *res = new int[tope + 1];
    int resp = 0;
    int cantProcesados = 0;
    while (solitarios->largo() > 0) // O(v+e)
    {
        int pos = solitarios->obtenerPpio();
        solitarios->borrarPpio();

        res[resp] = internoExterno[pos];
        resp++;
        NodoLista<NodoG> *it = vertices[pos]->obtenerNodos();
        while (it != NULL)
        {
            entrada[it->dato.vertice]--;
            if (entrada[it->dato.vertice] == 0)
                solitarios->insertarFin(it->dato.vertice);
            it = it->sig;
        }
        cantProcesados++;
    }
    if (cantProcesados < cant)
    {
        res[tope] = 1;
    }
    else
    {
        res[tope] = 0;
    }

    delete[] entrada;
    delete solitarios;

    return res;
}

int Grafo::verticeNoVisDeMenorDist(int *dist, bool *vis)
{
    int posMin = -1, min = 999999;
    for (int i = 0; i < tope; i++)
    {
        if (!vis[i] && dist[i] < min)
        {
            min = dist[i];
            posMin = i;
        }
    }
    return posMin;
}

int Grafo::dijkstra(int posOrigen)
{
    // Paso de nombre externo a nombre interno
    int posO = externoAInterno->find(posOrigen);

    // Declaro e Inicializo vectores
    int *dist = new int[tope];
    bool *vis = new bool[tope];
    int INF = 999999;
    for (int i = 0; i < tope; dist[i] = INF, vis[i] = false, i++)
    {
    };
    Heap<NodoG> *colaMenorDistancia = new Heap<NodoG>(tope * tope); // V^2
    // Inicializo la distancia del origen con 0
    dist[posO] = 0;
    colaMenorDistancia->insert(NodoG(posO, 0));
    // Realizo proceso reiterativo
    while (!colaMenorDistancia->isEmpty())
    {
        NodoG pos = colaMenorDistancia->getMin();
        vis[pos.vertice] = true;
        NodoLista<NodoG> *it = vertices[pos.vertice]->obtenerNodos();
        while (it != NULL)
        {
            int v = it->dato.vertice;
            int peso = it->dato.peso;
            if (!vis[v] && dist[v] > dist[pos.vertice] + peso)
            {
                dist[v] = dist[pos.vertice] + peso;
                colaMenorDistancia->insert(NodoG(v, dist[v]));
            }
            it = it->sig;
        }
    }

    for (int i = 0; i < tope; i++)
    {
        if (dist[i] != 0)
        {
            cout << dist[i] << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }

    delete[] dist;
    delete[] vis;
    delete colaMenorDistancia;
}

NodoA::NodoA(int o, int p, int d)
{
    origen = o;
    peso = p;
    destino = d;
}

NodoA::NodoA()
{
    origen = 0;
    peso = 0;
    destino = 0;
}

bool operator==(const NodoA &a, const NodoA &b)
{
    return a.origen == b.origen && a.destino == b.destino;
}

bool operator<(const NodoA &a, const NodoA &b)
{
    return a.peso < b.peso;
}

bool operator>(const NodoA &a, const NodoA &b)
{
    return a.peso > b.peso;
}

bool operator<=(const NodoA &a, const NodoA &b)
{
    return a.peso < b.peso || a.peso == b.peso;
}

bool operator>=(const NodoA &a, const NodoA &b)
{
    return a.peso > b.peso || a.peso == b.peso;
}

int findArray(int *v, int pos)
{
    if (v[pos] == pos)
        return pos;
    int aux = findArray(v, v[pos]);
    v[pos] = aux;
    return aux;
}

bool unionArray(int *&v, int posA, int posB)
{
    int rootA = findArray(v, posA);
    int rootB = findArray(v, posB);
    if (rootA == rootB)
    {
        return false;
    }
    (rootA > rootB) ? v[rootB] = rootA : v[rootA] = rootB;
    return true;
}

int Grafo::kruskal()
{
    Heap<NodoA> *Aristas = new Heap<NodoA>(tope * tope);
    int *Componentes = new int[tope];
    int pesoArbol = 0;
    int cantidadA = 0;
    for (int i = 0; i < tope; i++)
    {
        Componentes[i] = i;
        NodoLista<NodoG> *aux = vertices[i]->obtenerNodos();
        while (aux)
        {
            Aristas->insert(NodoA(i, aux->dato.peso, aux->dato.vertice));
            aux = aux->sig;
        }
    }

    while (!Aristas->isEmpty())
    {
        NodoA aux = Aristas->getMin();
        if (unionArray(Componentes, aux.origen, aux.destino))
        {
            pesoArbol += aux.peso;
            cantidadA++;
        }
    }
    if (cantidadA != tope - 1)
        pesoArbol = -1;
    delete Componentes;
    delete Aristas;
    return pesoArbol;
}

int Grafo::compConexas()
{
    Lista<NodoA> *Aristas = new Lista<NodoA>();
    int *Componentes = new int[tope];
    for (int i = 0; i < tope; i++)
    {
        Componentes[i] = i;
        NodoLista<NodoG> *aux = vertices[i]->obtenerNodos();
        while (aux)
        {
            Aristas->insertarPpio(NodoA(i, aux->dato.peso, aux->dato.vertice));
            aux = aux->sig;
        }
    }

    while (Aristas->largo() > 0)
    {
        NodoA aux = Aristas->obtenerPpio();
        unionArray(Componentes, aux.origen, aux.destino);
        Aristas->borrarPpio();
    }

    Lista<int> *l = new Lista<int>();
    for (size_t i = 0; i < tope; i++)
    {
        findArray(Componentes, i);
        if (!l->existeElem(Componentes[i]))
        {
            l->insertarPpio(Componentes[i]);
        }
    }
    int total = l->largo();
    delete l;
    delete Componentes;
    delete Aristas;
    return total;
}

par::par(int no, int ni): nodo(no), nivel(ni){}

bool operator==(const par &a, const par &b)
{
    return a.nodo == b.nodo && a.nivel == b.nivel;
}

bool operator<(const par &a, const par &b)
{
    return a.nivel < b.nivel;
}

bool operator>(const par &a, const par &b)
{
    return a.nivel > b.nivel;
}

bool operator<=(const par &a, const par &b)
{
    return a.nivel < b.nivel || a.nivel == b.nivel;
}

bool operator>=(const par &a, const par &b)
{
    return a.nivel > b.nivel || a.nivel == b.nivel;
}

int Grafo::cambioAdy(Lista<par> *&l)
{
    int max = 0;
    while (l->largo() > 0)
    {
        par actual = l->obtenerPpio();
        l->borrarPpio();
        if(actual.nivel > max)
            max = actual.nivel;

        int pos = externoAInterno->find(actual.nodo);
        NodoLista<NodoG> *it = vertices[pos]->obtenerNodos();
        while (it)
        {
            int ver = internoExterno[it->dato.vertice];
            if (ver < 0)
            {
                externoAInterno->deleteNode(ver);
                ver = ver * (-1);
                externoAInterno->insert(ver, it->dato.vertice);
                internoExterno[it->dato.vertice] = ver;
                l->insertarFin(par(ver, actual.nivel + 1));
            }
            it = it->sig;
        }
    }
    return max;
}