#include <string>
#include <iostream>
#include "tads\ejercicio5\kruskalDS.cpp"
using namespace std;

int main() {
    int V, E;
    cin >> V >> E;
    Arista* aristas = new Arista[E];
    for (int i = 0; i < E; i++) {
        cin >> aristas[i].desde >> aristas[i].hasta >> aristas[i].peso;
    }
    ordenarAristas(aristas, E);
    RepConjuntosDisjuntos conjuntos = RepConjuntosDisjuntos(V);
    int pesoTotal = 0;

    for (int i = 0; i < E; i++) {
        int u = aristas[i].desde;
        int v = aristas[i].hasta;
        int w = aristas[i].peso;

        int raizU = conjuntos.encontrar(u);
        int raizV = conjuntos.encontrar(v);

        if (raizU != raizV) {
            conjuntos.unir(raizU, raizV);
            pesoTotal += w;
        }
    }

    cout << pesoTotal << "\n";

    delete[] aristas;
    return 0;
}
