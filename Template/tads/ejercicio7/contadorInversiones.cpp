#include <iostream>
using namespace std;

// Algoritmo de Divide and Conquer para contar inversiones en O(N log N)

// Mezcla dos mitades ordenadas y cuenta las inversiones cruzadas
long long combinarYContar(int arreglo[], int auxiliar[], int inicio, int medio, int fin)
{
    int indiceIzq = inicio;
    int indiceDer = medio + 1;
    int indiceAux = inicio;
    long long inversiones = 0;

    while (indiceIzq <= medio && indiceDer <= fin)
    {
        if (arreglo[indiceIzq] <= arreglo[indiceDer])
        {
            auxiliar[indiceAux++] = arreglo[indiceIzq++];
        }
        else
        {
            auxiliar[indiceAux++] = arreglo[indiceDer++];
            // todos los elementos restantes en la mitad izquierda son mayores
            inversiones += (medio - indiceIzq + 1);
        }
    }

    while (indiceIzq <= medio)
        auxiliar[indiceAux++] = arreglo[indiceIzq++];

    while (indiceDer <= fin)
        auxiliar[indiceAux++] = arreglo[indiceDer++];

    for (int i = inicio; i <= fin; i++)
        arreglo[i] = auxiliar[i];

    return inversiones;
}

// Aplica Merge Sort recursivo y acumula las inversiones
long long mergeSortYContar(int arreglo[], int auxiliar[], int inicio, int fin)
{
    if (inicio >= fin)
        return 0;

    int medio = (inicio + fin) / 2;
    long long inversiones = 0;

    inversiones += mergeSortYContar(arreglo, auxiliar, inicio, medio);
    inversiones += mergeSortYContar(arreglo, auxiliar, medio + 1, fin);
    inversiones += combinarYContar(arreglo, auxiliar, inicio, medio, fin);

    return inversiones;
}

// Función principal: recibe un arreglo y devuelve el número de inversiones
long long contarInversiones(int arreglo[], int cantidad)
{
    int *auxiliar = new int[cantidad];
    long long totalInversiones = mergeSortYContar(arreglo, auxiliar, 0, cantidad - 1);
    delete[] auxiliar;
    return totalInversiones;
}
