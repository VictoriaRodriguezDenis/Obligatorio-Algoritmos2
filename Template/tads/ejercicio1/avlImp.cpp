#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

class AVL {
	private:
	struct NodoAVL {
        int id;
        string nombre;
        int puntaje;
        NodoAVL* izq;
        NodoAVL* der;
        int altura;
		nodoAVL(int unId, string unNombre, int unPuntaje) : id(unId), nombre(unNombre), puntaje(unPuntaje), izq(NULL), der(NULL), altura(1) {}
	};

	NodoAVL *raiz;

    struct RepresentacionAVL{
        NodoAVL *raiz;
        int cantJugadores;

        RepresentacionAVL(): raiz(NULL), cantJugadores(0) {}
    };
    typedef RepresentacionAVL *AVL;

	int max(int a, int b) {
		return a > b ? a : b;
	}

	// Funcion para acceder a la altura del nodo, si el nodo es nulo, la altura es 0
	int altura(NodoAVL *n) {
		if (!n) return 0;
		return n->altura;
	}

	// Funcion para calcular el balance del nodo
	int balance(NodoAVL *n) {
		if (!n) return 0;
		return altura(n->izq) - altura(n->der);
	}

	NodoAVL* rotacionHoraria(NodoAVL *A) {
		NodoAVL *B = A->izq;
		NodoAVL *T2 = B->der;
		B->der = A;
		A->izq = T2;
		A->altura = 1 + max(altura(A->izq), altura(A->der));
		B->altura = 1 + max(altura(B->izq), altura(B->der));
		return B;
	}

	NodoAVL* rotacionAntiHoraria(NodoAVL* B) {
		NodoAVL *A = B->der;
		NodoAVL *T2 = A->izq;
		A->izq = B;
		B->der = T2;
		B->altura = 1 + max(altura(B->izq), altura(B->der));
		A->altura = 1 + max(altura(A->izq), altura(A->der));
		return A;
	}

    NodoAVL * agregarJugadorEnAVL(NodoAVL *nodo, int dato, string nombre, int puntaje, int& cant) {
        if(!nodo) {
            return new NodoAVL(id, nombre, puntaje); 
            cant++;
        }
        if(id < nodo->id) 
            nodo->izq = agregarJugadorEnAVL(nodo->izq, id, dato, nombre, puntaje, cant);
        else if(id > nodo->id)
            nodo->der = agregarJugadorEnAVL(nodo->izq, id, dato, nombre, puntaje, cant);
        else
            return nodo;
        
        // A la vuelta de la recursión, actualizo la altura del nodo en el que estoy
        nodo->altura = 1 + max(altura(nodo->izq), altura(nodo->der));

        // Verifico si el nodo está desbalanceado
        int balanceo = balance(nodo);

        bool desbalanceoIzq = balanceo > 1;
        bool desbalanceoDer = balanceo < -1;

        // Caso izquierda izquierda
        if(desbalanceoIzq && id < nodo->izq->id) {
            return rotacionHoraria(nodo);
        }

        // Caso derecha derecha
        if(desbalanceoDer && id > nodo->der->id) {
            return rotacionAntiHoraria(nodo);
        }

        // Caso izquierda derecha
        if(desbalanceoIzq && id > nodo->izq->id) {
            nodo->izq = rotacionAntiHoraria(nodo->izq);
            return rotacionHoraria(nodo);
        }

        // Caso derecha izquierda
        if(desbalanceoDer && id < nodo->der->id) {
            nodo->der = rotacionHoraria(nodo->der);
            return rotacionAntiHoraria(nodo);
        }

        return nodo;
    }

    void encontrarJugadorEnAVL(NodoAVL* a, int id){
        if (a){
            if (a->id > id) encontrarJugadorEnAVL(a->izq, id);
            if (a->id < id) encontrarJugadorEnAVL(a->der, id);
            else cout << a->nombre << a->puntaje << endl;
        } else {
            cout << "jugador_no_encontrado" << endl;
        }
    }

	public:
    void agregarJugador(int id, string nombre, int puntaje) {
        raiz = agregarJugadorEnAVL(raiz, id, nombre, puntaje, raiz->cantJugadores);
    }

    void encontrarJugador(int id){
        encontrarJugadorEnAVL(raiz, id);
    }
};