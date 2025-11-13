#include <iostream>
#include "tads/ejercicio10/backtrackingAmazon.cpp"
using namespace std;

int main()
{
    char productoBuscado;
    cin >> productoBuscado;

    int cantidadCentros;
    cin >> cantidadCentros;

    int mejorCentro = -1;
    int mejorPasos = -1;

    for (int indice = 1; indice <= cantidadCentros; indice++)
    {
        int cantFilas, cantCols;
        cin >> cantFilas >> cantCols;

        // Crear mapa dinámico de chars
        char **mapa = new char *[cantFilas];
        for (int f = 0; f < cantFilas; f++)
        {
            mapa[f] = new char[cantCols];
        }

        // Leer el mapa
        for (int f = 0; f < cantFilas; f++)
            for (int c = 0; c < cantCols; c++)
                cin >> mapa[f][c];

        // Resolver este FC
        int pasos = buscarProducto(productoBuscado, mapa, cantFilas, cantCols);

        // Guardar el mejor
        if (pasos != -1)
        {
            if (mejorPasos == -1 || pasos < mejorPasos)
            {
                mejorPasos = pasos;
                mejorCentro = indice;
            }
        }

        // Liberar memoria del mapa
        for (int f = 0; f < cantFilas; f++)
            delete[] mapa[f];
        delete[] mapa;
    }

    cout << mejorCentro << " " << mejorPasos << endl;
    return 0;
}
