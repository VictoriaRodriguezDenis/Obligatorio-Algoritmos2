#include <string>
#include <iostream>
#include "tads\ejercicio5\kruskalDS.cpp"
using namespace std;

int main() {
    int V, E;
    cin >> V >> E;
    repHeap* heap = new repHeap(E);
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        heap->encolar(Arista(u, v, w));
    }
    RepConjuntosDisjuntos* conjuntos = new RepConjuntosDisjuntos(V);
    int pesoTotal = 0;
    while (!heap->esVacia()) {
        Arista a = heap->minArista();
        heap->desencolar();
        if (conjuntos->encontrar(a.desde) != conjuntos->encontrar(a.hasta)) {
            conjuntos->unir(a.desde, a.hasta);
            pesoTotal += a.peso;
        }
    }
    cout << pesoTotal << "\n";
    return 0;
}