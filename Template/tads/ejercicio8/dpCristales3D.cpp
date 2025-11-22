#include <iostream>
using namespace std;

int calcMemo(
    int izq, int der, int extras,
    int *colores,
    int ***dpMemo)
{
    if (izq > der)
        return 0;

    int &memo = dpMemo[izq][der][extras];
    if (memo != -1)
        return memo;

    // Opción 1: borrar colores[der] ahora
    int mejor = calcMemo(izq, der - 1, 0, colores, dpMemo) + (extras + 1) * (extras + 1);

    // Opción 2: unir colores iguales (i con der)
    for (int i = izq; i < der; i++)
    {
        if (colores[i] == colores[der])
        {

            int unir = calcMemo(izq, i, extras + 1, colores, dpMemo) + calcMemo(i + 1, der - 1, 0, colores, dpMemo);

            mejor = max(mejor, unir);
        }
    }

    memo = mejor;
    return mejor;
}
