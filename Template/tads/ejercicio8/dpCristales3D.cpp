#include <iostream>
using namespace std;

long long miMax(long long a, long long b)
{
    return (a > b ? a : b);
}

long long calcMemo(
    int izq, int der, int extras, int N,
    int *colores,
    long long ***dpMemo)
{
    if (izq > der)
        return 0;

    long long &memo = dpMemo[izq][der][extras];
    if (memo != -1)
        return memo;

    // Opción 1: borrar colores[der] ahora
    long long mejor = calcMemo(izq, der - 1, 0, N, colores, dpMemo) + (long long)(extras + 1) * (extras + 1);

    // Opción 2: unir colores iguales (i con der)
    for (int i = izq; i < der; i++)
    {
        if (colores[i] == colores[der])
        {

            long long unir = calcMemo(izq, i, extras + 1, N, colores, dpMemo) + calcMemo(i + 1, der - 1, 0, N, colores, dpMemo);

            mejor = miMax(mejor, unir);
        }
    }

    memo = mejor;
    return mejor;
}
