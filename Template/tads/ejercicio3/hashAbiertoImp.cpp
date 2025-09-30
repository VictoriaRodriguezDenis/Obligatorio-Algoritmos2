#include <string>
#include <iostream>
using namespace std;

class nodoRecurso {
public:
    string path;
    string titulo;
    int tiempo;
    nodoRecurso* sig;

    nodoRecurso(string unPath, string unTitulo, int unTiempo) :
        path(unPath), titulo(unTitulo), tiempo(unTiempo), sig(NULL) {}
};

class nodoHashPath {
public:
    string dominio;
    string path;
    string titulo;
    int tiempo;
    nodoHashPath* sig;

    nodoHashPath(string unDominio, string unPath, string unTitulo, int unTiempo) :
        dominio(unDominio), path(unPath), titulo(unTitulo), tiempo(unTiempo), sig(NULL) {}
};

class nodoHashDominio {
public:
    string dominio;
    nodoRecurso* raiz;
    int cantRecursos;
    nodoHashDominio* sig;

    nodoHashDominio(string unDominio) :
        dominio(unDominio), raiz(NULL), cantRecursos(0), sig(NULL) {}
};

class repHash {
private:
    nodoHashDominio** tablaDominio;
    nodoHashPath** tablaPath;
    int largoVec;
    int cant;

    int fhash(string& key) {
        long long h = 0;
        long long p = 31;
        for (char c : key) {
            h = (h * p + c) % 1000000007;
        }
        return int(h);
    }

    int calculateIndex(string& key) {
        return fhash(key) % largoVec;
    }

    void agregarAlPrincipio(nodoRecurso*& l, string p, string t, int tiempo) {
        nodoRecurso* nuevo = new nodoRecurso(p, t, tiempo);
        nuevo->sig = l;
        l = nuevo;
    }

public:
    repHash(int tope) {
        largoVec = tope * 4;
        tablaDominio = new nodoHashDominio*[largoVec];
        tablaPath = new nodoHashPath*[largoVec];
        for (int i = 0; i < largoVec; i++) {
            tablaDominio[i] = NULL;
            tablaPath[i] = NULL;
        }
        cant = 0;
    }

    void agregarRecurso(string d, string p, string t, int tiempo) {
        int idxDom = calculateIndex(d);
        int idxPath = calculateIndex(d + p);

        // ---- Dominio ----
        nodoHashDominio* dom = tablaDominio[idxDom];
        while (dom) {
            if (dom->dominio == d) {
                nodoRecurso* act = dom->raiz;
                nodoRecurso* ant = NULL;
                while (act) {
                    if (act->path == p) {
                        // Actualizar recurso existente
                        act->titulo = t;
                        act->tiempo = tiempo;
                        return;
                    }
                    ant = act;
                    act = act->sig;
                }
                // No existe el path → agregar
                agregarAlPrincipio(dom->raiz, p, t, tiempo);
                dom->cantRecursos++;
                cant++;
                return;
            }
            dom = dom->sig;
        }
        // Dominio no existe → crear
        nodoHashDominio* nuevoDom = new nodoHashDominio(d);
        agregarAlPrincipio(nuevoDom->raiz, p, t, tiempo);
        nuevoDom->cantRecursos++;
        cant++;
        nuevoDom->sig = tablaDominio[idxDom];
        tablaDominio[idxDom] = nuevoDom;

        // ---- Path ----
        nodoHashPath* nuevoPath = new nodoHashPath(d, p, t, tiempo);
        nuevoPath->sig = tablaPath[idxPath];
        tablaPath[idxPath] = nuevoPath;
    }

    void obtenerRecurso(string d, string p) {
        int idxPath = calculateIndex(d + p);
        nodoHashPath* pathElem = tablaPath[idxPath];
        while (pathElem) {
            if (pathElem->dominio == d && pathElem->path == p) {
                cout << pathElem->titulo << " " << pathElem->tiempo << endl;
                return;
            }
            pathElem = pathElem->sig;
        }
        cout << "recurso_no_encontrado" << endl;
    }

    void borrarRecurso(string d, string p) {
        int idxDom = calculateIndex(d);
        int idxPath = calculateIndex(d + p);

        // borrar en dominio
        nodoHashDominio* dom = tablaDominio[idxDom];
        nodoHashDominio* antDom = NULL;
        while (dom) {
            if (dom->dominio == d) {
                nodoRecurso* act = dom->raiz;
                nodoRecurso* ant = NULL;
                while (act) {
                    if (act->path == p) {
                        if (ant) ant->sig = act->sig;
                        else dom->raiz = act->sig;
                        delete act;
                        dom->cantRecursos--;
                        cant--;
                        break;
                    }
                    ant = act;
                    act = act->sig;
                }
                break;
            }
            antDom = dom;
            dom = dom->sig;
        }

        // borrar en path
        nodoHashPath* pathElem = tablaPath[idxPath];
        nodoHashPath* antPath = NULL;
        while (pathElem) {
            if (pathElem->dominio == d && pathElem->path == p) {
                if (antPath) antPath->sig = pathElem->sig;
                else tablaPath[idxPath] = pathElem->sig;
                delete pathElem;
                break;
            }
            antPath = pathElem;
            pathElem = pathElem->sig;
        }
    }

    void totalRecursos() {
        cout << cant << endl;
    }
};
typedef repHash* Hash;
