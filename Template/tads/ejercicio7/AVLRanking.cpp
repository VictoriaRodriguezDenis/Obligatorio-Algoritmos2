#include <iostream>
#include <string>
#include <map>
using namespace std;

const int MAX_ESTUDIANTES = 1000000; // Aumentado para soportar hasta 1 millón

// Fusiona dos mitades ordenadas y cuenta las inversiones
long long fusionarYContar(int ranking[], int temporal[], int inicio, int medio, int fin) {
    int indiceIzq = inicio;
    int indiceDer = medio + 1;
    int indiceTemporal = inicio;
    long long inversiones = 0;

    // Mientras haya elementos en ambas mitades
    while (indiceIzq <= medio && indiceDer <= fin) {
        if (ranking[indiceIzq] <= ranking[indiceDer]) {
            // El elemento de la izquierda es menor, lo copiamos
            temporal[indiceTemporal++] = ranking[indiceIzq++];
        } else {
            // El elemento de la derecha es menor ¡Hay inversiones!
            // Todos los elementos que quedan en la mitad izquierda
            // están invertidos con este elemento
            temporal[indiceTemporal++] = ranking[indiceDer++];
            inversiones += (medio - indiceIzq + 1);
        }
    }

    // Copiar elementos restantes de la mitad izquierda
    while (indiceIzq <= medio) {
        temporal[indiceTemporal++] = ranking[indiceIzq++];
    }

    // Copiar elementos restantes de la mitad derecha
    while (indiceDer <= fin) {
        temporal[indiceTemporal++] = ranking[indiceDer++];
    }

    // Copiar el resultado ordenado de vuelta al array original
    for (int i = inicio; i <= fin; i++) {
        ranking[i] = temporal[i];
    }

    return inversiones;
}

// Divide el array y cuenta inversiones (como merge sort pero contando)
long long dividirYContar(int ranking[], int temporal[], int inicio, int fin) {
    long long inversiones = 0;
    
    if (inicio < fin) {
        int medio = inicio + (fin - inicio) / 2;

        // Contar inversiones en la mitad izquierda
        inversiones += dividirYContar(ranking, temporal, inicio, medio);

        // Contar inversiones en la mitad derecha
        inversiones += dividirYContar(ranking, temporal, medio + 1, fin);

        // Contar inversiones entre las dos mitades al fusionarlas
        inversiones += fusionarYContar(ranking, temporal, inicio, medio, fin);
    }

    return inversiones;
}

// Función principal que inicia el conteo
long long contarInversiones(int ranking[], int cantidadEstudiantes) {
    static int temporal[MAX_ESTUDIANTES];
    return dividirYContar(ranking, temporal, 0, cantidadEstudiantes - 1);
}