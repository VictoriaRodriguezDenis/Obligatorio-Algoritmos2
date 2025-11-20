#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/ejercicio9/mochila3D.cpp"

using namespace std;

int main()
{
    int cantElementos;
    cin >> cantElementos;

    Elemento** elementos = new Elemento*[cantElementos];

    for (int i = 0; i < cantElementos; i++)
    {
        int tamano, lineas, puntos;
        cin >> tamano >> lineas >> puntos;
        elementos[i] = new Elemento(tamano, lineas, puntos);
    }

    int S, L;
    cin >> S >> L;

    mochilaDP(elementos, cantElementos, S, L);

    // liberar memoria
    for (int i = 0; i < cantElementos; i++) {
        delete elementos[i];
    }
    delete[] elementos;

    return 0;
}
