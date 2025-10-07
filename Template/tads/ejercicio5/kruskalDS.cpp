#include <iostream>
#include "minHeapArista.cpp"
using namespace std;

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