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

    nodoAVL(int unId, int unPuntaje, string unNombre) : id(unId), puntaje(unPuntaje), nombre(unNombre), izq(NULL), der(NULL) {}
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


