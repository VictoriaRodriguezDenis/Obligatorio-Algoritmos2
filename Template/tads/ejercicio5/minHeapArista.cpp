#include <iostream>
using namespace std;

struct Arista {
    int desde, hasta, peso;
    Arista() {}
    Arista(int d, int h, int p) : desde(d), hasta(h), peso(p) {}
};

class NodoHeap {
public:
    Arista arista;
    NodoHeap(Arista a) : arista(a) {}
};

class repHeap {
private:
    NodoHeap** heap;
    int cant;
    int tope;

    int getPadre(int pos) { return (pos - 1) / 2; }
    int getHijoIzq(int pos) { return 2 * pos + 1; }
    int getHijoDer(int pos) { return 2 * pos + 2; }

    void flotar(int pos) {
        int posPadre = getPadre(pos);
        if (pos > 0 && heap[pos]->arista.peso < heap[posPadre]->arista.peso) {
            NodoHeap* aux = heap[pos];
            heap[pos] = heap[posPadre];
            heap[posPadre] = aux;
            flotar(posPadre);
        }
    }

    void hundir(int pos) {
        int posCandidato = getHijoIzq(pos);
        if (posCandidato < cant) {
            if (posCandidato + 1 < cant && heap[posCandidato + 1]->arista.peso < heap[posCandidato]->arista.peso) {
                posCandidato++;
            }
            if (heap[pos]->arista.peso > heap[posCandidato]->arista.peso) {
                NodoHeap* aux = heap[pos];
                heap[pos] = heap[posCandidato];
                heap[posCandidato] = aux;
                hundir(posCandidato);
            }
        }
    }

public:
    repHeap(int tope) {
        this->tope = tope;
        this->cant = 0;
        heap = new NodoHeap*[tope];
        for (int i = 0; i < tope; i++) heap[i] = NULL;
    }

    ~repHeap() {
        for (int i = 0; i < cant; i++) delete heap[i];
        delete[] heap;
    }

    bool esVacia() { return cant == 0; }

    void encolar(Arista arista) {
        heap[cant] = new NodoHeap(arista);
        flotar(cant++);
    }

    Arista minArista() { return heap[0]->arista; }

    void desencolar() {
        delete heap[0];
        heap[0] = heap[--cant];
        heap[cant] = NULL;
        if (cant > 0) hundir(0);
    }
};
