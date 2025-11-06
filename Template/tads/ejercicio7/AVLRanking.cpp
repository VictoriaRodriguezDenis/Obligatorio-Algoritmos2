#include <iostream>
#include <string>
using namespace std;

const int MAXN = 100000;

class NodoAVL
{
public:
    int id; // valor (índice en el ranking oficial)
    NodoAVL *izq;
    NodoAVL *der;
    int altura;
    int cantNodos; // tamaño del subárbol

    NodoAVL(int unId)
        : id(unId), izq(NULL), der(NULL), altura(1), cantNodos(1) {}
};

class repAVL
{
private:
    NodoAVL *raiz;
    long long inversionesTotales;

    int max(int a, int b)
    {
        return a > b ? a : b;
    }

    int altura(NodoAVL *n)
    {
        return n ? n->altura : 0;
    }

    int cantNodos(NodoAVL *n)
    {
        return n ? n->cantNodos : 0;
    }

    int balance(NodoAVL *n)
    {
        return n ? altura(n->izq) - altura(n->der) : 0;
    }

    NodoAVL *rotacionHoraria(NodoAVL *A)
    {
        NodoAVL *B = A->izq;
        NodoAVL *T2 = B->der;
        B->der = A;
        A->izq = T2;
        actualizar(A);
        actualizar(B);
        return B;
    }

    NodoAVL *rotacionAntiHoraria(NodoAVL *B)
    {
        NodoAVL *A = B->der;
        NodoAVL *T2 = A->izq;
        A->izq = B;
        B->der = T2;
        actualizar(B);
        actualizar(A);
        return A;
    }

    void actualizar(NodoAVL *n)
    {
        if (n)
        {
            n->altura = 1 + max(altura(n->izq), altura(n->der));
            n->cantNodos = 1 + cantNodos(n->izq) + cantNodos(n->der);
        }
    }

    NodoAVL *insertarEnAVL(NodoAVL *nodo, int id)
    {
        if (!nodo)
            return new NodoAVL(id);

        if (id < nodo->id)
        {
            nodo->izq = insertarEnAVL(nodo->izq, id);
        }
        else
        {
            // Cada vez que inserto un valor mayor, cuento los de la izquierda + el nodo
            inversionesTotales += cantNodos(nodo->izq) + 1;
            nodo->der = insertarEnAVL(nodo->der, id);
        }

        actualizar(nodo);

        int balanceo = balance(nodo);
        bool desbIzq = balanceo > 1;
        bool desbDer = balanceo < -1;

        if (desbIzq && id < nodo->izq->id)
            return rotacionHoraria(nodo);
        if (desbDer && id > nodo->der->id)
            return rotacionAntiHoraria(nodo);
        if (desbIzq && id > nodo->izq->id)
        {
            nodo->izq = rotacionAntiHoraria(nodo->izq);
            return rotacionHoraria(nodo);
        }
        if (desbDer && id < nodo->der->id)
        {
            nodo->der = rotacionHoraria(nodo->der);
            return rotacionAntiHoraria(nodo);
        }

        return nodo;
    }

    void borrarNodo(NodoAVL *n)
    {
        if (!n)
            return;
        borrarNodo(n->izq);
        borrarNodo(n->der);
        delete n;
    }

public:
    repAVL()
    {
        raiz = NULL;
        inversionesTotales = 0;
    }

    ~repAVL()
    {
        borrarNodo(raiz);
    }

    void insertar(int id)
    {
        raiz = insertarEnAVL(raiz, id);
    }

    long long obtenerInversiones()
    {
        return inversionesTotales;
    }
};

int buscarIndice(string rankingOficial[], int n, const string &nombre)
{
    for (int i = 0; i < n; i++)
        if (rankingOficial[i] == nombre)
            return i;
    return -1;
}