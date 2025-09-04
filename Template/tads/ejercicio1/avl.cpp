#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

struct nodoAVL {
    int id;
    int puntaje;
    string nombre;
    int altura;
    NodoAVL* izq;
    NodoAVL* der;
    int fVal;

    nodoAVL(int unId, int unPuntaje, string unNombre) : id(unId), puntaje(unPuntaje), nombre(unNombre), izq(NULL), der(NULL), fVal(0) {}
};

struct RepresentacionAVL{
  NodoAVL *raiz;
  int cantJugadores;

  RepresentacionAVL(): raiz(NULL), cantJugadores(0) {}
};
typedef RepresentacionAVL *AVL;

AVL crearAVL(){
    return new RepresentacionAVL();
}

void agregarJugadorEnAVL(AVL a, int id, string nombre, int puntaje) {
    bool varioAltura = false;
    bool insertado = agregarJugadorEnAVLRec(a->raiz, id, nombre, puntaje, varioAltura);
    if (insertado) {
        a->cantJugadores++;
    }
}

bool agregarJugadorEnAVLRec(NodoAVL *&a, int id, string nombre, int puntaje, bool &varioAltura)
{
    bool insertado;
    if (a == NULL)
    {
        a = new NodoAVL(id, puntaje, nombre);
        varioAltura = true;
        return true;
    }
    if (id < a->id)
    {
        insertado = agregarJugadorEnAVLRec(a->izq, id, nombre, puntaje, varioAltura);
        if (varioAltura)
        {
            switch (a->fVal)
            {
                case 1:
                    a->fVal = 0;
                    varioAltura = false;
                    break;
                case 0:
                    a->fVal = -1;
                    break;
                case -1:
                    NodoAVL *p1 = a->izq;
                    if(p1->fVal == -1){
                        a->izq = p1->der;
                        p1->der = a;
                        a->fVal = 0;
                        a = p1;
                    } else {
                        NodoAVL *p2 = p1->der;
                        p1->der = p2->izq;
                        p2->izq = p1;
                        a->izq = p2->der;
                        p2->der = a;
                        a->fVal = p2->fVal == -1 ? 1 : 0;
                        p1->fVal = p2->fVal == 1 ? -1 : 0;
                        a = p2;
                    }
                    a->fVal = 0;
                    varioAltura = false;
                    break;
            }
            varioAltura = false;
        }
        return insertado;
    }
    else if (id > a->id)
    {
        insertado = agregarJugadorEnAVLRec(a->der, id, nombre, puntaje, varioAltura);
        if (varioAltura)
        {
            switch (a->fVal)
            {
                case -1:
                    a->fVal = 0;
                    varioAltura = false;
                    break;
                case 0:
                    a->fVal = 1;
                    break;
                case 1:
                    NodoAVL *p1 = a->der;
                    if(p1->fVal == 1){
                        a->der = p1->izq;
                        p1->izq = a;
                        a->fVal = 0;
                        a = p1;
                    } else {
                        NodoAVL *p2 = p1->izq;
                        p1->izq = p2->der;
                        p2->der = p1;
                        a->der = p2->izq;
                        p2->izq = a;
                        a->fVal = p2->fVal == 1 ? -1 : 0;
                        p1->fVal = p2->fVal == -1 ? 1 : 0;
                        a = p2;
                        return insertado;
                    }
                    a->fVal = 0;
                    varioAltura = false;
                    break;
            }
            varioAltura = false;
        }
        return insertado;
    } else return false;
}

void encontrarJugador(AVL a, int id){
  encontrarJugadorEnAVL(a->raiz, id);
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

