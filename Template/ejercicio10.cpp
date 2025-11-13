#include <iostream>
#include "tads/ejercicio10/backtrackingAmazon.cpp"
using namespace std;

int main()
{
    char caracter;
    cin >> caracter;

    int cantidad;
    cin >> cantidad;

    int mejorCentro = -1;
    int pasosMin = -1;

    for (int idx = 1; idx <= cantidad; idx++)
    {
        int filas, columnas;
        cin >> filas >> columnas;

        char mapa[MAXF][MAXC];
        for (int f = 0; f < filas; f++)
            for (int c = 0; c < columnas; c++)
                cin >> mapa[f][c];

        int pasos = resolverCentro(caracter, mapa, filas, columnas);

        if (pasos != -1)
        {
            if (pasosMin == -1 || pasos < pasosMin)
            {
                pasosMin = pasos;
                mejorCentro = idx;
            }
        }
    }

    cout << mejorCentro << " " << pasosMin << endl;
    return 0;
}
