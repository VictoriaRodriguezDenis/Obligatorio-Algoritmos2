#ifndef AVL_H
#define AVL_H

#include <string>
using namespace std;


struct NodoAVL {
    int id;
    string nombre;
    int puntaje;
    NodoAVL* izq;
    NodoAVL* der;
    int altura;

    NodoAVL(int unId, string unNombre, int unPuntaje);
};

struct RepresentacionAVL {
    NodoAVL* raizPorId;
    NodoAVL* raizPorPuntaje;
    NodoAVL* jugadorMejorRankeado;
    int cantJugadores;

    RepresentacionAVL();
};

typedef RepresentacionAVL* AVL;

AVL crearAVL();

void agregarJugador(AVL a, int id, string nombre, int puntaje);

void encontrarJugador(AVL a, int id);

void contarJugadoresPuntaje(AVL a, int puntaje);

void mostrarMejorJugador(AVL a);

void contarJugadores(AVL a);

#endif
