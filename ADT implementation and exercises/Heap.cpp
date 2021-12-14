#include "Definiciones.h"

template <class T>
void Heap<T>::bubbleUp(int pos)
{
  if (pos > 1)
  {
    T data = heap[pos];
    if (data < heap[pos / 2])
    {
      heap[pos] = heap[pos / 2];
      heap[pos / 2] = data;
      bubbleUp(pos / 2);
    }
  }
}

template <class T>
void Heap<T>::bubbleDown(int pos)
{
  int min = pos;
  int l = 2 * pos;
  int r = 2 * pos + 1;

  if (l <= length && heap[l] <= heap[min])
    min = l;

  if (r <= length && heap[r] <= heap[min])
    min = r;

  if (min != pos)
  {
    T temp = heap[pos];
    heap[pos] = heap[min];
    heap[min] = temp;

    bubbleDown(min);
  }
}

template <class T>
Heap<T>::Heap(int maxPos)
{
  this->length = 0;
  this->maxPos = maxPos + 1;
  this->heap = new T[maxPos + 1];
}

template <class T>
Heap<T>::~Heap()
{
  delete[] this->heap;
}

template <class T>
void Heap<T>::increaseHeap()
{
  int n = 2*this->maxPos;
  T *newHeap = new T[n];
  for (size_t i = 1; i < this->maxPos; i++)
    newHeap[i] = this->heap[i];
  T* temp = this->heap;
  this->heap = newHeap;
  delete[] temp;
  this->maxPos = n;
}

template <class T>
void Heap<T>::insert(T data)
{
  if (this->length == this->maxPos)
    increaseHeap();
  this->length++;
  this->heap[length] = data;
  bubbleUp(length);
}

template <class T>
T Heap<T>::minimum()
{
  return this->heap[1];
}

template <class T>
T Heap<T>::getMin()
{
  T res = heap[1];
  heap[1] = heap[length];
  length--;
  bubbleDown(1);
  return res;
}

template <class T>
void Heap<T>::deleteMin()
{
  T res = heap[1];
  heap[1] = heap[length];
  length--;
  bubbleDown(0);
}

template <class T>
bool Heap<T>::isEmpty()
{
  return this->length == 0;
}

template <class T>
int Heap<T>::size()
{
  return this->length;
}

template class Heap<NodoG>;
template class Heap<NodoA>;