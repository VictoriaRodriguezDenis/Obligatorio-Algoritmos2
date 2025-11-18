#include <iostream>
using namespace std;

long long ***dpMemo;
int *colores;

// max propio
long long miMax(long long a, long long b)
{
    return (a > b ? a : b);
}

// DP top-down con memorización
long long calcMemo(int izq, int der, int extras, int N)
{
    if (izq > der)
        return 0;

    long long &memo = dpMemo[izq][der][extras];
    if (memo != -1)
        return memo;

    long long mejor =
        calcMemo(izq, der - 1, 0, N) + (long long)(extras + 1) * (extras + 1);

    for (int i = izq; i < der; i++)
    {
        if (colores[i] == colores[der])
        {
            long long unir =
                calcMemo(izq, i, extras + 1, N) +
                calcMemo(i + 1, der - 1, 0, N);

            mejor = miMax(mejor, unir);
        }
    }

    memo = mejor;
    return mejor;
}
