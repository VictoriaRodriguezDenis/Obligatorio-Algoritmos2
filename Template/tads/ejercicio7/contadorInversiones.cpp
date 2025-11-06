#include <iostream>
using namespace std;

const int MAXN = 1000000;

long long fusionarYContar(int v[], int aux[], int izq, int medio, int der)
{
    int i = izq, j = medio + 1, k = izq;
    long long inv = 0;

    while (i <= medio && j <= der)
    {
        if (v[i] <= v[j])
            aux[k++] = v[i++];
        else
        {
            aux[k++] = v[j++];
            inv += (medio - i + 1);
        }
    }
    while (i <= medio)
        aux[k++] = v[i++];
    while (j <= der)
        aux[k++] = v[j++];
    for (int t = izq; t <= der; t++)
        v[t] = aux[t];
    return inv;
}

long long mergeSortContar(int v[], int aux[], int izq, int der)
{
    if (izq >= der)
        return 0;
    int medio = (izq + der) / 2;
    long long inv = 0;
    inv += mergeSortContar(v, aux, izq, medio);
    inv += mergeSortContar(v, aux, medio + 1, der);
    inv += fusionarYContar(v, aux, izq, medio, der);
    return inv;
}

long long contarInversiones(int v[], int n)
{
    int *aux = new int[n];
    long long res = mergeSortContar(v, aux, 0, n - 1);
    delete[] aux;
    return res;
}
