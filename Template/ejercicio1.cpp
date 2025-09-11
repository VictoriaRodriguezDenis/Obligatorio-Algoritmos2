#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads\ejercicio1\avlImp.cpp"

using namespace std;

int main(){
   int cantAcciones;
   string accion; 
   AVL* a = new AVL();
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
         a->agregarJugador(id, nombre, puntaje);
      } else if (accion == "FIND"){
         int id;
         cin >> id;
         a->encontrarJugador(id);
      } else if (accion == "RANK"){
         int puntaje;
         cin >> puntaje;
         a->contarJugadoresPuntaje(puntaje);
      } else if (accion == "TOP1"){
         a->mostrarMejorJugador();
      } else if (accion == "COUNT") {
         a->contarJugadores();
      }
   }
    
   return 0;
}