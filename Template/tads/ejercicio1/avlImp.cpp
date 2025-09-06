#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

struct NodoAVL {
    int id;
    string nombre;
    int puntaje;
    NodoAVL* izq;
    NodoAVL* der;
    int altura;
    NodoAVL(int unId, string unNombre, int unPuntaje) : id(unId), nombre(unNombre), puntaje(unPuntaje), izq(NULL), der(NULL), altura(1) {}
};

struct RepresentacionAVL{
    NodoAVL* raizPorId;
    NodoAVL* raizPorPuntaje;
    NodoAVL* jugadorMejorRankeado;
    int cantJugadores;

  RepresentacionAVL(): raizPorId(NULL), raizPorPuntaje(NULL), jugadorMejorRankeado(NULL), cantJugadores(0) {}
};
typedef RepresentacionAVL *AVL;

AVL crearAVL(){
    return new RepresentacionAVL();
}

int max(int a, int b) {
    return a > b ? a : b;
}

int altura(NodoAVL *n) {
    if (!n) return 0;
    return n->altura;
}

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

NodoAVL * agregarJugadorEnAVLID(NodoAVL *nodo, int id, string nombre, int puntaje, int& cant, NodoAVL* mejorRankeado) {
    if(!nodo) {
        cant++;
        if (!mejorRankeado || mejorRankeado->puntaje<puntaje || (mejorRankeado->puntaje==puntaje && mejorRankeado->id<id)){
            mejorRankeado = new NodoAVL(id, nombre, puntaje);
            return mejorRankeado;
        } else {
            return new NodoAVL(id, nombre, puntaje);
        }
    }
    if(id < nodo->id) 
        nodo->izq = agregarJugadorEnAVLID(nodo->izq, id, nombre, puntaje, cant, mejorRankeado);
    else if(id > nodo->id)
        nodo->der = agregarJugadorEnAVLID(nodo->der, id, nombre, puntaje, cant, mejorRankeado);
    else
        return nodo;
    
    nodo->altura = 1 + max(altura(nodo->izq), altura(nodo->der));
    int balanceo = balance(nodo);

    bool desbalanceoIzq = balanceo > 1;
    bool desbalanceoDer = balanceo < -1;

    if(desbalanceoIzq && id < nodo->izq->id) {
        return rotacionHoraria(nodo);
    }

    if(desbalanceoDer && id > nodo->der->id) {
        return rotacionAntiHoraria(nodo);
    }

    if(desbalanceoIzq && id > nodo->izq->id) {
        nodo->izq = rotacionAntiHoraria(nodo->izq);
        return rotacionHoraria(nodo);
    }

    if(desbalanceoDer && id < nodo->der->id) {
        nodo->der = rotacionHoraria(nodo->der);
        return rotacionAntiHoraria(nodo);
    }

    return nodo;
}

NodoAVL *agregarJugadorEnAVLPuntaje(NodoAVL *nodo, int id, string nombre, int puntaje){
    if(!nodo) {
        return new NodoAVL(id, nombre, puntaje);
    }
    if(puntaje < nodo->puntaje) 
        nodo->izq = agregarJugadorEnAVLPuntaje(nodo->izq, id, nombre, puntaje);
    else if(puntaje >= nodo->puntaje)
        nodo->der = agregarJugadorEnAVLPuntaje(nodo->der, id, nombre, puntaje);
    
    nodo->altura = 1 + max(altura(nodo->izq), altura(nodo->der));
    int balanceo = balance(nodo);

    bool desbalanceoIzq = balanceo > 1;
    bool desbalanceoDer = balanceo < -1;

    if(desbalanceoIzq && id < nodo->izq->id) {
        return rotacionHoraria(nodo);
    }

    if(desbalanceoDer && id > nodo->der->id) {
        return rotacionAntiHoraria(nodo);
    }

    if(desbalanceoIzq && id > nodo->izq->id) {
        nodo->izq = rotacionAntiHoraria(nodo->izq);
        return rotacionHoraria(nodo);
    }

    if(desbalanceoDer && id < nodo->der->id) {
        nodo->der = rotacionHoraria(nodo->der);
        return rotacionAntiHoraria(nodo);
    }

    return nodo;
}

void encontrarJugadorEnAVL(NodoAVL* a, int id){
    if (a){
        if (a->id > id) encontrarJugadorEnAVL(a->izq, id);
        else if (a->id < id) encontrarJugadorEnAVL(a->der, id);
        else cout << a->nombre << " " << a->puntaje << endl;
    } else {
        cout << "jugador_no_encontrado" << endl;
    }
}

void agregarJugador(AVL a, int id, string nombre, int puntaje) {
    a->raizPorId = agregarJugadorEnAVLID(a->raizPorId, id, nombre, puntaje, a->cantJugadores, a->jugadorMejorRankeado);
    a->raizPorPuntaje = agregarJugadorEnAVLPuntaje(a->raizPorPuntaje, id, nombre, puntaje);
}

void encontrarJugador(AVL a, int id){
    encontrarJugadorEnAVL(a->raizPorId, id);
}

void contarJugadoresPuntajesEnAVL(NodoAVL* a, int puntaje, int& cant){
    if (a){
        if (a->puntaje>=puntaje){
            cant++;
            contarJugadoresPuntajesEnAVL(a->izq, puntaje, cant);
            contarJugadoresPuntajesEnAVL(a->der, puntaje, cant);
        } else {
            contarJugadoresPuntajesEnAVL(a->der, puntaje, cant);
        }
    }
}

void contarJugadoresPuntaje(AVL a, int puntaje){
    int cant = 0;
    contarJugadoresPuntajesEnAVL(a->raizPorPuntaje, puntaje, cant);
    cout << cant << endl;
}

void mostrarMejorJugador(AVL a){
    if (!a) cout << "sin_jugadores" << endl;
    else cout << a->jugadorMejorRankeado->nombre << " " << a->jugadorMejorRankeado->puntaje << endl;
}

void contarJugadores (AVL a){
    cout << a->cantJugadores << endl;
}
