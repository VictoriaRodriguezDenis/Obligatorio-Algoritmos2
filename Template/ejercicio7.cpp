#include <string>
#include <iostream>
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
    {
        cin >> rankingOficial[i];
    }

    for (int i = 0; i < n; i++)
    {
        cin >> rankingAyudante[i];
    }

    for (int i = 0; i < n; i++)
    {
        ordenNumerico[i] = buscarIndice(rankingOficial, n, rankingAyudante[i]);
    }

    Nodo *raiz = NULL;
    int totalInversiones = 0;

    for (int i = 0; i < n; i++)
    {
        int mayores = 0;
        raiz = insertar(raiz, ordenNumerico[i], mayores);
        totalInversiones += mayores;
    }

    cout << totalInversiones << endl;
    return 0;
}
