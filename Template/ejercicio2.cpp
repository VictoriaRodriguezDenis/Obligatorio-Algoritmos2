#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads\ejercicio2\hashCerradoImp2.cpp"
using namespace std;

int main()
{
    int cantAcciones;
    string accion; 
    cin >> cantAcciones;
    Hash h = new repHash(cantAcciones);
    for (int i = 0; i < cantAcciones; i++) {
        cin >> accion;
        if (accion == "PUT"){
            string dominio;
            string path;
            string titulo;
            int tiempo;
            cin >> dominio;
            cin >> path;
            cin >> titulo;
            cin >> tiempo;
            h->agregarRecurso(dominio, path, titulo, tiempo);
        } else if (accion == "GET"){
            string dominio;
            string path;
            cin >> dominio;
            cin >> path;
            h->obtenerRecurso(dominio, path);
        } else if (accion == "REMOVE"){
            string dominio;
            string path;
            cin >> dominio;
            cin >> path;
            h->borrarRecurso(dominio, path);
        } else if (accion == "COUNT_DOMAIN"){
            string dominio;
            cin >> dominio;
            h->contarDominio(dominio);
        } else if (accion == "LIST_DOMAIN") {
            string dominio;
            cin >> dominio;
            h->listarDominio(dominio);
        } else if (accion == "CLEAR_DOMAIN"){
            string dominio;
            cin >> dominio;
            h->limpiarDominio(dominio);
        } else if (accion == "SIZE") {
            h->totalRecursos();
        } else if (accion == "CLEAR") {
            h->limpiar();
        }
    }
        
    return 0;
}