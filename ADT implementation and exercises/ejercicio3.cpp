#include "iostream"
using namespace std;

class Node
{
public:
  int data;
  Node *next;
  Node(int d) : data(d), next(NULL) {}
};

class List
{
private:
  int length_;
  Node *head;
  Node *tail;

public:
  List()
  {
    length_ = 0;
    head = tail = NULL;
  }

  ~List()
  {
    Node *n = this->head;
    Node *temp = NULL;
    while (n != NULL)
    {
      temp = n;
      n = n->next;
      delete temp;
    }
    tail = NULL;
  }

  bool isEmpty()
  {
    return head == NULL;
  }

  void push(int data)
  {
    Node *node = new Node(data);
    if (this->isEmpty())
      tail = head = node;
    else
    {
      tail->next = node;
      tail = node;
    }
    length_++;
  }

  int length()
  {
    return length_;
  }

  void deleteMin()
  {
    if (head != NULL)
    {
      Node *temp = head;
      head = head->next;
      delete temp;
      if (length() == 1)
        tail = NULL;
      length_--;
    }
  }

  int getMin()
  {
    return head->data;
  }
};

class Heap
{
private:
  List **heap;
  int length;
  int maxPos;

  bool min(List *l1, List *l2)
  {
    return (l1->getMin() < l2->getMin()) ? true : false;
  }

  void bubbleUp(int pos)
  {
    if (pos > 1)
    {
      List *data = heap[pos];
      if (min(data, heap[pos / 2]))
      {
        heap[pos] = heap[pos / 2];
        heap[pos / 2] = data;
        bubbleUp(pos / 2);
      }
    }
  }

  void bubbleDown(int pos)
  {
    int min = pos;
    int l = 2 * pos;
    int r = 2 * pos + 1;

    if (l <= length && heap[l]->getMin() < heap[min]->getMin())
      min = l;

    if (r <= length && heap[r]->getMin() < heap[min]->getMin())
      min = r;

    if (min != pos)
    {
      List *temp = heap[pos];
      heap[pos] = heap[min];
      heap[min] = temp;

      bubbleDown(min);
    }
  }

public:
  Heap(int maxPos)
  {
    this->length = 0;
    this->maxPos = maxPos + 1;
    this->heap = new List *[maxPos + 1];
  }

  ~Heap()
  {
    delete[] this->heap;
  }

  void insert(List *data)
  {
    this->length++;
    this->heap[length] = data;
    bubbleUp(length);
  }

  List *minimum()
  {
    return this->heap[1];
  }

  int getMin()
  {
    int min = heap[1]->getMin();
    if (heap[1]->length() == 1)
    {
      List *temp = heap[1];
      heap[1]->deleteMin();
      heap[1] = heap[length];
      delete temp;
      length--;
    }
    else
    {
      heap[1]->deleteMin();
    }
    bubbleDown(1);
    return min;
  }

  bool isEmpty()
  {
    return this->length == 0;
  }

  int hLength()
  {
    return this->length;
  }
};

int main()
{
  int k;
  cin >> k;
  Heap *h = new Heap(k);
  for (size_t i = 0; i < k; i++)
  {
    int n;
    cin >> n;
    List *l = new List();
    for (size_t i = 0; i < n; i++)
    {
      int x;
      cin >> x;
      l->push(x);
    }
    if (!l->isEmpty())
    {
      h->insert(l);
    }
  }

  while (!h->isEmpty())
  {
    int x = h->getMin();
    cout << x << endl;
  }

  delete h;

  return 0;
}
