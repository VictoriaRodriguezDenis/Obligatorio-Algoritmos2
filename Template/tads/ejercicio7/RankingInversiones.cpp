#include <iostream>
#include <string>
using namespace std;

const int MAXN = 100000;

long long mezclarYContar(int arr[], int temp[], int izq, int medio, int der)
{
    int i = izq, j = medio + 1, k = izq;
    long long inv = 0;

    while (i <= medio && j <= der)
    {
        if (arr[i] <= arr[j])
        {
            temp[k++] = arr[i++];
        }
        else
        {
            // Todos los elementos restantes en la mitad izquierda son mayores
            inv += (medio - i + 1);
            temp[k++] = arr[j++];
        }
    }

    while (i <= medio)
        temp[k++] = arr[i++];
    while (j <= der)
        temp[k++] = arr[j++];

    for (i = izq; i <= der; i++)
        arr[i] = temp[i];

    return inv;
}

long long contarInversionesRec(int arr[], int temp[], int izq, int der)
{
    long long inv = 0;
    if (izq < der)
    {
        int medio = (izq + der) / 2;
        inv += contarInversionesRec(arr, temp, izq, medio);
        inv += contarInversionesRec(arr, temp, medio + 1, der);
        inv += mezclarYContar(arr, temp, izq, medio, der);
    }
    return inv;
}

long long contarInversiones(int arr[], int n)
{
    static int temp[MAXN];
    return contarInversionesRec(arr, temp, 0, n - 1);
}
