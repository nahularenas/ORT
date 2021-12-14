#include "iostream"
using namespace std;

template <class T>
class NodoLista
{
public:
  NodoLista<T> *sig;
  T dato;
  NodoLista(T dato);
  NodoLista(T dato, NodoLista<T> *sig);
};

template <class T>
class Lista
{
private:
  NodoLista<T> *inicio;
  NodoLista<T> *fin;
  int cant;

  void vaciarRec(NodoLista<T> *nodo);

  void insertarOrdRec(T dato, NodoLista<T> *&nodo);

  void recBorarElem(NodoLista<T> *&nodo, T dato);

public:
  Lista();

  ~Lista();

  void vaciar();

  void insertarPpio(T dato);

  void insertarFin(T dato);

  void insertarOrd(T dato);

  // Pre: largo > 0
  T obtenerPpio();

  NodoLista<T> *obtenerNodos();

  // Pre: largo > 0
  void borrarPpio();

  bool existeElem(T dato);

  void borrarElem(T dato);

  T *encontrarElem(T dato);

  int largo();

  template <class U>
  friend bool operator<(const Lista<U> &a, const Lista<U> &b);
  template <class U>
  friend bool operator==(const Lista<U> &a, const Lista<U> &b);
};

template <class T>
class Heap
{
private:
  T *heap;
  int length;
  int maxPos;

  void bubbleUp(int pos);

  void bubbleDown(int pos);

  int find(int pos, T *ver);

public:
  Heap(int maxCant);

  ~Heap();

  void insert(T data);

  void increaseHeap();

  T minimum();

  T getMin();

  void deleteMin();

  bool isEmpty();

  int size();
};

template <class T>
class nodeHa
{
public:
  int key;
  T data;
  nodeHa<T> *next;

  nodeHa(int k, T d);
  nodeHa(int k, T d, nodeHa<T> *n);
};

template <class T>
class Hash
{
private:
  nodeHa<T> **hash;
  int userBound;
  int realBound;
  int length_;

  bool isPrime(int n);

  int nextPrime(int num);

  void clear(nodeHa<T> *node);

  unsigned int hashFunction(int e);

  void deleteNodeAux(nodeHa<T> *&t, int k);

public:
  Hash(int max);

  ~Hash();

  // no rep elem
  void insert(int k, T d);

  void deleteNode(int k);

  T find(int k);

  bool exist(int k);

  bool isEmpty();

  int length();
};

class NodoG
{
public:
  int vertice;
  int peso;
  NodoG(int v, int p);
  NodoG();

  friend bool operator==(const NodoG &a, const NodoG &b);
  friend bool operator<(const NodoG &a, const NodoG &b);
  friend bool operator>(const NodoG &a, const NodoG &b);
  friend bool operator<=(const NodoG &a, const NodoG &b);
  friend bool operator>=(const NodoG &a, const NodoG &b);
};

class NodoA
{
public:
  int origen;
  int peso;
  int destino;
  NodoA(int o, int p, int d);
  NodoA();

  friend bool operator==(const NodoA &a, const NodoA &b);
  friend bool operator<(const NodoA &a, const NodoA &b);
  friend bool operator>(const NodoA &a, const NodoA &b);
  friend bool operator<=(const NodoA &a, const NodoA &b);
  friend bool operator>=(const NodoA &a, const NodoA &b);
};

class par
{
public:
  int nodo;
  int nivel;
  par(int no, int ni);

  friend bool operator==(const par &a, const par &b);
  friend bool operator<(const par &a, const par &b);
  friend bool operator>(const par &a, const par &b);
  friend bool operator<=(const par &a, const par &b);
  friend bool operator>=(const par &a, const par &b);
};

class Grafo
{
private:
  int tope;
  int cant;
  Lista<NodoG> **vertices;

  Hash<int> *externoAInterno;
  int *internoExterno;
  Lista<int> *huecos;
  bool esDrigido;

  int verticeNoVisDeMenorDist(int *dist, bool *vis);

public:
  Grafo(int tope, bool dirigido);

  ~Grafo();

  void insertarVertice(int v);

  // Pre: existeVertice(vOri) && existeVertice(vDes)
  void insertarArista(int vOri, int vDes, int peso);

  // Pre: existeVertice(vOri) && existeVertice(vDes)
  void borrarArista(int vOri, int vDes);

  bool existeVertice(int v);

  bool existeArista(int vOri, int vDes);

  int cambioAdy(Lista<par> *&l);

  int *ordenTopo();

  int dijkstra(int posO);

  int kruskal();

  int compConexas();

  int largo();
  // Pre: existeVertice(v)
  void borrarVertice(int v);
};