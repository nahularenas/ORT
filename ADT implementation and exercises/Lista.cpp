#include "Definiciones.h"

template <class T>
NodoLista<T>::NodoLista(T dato) : dato(dato), sig(NULL) {}

template <class T>
NodoLista<T>::NodoLista(T dato, NodoLista<T> *sig) : dato(dato), sig(sig) {}

template class NodoLista<int>;
template class NodoLista<NodoG>;
template class NodoLista<NodoA>;
template class NodoLista<par>;


template <class T>
void Lista<T>::vaciarRec(NodoLista<T> *nodo)
{
    if (nodo)
    {
        vaciarRec(nodo->sig);
        delete nodo;
    }
}

template <class T>
void Lista<T>::insertarOrdRec(T dato, NodoLista<T> *&nodo)
{
    if (dato <= nodo->dato)
    {
        nodo = new NodoLista<T>(dato, nodo);
        cant++;
    }
    else
    {
        insertarOrdRec(dato, nodo->sig);
    }
}

template <class T>
Lista<T>::Lista() : inicio(NULL), fin(NULL), cant(0) {}

template <class T>
Lista<T>::~Lista()
{
    vaciar();
}

template <class T>
void Lista<T>::vaciar()
{
    vaciarRec(inicio);
    inicio = fin = NULL;
    cant = 0;
}

template <class T>
void Lista<T>::insertarPpio(T dato)
{
    NodoLista<T> *nodo = new NodoLista<T>(dato);
    nodo->sig = inicio;
    inicio = nodo;
    if (fin == NULL)
        fin = inicio;
    cant++;
}

template <class T>
void Lista<T>::insertarFin(T dato)
{
    NodoLista<T> *nuevo = new NodoLista<T>(dato);
    if (fin == NULL)
        fin = inicio = nuevo;
    else
    {
        fin->sig = nuevo;
        fin = fin->sig;
    }
    cant++;
}

template <class T>
void Lista<T>::insertarOrd(T dato)
{
    if (!inicio || dato <= inicio->dato)
    {
        insertarPpio(dato);
    }
    else if (dato >= fin->dato)
    {
        insertarFin(dato);
    }
    else
    {
        insertarOrdRec(dato, inicio->sig);
    }
}

template <class T>
T Lista<T>::obtenerPpio()
{
    return inicio->dato;
}
//i < largo();
template <class T>
NodoLista<T> * Lista<T>::obtenerNodos()
{
    return inicio;
}

template <class T>
void Lista<T>::borrarPpio()
{
    NodoLista<T> *aBorrar = inicio;
    inicio = inicio->sig;
    delete aBorrar;
    cant--;
    if (!inicio)
    {
        fin = NULL;
    }
}

template <class T>
bool Lista<T>::existeElem(T dato)
{
    NodoLista<T> *it = inicio;
    while (it != NULL)
    {
        if (it->dato == dato)
            return true;
        it = it->sig;
    }
    return false;
}

template <class T>
T* Lista<T>::encontrarElem(T dato)
{
    NodoLista<T> *it = inicio;
    while (it != NULL)
    {
        if (it->dato == dato){
            T* encontrado = &it->dato;
            return encontrado;
        }
        it = it->sig;
    }
    return NULL;
}

template <class T>
void Lista<T>::recBorarElem(NodoLista<T> *&nodo, T dato)
{
    if (nodo != NULL)
    {
        if (nodo->dato == dato)
        {
            NodoLista<T> *temp = nodo;
            nodo = nodo->sig;
            delete temp;
        }
        else
        {
            recBorarElem(nodo->sig, dato);
        }
    }
}

template <class T>
void Lista<T>::borrarElem(T dato)
{
    recBorarElem(inicio, dato);
}

template <class T>
int Lista<T>::largo()
{
    return cant;
}

template <class U>
bool operator<(const Lista<U> &a, const Lista<U> &b)
{
    return a.obtenerPpio() < b.obtenerPpio();
}

template <class U>
bool operator==(const Lista<U> &a, const Lista<U> &b)
{
    return a.obtenerPpio() == b.obtenerPpio();
}

template class Lista<int>;
template class Lista<NodoG>;
template class Lista<NodoA>;
template class Lista<par>;