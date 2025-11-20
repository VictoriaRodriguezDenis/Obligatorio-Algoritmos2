#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/ejercicio9/mochila3D.cpp"

using namespace std;

int main()
{
    int cantElementos, capacidad, tamano, lineas, puntos;
    cin >> cantElementos;
    Elemento** elementos = new Elemento*[cantElementos];
    for (int i = 0; i < cantElementos; i++)
    {
        cin >> tamano >> lineas >> puntos;
        elementos[i] = new Elemento(tamano, lineas, puntos); 
    }
    cin >> capacidad;

    int S, L;
    cin >> S >> L;

    mochilaDP(elementos, cantElementos, S, L);
    
    return 0;    
}

