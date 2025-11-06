#include <iostream>
#include <string>
#include "tads/ejercicio7/HashCerrado.cpp"
#include "tads/ejercicio7/ContadorInversiones.cpp"
using namespace std;

int main()
{
    int N;
    cin >> N;

    // Reservar memoria dinámica
    string *rankingOficial = new string[N];
    string *rankingAyudante = new string[N];
    int *arregloIndices = new int[N];

    // Crear hash cerrado con espacio extra para reducir colisiones
    HashCerrado tablaHash(N * 2);

    // Leer ranking oficial y guardarlo en el hash
    for (int i = 0; i < N; i++)
    {
        cin >> rankingOficial[i];
        tablaHash.insertar(rankingOficial[i], i);
    }

    // Leer ranking del ayudante y traducir nombres a índices
    for (int i = 0; i < N; i++)
    {
        cin >> rankingAyudante[i];
        arregloIndices[i] = tablaHash.buscar(rankingAyudante[i]);
    }

    // Contar el número total de inversiones entre rankings
    long long totalInversiones = contarInversiones(arregloIndices, N);
    cout << totalInversiones << "\n";

    // Liberar memoria dinámica
    delete[] rankingOficial;
    delete[] rankingAyudante;
    delete[] arregloIndices;

    return 0;
}
