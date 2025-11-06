#include <iostream>
#include <string>
using namespace std;

const int MAXN = 100000;

// Función auxiliar para hacer merge y contar inversiones
long long mergeAndCount(int arr[], int temp[], int izq, int mid, int der)
{
    int i = izq;     // índice para subarray izquierdo
    int j = mid + 1; // índice para subarray derecho
    int k = izq;     // índice para array temporal
    long long inv_count = 0;

    // Mientras hay elementos en ambos subarrays
    while (i <= mid && j <= der)
    {
        if (arr[i] <= arr[j])
        {
            temp[k++] = arr[i++];
        }
        else
        {
            // arr[i] > arr[j], entonces hay inversiones
            // Todos los elementos desde i hasta mid son mayores que arr[j]
            temp[k++] = arr[j++];
            inv_count += (mid - i + 1);
        }
    }

    // Copiar elementos restantes del subarray izquierdo
    while (i <= mid)
        temp[k++] = arr[i++];

    // Copiar elementos restantes del subarray derecho
    while (j <= der)
        temp[k++] = arr[j++];

    // Copiar el array temporal de vuelta al original
    for (i = izq; i <= der; i++)
        arr[i] = temp[i];

    return inv_count;
}

// Función recursiva de Divide and Conquer
long long mergeSortAndCount(int arr[], int temp[], int izq, int der)
{
    long long inv_count = 0;

    if (izq < der)
    {
        int mid = izq + (der - izq) / 2;

        // Contar inversiones en la mitad izquierda
        inv_count += mergeSortAndCount(arr, temp, izq, mid);

        // Contar inversiones en la mitad derecha
        inv_count += mergeSortAndCount(arr, temp, mid + 1, der);

        // Contar inversiones al hacer merge
        inv_count += mergeAndCount(arr, temp, izq, mid, der);
    }

    return inv_count;
}

// Función principal para contar inversiones
long long contarInversiones(int arr[], int n)
{
    static int temp[MAXN];
    return mergeSortAndCount(arr, temp, 0, n - 1);
}

// Buscar el índice de un nombre en el ranking oficial
int buscarIndice(string rankingOficial[], int n, const string &nombre)
{
    for (int i = 0; i < n; i++)
        if (rankingOficial[i] == nombre)
            return i;
    return -1;
}