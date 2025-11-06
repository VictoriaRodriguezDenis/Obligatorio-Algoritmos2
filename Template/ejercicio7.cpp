#include <iostream>
#include <string>
#include "tads/ejercicio7/RankingInversiones.cpp"
using namespace std;

const int MAXN = 100000;

// Mapea el nombre del ayudante al índice en el ranking oficial
int buscarIndice(string rankingOficial[], int n, const string &nombre)
{
    for (int i = 0; i < n; i++)
        if (rankingOficial[i] == nombre)
            return i;
    return -1;
}

int main()
{
    int n;
    cin >> n;

    string rankingOficial[MAXN];
    string rankingAyudante[MAXN];
    int arr[MAXN];

    for (int i = 0; i < n; i++)
        cin >> rankingOficial[i];

    for (int i = 0; i < n; i++)
        cin >> rankingAyudante[i];

    // Convertir el ranking del ayudante a índices numéricos según el ranking oficial
    for (int i = 0; i < n; i++)
        arr[i] = buscarIndice(rankingOficial, n, rankingAyudante[i]);

    // Calcular el número de inversiones (pares invertidos)
    cout << contarInversiones(arr, n) << endl;
    return 0;
}
