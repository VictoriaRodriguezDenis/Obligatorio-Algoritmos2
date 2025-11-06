#include <iostream>
#include <string>
#include "tads\ejercicio7\AVLRanking.cpp"
using namespace std;

int main()
{
    int n;
    cin >> n;

    string rankingOficial[MAXN];
    string rankingAyudante[MAXN];
    int ordenNumerico[MAXN];

    for (int i = 0; i < n; i++)
        cin >> rankingOficial[i];
    for (int i = 0; i < n; i++)
        cin >> rankingAyudante[i];

    for (int i = 0; i < n; i++)
        ordenNumerico[i] = buscarIndice(rankingOficial, n, rankingAyudante[i]);

    repAVL arbol;
    for (int i = n - 1; i >= 0; i--)
        arbol.insertar(ordenNumerico[i]);

    cout << arbol.obtenerInversiones() << endl;
    return 0;
}
