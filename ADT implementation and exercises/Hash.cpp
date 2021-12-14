#include "Definiciones.h"

template <class T>
nodeHa<T>::nodeHa(int k, T d) : key(k), data(d), next(NULL) {}

template <class T>
nodeHa<T>::nodeHa(int k, T d, nodeHa<T> *n) : key(k), data(d), next(n) {}

template class nodeHa<int>;

template <class T>
bool Hash<T>::isPrime(int n)
{
    if (n == 2 || n == 3)
        return true;
    if (n <= 1 || n % 2 == 0 || n % 3 == 0)
        return false;
    for (int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

template <class T>
int Hash<T>::nextPrime(int num)
{
    while (!isPrime(++num))
        ;
    return num;
}

template <class T>
void Hash<T>::clear(nodeHa<T> *node)
{
    if (node)
    {
        clear(node->next);
        delete node;
    }
}

template <class T>
unsigned int Hash<T>::hashFunction(int e)
{
    if (e < 0)
        e = -1 * e;
    return e % realBound;
}

template <class T>
void Hash<T>::deleteNodeAux(nodeHa<T> *&t, int k)
{
    if (t)
    {
        if (t->key == k)
        {
            nodeHa<T> *temp = t;
            t = t->next;
            delete temp;
            length_--;
        }
        else
        {
            deleteNodeAux(t->next, k);
        }
    }
}

template <class T>
Hash<T>::Hash(int max)
{
    this->userBound = max;
    this->realBound = nextPrime(max);
    this->hash = new nodeHa<T> *[realBound];
    this->length_ = 0;
    for (int i = 0; i < realBound; this->hash[i++] = NULL)
        ;
}

template <class T>
Hash<T>::~Hash()
{
    for (int i = 0; i < realBound; clear(this->hash[i++]))
        ;
    delete[] this->hash;
}

template <class T>
//! exist(k)
void Hash<T>::insert(int k, T d)
{
    nodeHa<T> *node = new nodeHa<T>(k, d);
    int index = hashFunction(k);
    node->next = hash[index];
    hash[index] = node;
    length_++;
}

template <class T>
void Hash<T>::deleteNode(int k)
{
    int index = hashFunction(k);
    deleteNodeAux(hash[index], k);
}


template <class T>
T Hash<T>::find(int k)
{
    int index = hashFunction(k);
    nodeHa<T> *node = hash[index];
    while (node)
    {
        if (node->key == k)
            return node->data;
        node = node->next;
    }
    return false;
}

template <class T>
bool Hash<T>::exist(int k)
{
    int index = hashFunction(k);
    nodeHa<T> *node = hash[index];
    while (node)
    {
        if (node->key == k)
            return true;
        node = node->next;
    }
    return false;
}

template <class T>
bool Hash<T>::isEmpty()
{
    return length_ == 0;
}

template <class T>
int Hash<T>::length()
{
    return this->length_;
}

template class Hash<int>;