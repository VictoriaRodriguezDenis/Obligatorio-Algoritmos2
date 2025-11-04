#include <iostream>
#include <string>
using namespace std;

const int MAXN = 100000;

struct Nodo
{
    int valor;
    int altura;
    int tam; // tamaño del subárbol
    Nodo *izq;
    Nodo *der;
};

int altura(Nodo *n)
{
    if (n == NULL)
    {
        return 0;
    }
    return n->altura;
}

int tamano(Nodo *n)
{
    if (n == NULL)
    {
        return 0;
    }
    return n->tam;
}

int maximo(int a, int b)
{
    return (a > b) ? a : b;
}

Nodo *nuevoNodo(int valor)
{
    Nodo *n = new Nodo();
    n->valor = valor;
    n->altura = 1;
    n->tam = 1;
    n->izq = NULL;
    n->der = NULL;
    return n;
}

void actualizar(Nodo *n)
{
    if (n != NULL)
    {
        n->altura = 1 + maximo(altura(n->izq), altura(n->der));
        n->tam = 1 + tamano(n->izq) + tamano(n->der);
    }
}

int balance(Nodo *n)
{
    if (n == NULL)
    {
        return 0;
    }
    return altura(n->izq) - altura(n->der);
}

Nodo *rotarDerecha(Nodo *y)
{
    Nodo *x = y->izq;
    Nodo *T2 = x->der;
    x->der = y;
    y->izq = T2;
    actualizar(y);
    actualizar(x);
    return x;
}

Nodo *rotarIzquierda(Nodo *x)
{
    Nodo *y = x->der;
    Nodo *T2 = y->izq;
    y->izq = x;
    x->der = T2;
    actualizar(x);
    actualizar(y);
    return y;
}

// Inserta un valor y devuelve cuántos elementos mayores había
Nodo *insertar(Nodo *raiz, int valor, int &mayores)
{
    if (raiz == NULL)
    {
        return nuevoNodo(valor);
    }

    if (valor < raiz->valor)
    {
        // si voy a la izquierda, todo el subárbol derecho + el nodo actual son mayores
        mayores += tamano(raiz->der) + 1;
        raiz->izq = insertar(raiz->izq, valor, mayores);
    }
    else
    {
        raiz->der = insertar(raiz->der, valor, mayores);
    }

    actualizar(raiz);

    int bf = balance(raiz);
    if (bf > 1 && valor < raiz->izq->valor)
    {
        return rotarDerecha(raiz);
    }
    if (bf < -1 && valor > raiz->der->valor)
    {
        return rotarIzquierda(raiz);
    }
    if (bf > 1 && valor > raiz->izq->valor)
    {
        raiz->izq = rotarIzquierda(raiz->izq);
        return rotarDerecha(raiz);
    }
    if (bf < -1 && valor < raiz->der->valor)
    {
        raiz->der = rotarDerecha(raiz->der);
        return rotarIzquierda(raiz);
    }

    return raiz;
}

int buscarIndice(string rankingOficial[], int n, string nombre)
{
    for (int i = 0; i < n; i++)
    {
        if (rankingOficial[i] == nombre)
        {
            return i;
        }
    }
    return -1;
}