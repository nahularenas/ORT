#include "iostream"
using namespace std;

struct nodeA
{
  nodeA *l;
  nodeA *r;
  int balance;
  int data;
  int occurrence;
  nodeA(int d);
};

class Avl{
  private:
  nodeA* root;
  bool heightVaried;
  void insertion(nodeA *&node, int d);
  void makeEmpty(nodeA *&node);
  public:
  Avl();
  ~Avl();
  void insert(int data);
  nodeA* getRoot();
};