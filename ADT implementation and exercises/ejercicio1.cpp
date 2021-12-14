#include "Avl.h"

void inOrder(nodeA *node)
{
    if (node != NULL)
    {
        inOrder(node->l);
        for (int i = 0; i < node->occurrence; i++)
        {
            cout << node->data << endl;
        }
        inOrder(node->r);
    }
}

int main()
{
    Avl *t = new Avl();

    int length;
    cin >> length;
    int x;
    for (size_t i = 0; i < length; i++)
    {
        cin >> x;
        t->insert(x);
    }
    nodeA *root = t->getRoot();
    inOrder(root);
    delete t;
    return 0;
}