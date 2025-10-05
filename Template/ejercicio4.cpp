#include <string>
#include <iostream>
#include "tads\ejercicio4\heapImp.cpp"
using namespace std;

int main() {
    int K;
    cin >> K;

    int** listas = new int*[K];
    int* tamanos = new int[K];

    for (int i = 0; i < K; i++) {
        cin >> tamanos[i];
        listas[i] = new int[tamanos[i]];
        for (int j = 0; j < tamanos[i]; j++) {
            cin >> listas[i][j];
        }
    }

    int total;
    int* resultado = fusionarKListas(listas, tamanos, K, total);

    for (int i = 0; i < total; i++) {
        cout << resultado[i] << "\n";
    }

    // Liberar memoria
    delete[] resultado;
    for (int i = 0; i < K; i++) delete[] listas[i];
    delete[] listas;
    delete[] tamanos;

    return 0;
}