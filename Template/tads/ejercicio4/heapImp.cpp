#include <string>
#include <iostream>
using namespace std;

class NodoHeap {
public:
    int dato;
    NodoHeap(int dato) : dato(dato) {}
};

class repHeap {
private:
        NodoHeap** heap;
        int cant;
        int tope;

        int getPadre(int pos) { 
                return (pos - 1) / 2; 
        }
        int getHijoIzq(int pos) { 
                return 2 * pos + 1; 
        }
        int getHijoDer(int pos) { 
                return 2 * pos + 2; 
        }

        void flotar(NodoHeap** h, int pos) {
                int posPadre = getPadre(pos);
                if (pos > 0 && h[pos]->dato < h[posPadre]->dato) {
                        NodoHeap* aux = h[pos];
                        h[pos] = h[posPadre];
                        h[posPadre] = aux;
                        flotar(h, posPadre);
                }
        }

        void hundir(NodoHeap** h, int pos, int cant) {
                int posCandidato = getHijoIzq(pos);
                if (posCandidato < cant) {
                        if (posCandidato + 1 < cant && h[posCandidato + 1]->dato <= h[posCandidato]->dato) {
                                posCandidato++;
                        }
                        if (h[pos]->dato >= h[posCandidato]->dato) {
                                NodoHeap* aux = h[pos];
                                h[pos] = h[posCandidato];
                                h[posCandidato] = aux;
                                hundir(h, posCandidato, cant);
                        }
                }
        }

public:
        repHeap(int tope) {
                this->tope = tope;
                this->cant = 0;
                this->heap = new NodoHeap*[tope];
                for (int i = 0; i < tope; i++)
                this->heap[i] = NULL;
        }

        bool esVacia() { 
                return cant == 0; 
        }

        int min() { 
                return heap[0]->dato; 
        }

        void encolar(int dato) {
                heap[cant] = new NodoHeap(dato);
                flotar(heap, cant++);
        }

        void desencolar() {
                delete heap[0];
                heap[0] = heap[--cant];
                heap[cant] = NULL;
                hundir(heap, 0, cant);
        }
};

typedef repHeap* Heap;
