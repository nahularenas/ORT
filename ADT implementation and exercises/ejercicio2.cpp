#include "iostream"
using namespace std;

class NodeH
{
public:
    int occurrence;
    string word;
    NodeH *next;
    NodeH(string n) : occurrence(1), word(n), next(NULL) {}
};

class Hash
{
private:
    NodeH **hash;
    int bound;
    int length_;
    int cantDouble;

    bool isPrime(int n)
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

    int nextPrime(int num)
    {
        while (!isPrime(++num))
            ;
        return num;
    }

    unsigned int pow(int b, int e)
    {
        unsigned int r = 1;
        for (size_t i = 0; i < e; i++)
        {
            r = r * b;
        }
        return r;
    }

    void clearNodeList(NodeH *node)
    {
        if (node)
        {
            clearNodeList(node->next);
            delete node;
        }
    }

    unsigned int hashFunction(string e)
    {
        unsigned int x = 0;
        for (size_t i = 0; i < e.length(); i++)
        {
            x += e[i] * pow(7, i);
        }
        return x % bound;
    }

    void agregarAux(NodeH *&n, string s)
    {
        if (n == NULL)
        {
            n = new NodeH(s);
            length_++;
        }
        else if (n->word == s)
        {
            n->occurrence++;
            if (n->occurrence == 2)
                cantDouble++;
            else if (n->occurrence == 3)
                cantDouble--;
        }
        else
            agregarAux(n->next, s);
    }

public:
    Hash(int max)
    {
        this->bound = nextPrime(max);
        this->hash = new NodeH *[bound];
        this->length_ = 0;
        this->cantDouble = 0;
        for (int i = 0; i < bound; this->hash[i++] = NULL)
            ;
    }

    ~Hash()
    {
        for (int i = 0; i < bound; clearNodeList(this->hash[i++]))
            ;
        delete[] this->hash;
    }

    void insert(string s)
    {
        int k = hashFunction(s);
        agregarAux(hash[k], s);
    }

    int length()
    {
        return this->length_;
    }

    int getCantDouble(){
        return cantDouble;
    }
};

int main()
{
    int length;
    cin >> length;
    Hash *h = new Hash(length);
    string w;
    for (size_t i = 0; i < length; i++)
    {
        cin >> w;
        h->insert(w);
    }
    cout << h->getCantDouble();
    delete h;
    return 0;
}