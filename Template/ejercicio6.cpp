#include <iostream>
#include "tads/ejercicio6/skatePropulsion.cpp"
using namespace std;

int main()
{
    int cantPozos, cantMejoras, destino;
    cin >> cantPozos >> cantMejoras >> destino;

    // Reservamos memoria exacta según las cantidades
    Pozo *pozos = new Pozo[cantPozos];
    for (int i = 0; i < cantPozos; i++)
        cin >> pozos[i].inicio >> pozos[i].fin;

    Mejora *mejoras = new Mejora[cantMejoras];
    for (int i = 0; i < cantMejoras; i++)
        cin >> mejoras[i].posicion >> mejoras[i].aumento;

    int resultado = resolverSkate(pozos, cantPozos, mejoras, cantMejoras, destino);

    if (resultado == -1)
        cout << "Imposible\n";
    else
        cout << resultado << "\n";

    delete[] pozos;
    delete[] mejoras;

    return 0;
}
