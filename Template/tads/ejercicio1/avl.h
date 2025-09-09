#ifndef AVL_H
#define AVL_H
#include "avlImp.cpp"
#include <string>
using namespace std;

struct NodoAVL;

struct RepresentacionAVL;

typedef RepresentacionAVL* AVL;

AVL crearAVL();

void agregarJugador(AVL a, int id, string nombre, int puntaje);

void encontrarJugador(AVL a, int id);

void contarJugadoresPuntaje(AVL a, int puntaje);

void mostrarMejorJugador(AVL a);

void contarJugadores(AVL a);

#endif