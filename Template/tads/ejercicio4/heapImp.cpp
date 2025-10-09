#include <iostream>
using namespace std;

// Nodo del heap
class NodoHeap {
public:
    int dato;       
    int idxLista;   // índice de la lista de donde viene
    int idxElem;    // índice dentro de la lista
    NodoHeap(int dato, int idxLista, int idxElem) 
        : dato(dato), idxLista(idxLista), idxElem(idxElem) {}
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
        if (pos > 0 && heap[pos]->dato < heap[posPadre]->dato) {
            NodoHeap* aux = heap[pos];
            heap[pos] = heap[posPadre];
            heap[posPadre] = aux;
            flotar(posPadre);
        }
    }

    void hundir(int pos) {
        int posCandidato = getHijoIzq(pos);
        if (posCandidato < cant) {
            if (posCandidato + 1 < cant && heap[posCandidato + 1]->dato < heap[posCandidato]->dato) {
                posCandidato++;
            }
            if (heap[pos]->dato > heap[posCandidato]->dato) {
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
        this->heap = new NodoHeap*[tope];
        for (int i = 0; i < tope; i++) heap[i] = nullptr;
    }

    ~repHeap() {
        for (int i = 0; i < cant; i++) delete heap[i];
        delete[] heap;
    }

    bool esVacia() { return cant == 0; }

    void encolar(int dato, int idxLista, int idxElem) {
        heap[cant] = new NodoHeap(dato, idxLista, idxElem);
        flotar(cant++);
    }

    NodoHeap* minNodo() { return heap[0]; }

    void desencolar() {
        delete heap[0];
        heap[0] = heap[--cant];
        heap[cant] = nullptr;
        if (cant > 0) hundir(0);
    }
};


int* fusionarKListas(int** listas, int* tamanos, int K, int& totalElementos) {
    totalElementos = 0;
    for (int i = 0; i < K; i++) totalElementos += tamanos[i];

    int* resultado = new int[totalElementos];
    int posResultado = 0;

    repHeap heap(totalElementos);

    // Insertar el primer elemento de cada lista
    for (int i = 0; i < K; i++) {
        if (tamanos[i] > 0) {
            heap.encolar(listas[i][0], i, 0);
        }
    }

    while (!heap.esVacia()) {
        NodoHeap* nodo = heap.minNodo();
        resultado[posResultado++] = nodo->dato;
        int lista = nodo->idxLista;
        int elem = nodo->idxElem;

        heap.desencolar();

        // Insertar siguiente elemento de la misma lista
        if (elem + 1 < tamanos[lista]) {
            heap.encolar(listas[lista][elem + 1], lista, elem + 1);
        }
    }

    return resultado;
}