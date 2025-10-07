#include <string>
#include <iostream>
using namespace std;

struct Arista {
    int desde, hasta, peso;
};

class RepConjuntosDisjuntos {
private:
    int* padre;
    int* nivel;

public:
    RepConjuntosDisjuntos(int n) {
        padre = new int[n];
        nivel = new int[n];
        for (int i = 0; i < n; i++) {
            padre[i] = i;
            nivel[i] = 0;
        }
    }

    int encontrar(int x) {
        if (padre[x] == x) return x;
        padre[x] = encontrar(padre[x]);
        return padre[x];
    }

    void unir(int a, int b) {
        int raizA = encontrar(a);
        int raizB = encontrar(b);
        if (raizA == raizB) return;

        // unión por nivel (rank)
        if (nivel[raizA] < nivel[raizB]) {
            padre[raizA] = raizB;
        } else if (nivel[raizA] > nivel[raizB]) {
            padre[raizB] = raizA;
        } else {
            padre[raizB] = raizA;
            nivel[raizA]++;
        }
    }
};

// Ordena las aristas por peso usando selección
void ordenarAristas(Arista* aristas, int n) {
    for (int i = 0; i < n - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < n; j++) {
            if (aristas[j].peso < aristas[menor].peso)
                menor = j;
        }
        if (menor != i) {
            Arista aux = aristas[i];
            aristas[i] = aristas[menor];
            aristas[menor] = aux;
        }
    }
}