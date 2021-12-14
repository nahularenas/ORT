#include "Avl.h"

nodeA::nodeA(int d){
    l = NULL;
    r = NULL;
    data = d;
    balance = 0;
    occurrence = 1;
}

void Avl::insertion(nodeA *&node, int d)
{
    nodeA *lSubtree;
    nodeA *rSubtree;
    if (node == NULL)
    {
        node = new nodeA(d);
        heightVaried = true;
    }
    else if (node->data > d)
    {
        insertion(node->l, d);
        if (heightVaried)
        {
            switch (node->balance)
            {
            case 1:
                node->balance = 0;
                heightVaried = false;
                break;
            case 0:
                node->balance = -1;
                break;
            case -1:
                lSubtree = node->l;
                if (lSubtree->balance == -1)
                {
                    //LL
                    node->l = lSubtree->r;
                    lSubtree->r = node;
                    node->balance = 0;
                    node = lSubtree;
                }
                else
                {
                    //LR
                    rSubtree = lSubtree->r;
                    lSubtree->r = rSubtree->l;
                    rSubtree->l = lSubtree;
                    node->l = rSubtree->r;
                    rSubtree->r = node;
                    node->balance = (rSubtree->balance == -1) ? 1 : 0;
                    lSubtree->balance = (rSubtree->balance == 1) ? -1 : 0;
                    node = rSubtree;
                }
                node->balance = 0;
                heightVaried = false;
            }
        }
    }
    else if (node->data < d)
    {
        insertion(node->r, d);
        if (heightVaried)
        {
            switch (node->balance)
            {
            case -1:
                node->balance = 0;
                heightVaried = false;
                break;
            case 0:
                node->balance = 1;
                break;
            case 1:
                rSubtree = node->r;
                if (rSubtree->balance == 1)
                {
                    //RR
                    node->r = rSubtree->l;
                    rSubtree->l = node;
                    node->balance = 0;
                    node = rSubtree;
                }
                else
                {
                    //RL
                    lSubtree = rSubtree->l;
                    rSubtree->l = lSubtree->r;
                    lSubtree->r = rSubtree;
                    node->r = lSubtree->l;
                    lSubtree->l = node;
                    node->balance = (lSubtree->balance == 1) ? -1 : 0;
                    rSubtree->balance = (lSubtree->balance == -1) ? 1 : 0;
                    node = lSubtree;
                }
                node->balance = 0;
                heightVaried = false;
            }
        }
    }
    else
    {
        node->occurrence++;
        heightVaried = false;
    }
}

void Avl::makeEmpty(nodeA *&node)
{
    if (node != NULL)
    {
        makeEmpty(node->l);
        makeEmpty(node->r);
        delete node;
    }
}

Avl::Avl(){
    root = NULL;
    heightVaried = false;
}

Avl::~Avl(){
    makeEmpty(root);
}

void Avl::insert(int data){
    insertion(root, data);
}

nodeA* Avl::getRoot(){
    return root;
}