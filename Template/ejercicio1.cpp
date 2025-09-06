#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads\ejercicio1\avl.h"

using namespace std;

int main(){
   int cantAcciones;
   string accion; 
   AVL a = crearAVL();
   cin >> cantAcciones;
   for (int i = 0; i < cantAcciones; i++) {
      cin >> accion;
      if (accion == "ADD"){
         int id;
         string nombre;
         int puntaje;
         cin >> id;
         cin >> nombre;
         cin >> puntaje;
         agregarJugador(a, id, nombre, puntaje);
      } else if (accion == "FIND"){
         int id;
         cin >> id;
         encontrarJugador(a, id);
      } else if (accion == "RANK"){
         int puntaje;
         cin >> puntaje;
         contarJugadoresPuntaje(a, puntaje);
      } else if (accion == "TOP1"){
         mostrarMejorJugador(a);
      } else if (accion == "COUNT") {
         contarJugadores(a);
      }
   }
    
   return 0;
}