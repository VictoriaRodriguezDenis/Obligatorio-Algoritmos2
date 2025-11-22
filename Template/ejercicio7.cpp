#include <iostream>
#include <string>
#include "tads/ejercicio7/HashCerrado.cpp"
#include "tads/ejercicio7/ContadorInversiones.cpp"
using namespace std;

int main()
{
    int N;
    cin >> N;

    string *rankingOficial = new string[N];
    string *rankingAyudante = new string[N];
    int *indicesNumericos = new int[N];

    HashCerrado *tablaDeIndices = new HashCerrado(N * 2);

    for (int i = 0; i < N; i++)
    {
        cin >> rankingOficial[i];
        tablaDeIndices->insertar(rankingOficial[i], i);
    }

    for (int i = 0; i < N; i++)
    {
        cin >> rankingAyudante[i];
        indicesNumericos[i] = tablaDeIndices->buscar(rankingAyudante[i]);
    }

    long long totalInversiones = contarInversiones(indicesNumericos, N);
    cout << totalInversiones << "\n";

    delete[] rankingOficial;
    delete[] rankingAyudante;
    delete[] indicesNumericos;
    delete tablaDeIndices;

    return 0;
}
