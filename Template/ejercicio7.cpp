#include <string>
#include <iostream>
#include "tads\ejercicio7\AVLRanking.cpp"
using namespace std;
int main() {
    int n;
    if (!(cin >> n) || n <= 0 || n > MAXN) {
        return 1;
    }

    static string rankingOficial[MAXN];
    static string rankingAyudante[MAXN];
    static int ordenNumerico[MAXN];

    // Leer ranking oficial
    for (int i = 0; i < n; i++) {
        if (!(cin >> rankingOficial[i])) {
            return 1;
        }
    }

    // Leer ranking del ayudante
    for (int i = 0; i < n; i++) {
        if (!(cin >> rankingAyudante[i])) {
            return 1;
        }
    }

    // Convertir el ranking del ayudante a posiciones numéricas
    // según el ranking oficial
    for (int i = 0; i < n; i++) {
        ordenNumerico[i] = buscarIndice(rankingOficial, n, rankingAyudante[i]);
        if (ordenNumerico[i] == -1) {
            return 1; // Nombre no encontrado
        }
    }

    // Contar inversiones usando Divide and Conquer (Merge Sort modificado)
    int inversiones = contarInversiones(ordenNumerico, n);

    cout << inversiones << endl;

    return 0;
}