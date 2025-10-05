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
    int tope;
    int cant;
    int largoVec;

    int fhash(string key)
    {
        int h = 0;
        for (int i = 0; i < key.length(); i++)
            h = h + int(key[i]);
        return h;
    }

    int calculateIndex(string key) {
        return abs(fhash(key)) % largoVec;
    }

    bool esPrimo(int num) {
        if (num <= 1) return false;
        if (num == 2) return true;
        if (num % 2 == 0) return false;
        for (int i = 3; i * i <= num; i += 2) {
            if (num % i == 0) return false;
        }
        return true;
    }

    int primoSupMinimo(int dato) {
        while (!esPrimo(dato)) {
            dato++;
        }
        return dato;
    }

    void agregarAlPrincipio(nodoRecurso*& l, string p, string t, int tiempo) {
        nodoRecurso* nuevo = new nodoRecurso(p, t, tiempo);
        nuevo->sig = l;
        l = nuevo;
    }

    void eliminarLista(nodoRecurso*& l) {
        while (l) {
            nodoRecurso* aBorrar = l;
            l = l->sig;
            delete aBorrar;
        }
    }

    void eliminarListaYPath(string d, nodoRecurso*& l) {
        while (l) {
            limpiarPath(d, l->path);
            nodoRecurso* aBorrar = l;
            l = l->sig;
            delete aBorrar;
        }
    }

    void agregarRecursoPorDominio(string d, string p, string t, int tiempo) {
        int i = calculateIndex(d);
        nodoHashDominio* dom = tablaDominio[i];
        nodoHashDominio* antDom = NULL;
        while (dom) {
            if (dom->dominio == d) {
                nodoRecurso* act = dom->raiz;
                nodoRecurso* ant = NULL;
                while (act) {
                    if (act->path == p) {
                        act->titulo = t;
                        act->tiempo = tiempo;
                        if (ant) {
                            ant->sig = act->sig;
                            act->sig = dom->raiz;
                            dom->raiz = act;
                        }
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
            antDom = dom;
            dom = dom->sig;
        }
        // Dominio no existe → crear
        nodoHashDominio* nuevoDom = new nodoHashDominio(d);
        agregarAlPrincipio(nuevoDom->raiz, p, t, tiempo);
        nuevoDom->cantRecursos++;
        cant++;
        nuevoDom->sig = tablaDominio[i];
        tablaDominio[i] = nuevoDom;
    }

    void agregarRecursoPorPath(string d, string p, string t, int tiempo) {
        int i = calculateIndex(d+p);
        nodoHashPath* pathElem = tablaPath[i];
        while (pathElem) {
            if (pathElem->dominio == d && pathElem->path == p) {
                pathElem->titulo = t;
                pathElem->tiempo = tiempo;
                return;
            }
            pathElem = pathElem->sig;
        }
        nodoHashPath* nuevoPath = new nodoHashPath(d, p, t, tiempo);
        nuevoPath->sig = tablaPath[i];
        tablaPath[i] = nuevoPath;
    }

    void borrarRecursoPorDominio(string d, string p) {
        int i = calculateIndex(d);
        nodoHashDominio* dom = tablaDominio[i];
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
                        /*
                        if (dom->cantRecursos == 0) {
                            // Eliminar dominio si está vacío
                            if (antDom) antDom->sig = dom->sig;
                            else tablaDominio[i] = dom->sig;
                            delete dom;
                        }*/
                        return;
                    }
                    ant = act;
                    act = act->sig;
                }
                return;
            }
            antDom = dom;
            dom = dom->sig;
        }
    }
    
    void limpiarPath(string d, string p) {
        int i = calculateIndex(d + p);
        nodoHashPath* pathElem = tablaPath[i];
        nodoHashPath* antPath = NULL;
        while (pathElem) {
            if (pathElem->dominio == d && pathElem->path == p) {
                if (antPath) antPath->sig = pathElem->sig;
                else tablaPath[i] = pathElem->sig;
                delete pathElem;
                return;
            }
            antPath = pathElem;
            pathElem = pathElem->sig;
        }
    }

public:
    repHash(int tope) {
        this->tope = tope;
        this->cant = 0;
        this->largoVec = primoSupMinimo(tope);
        this->tablaDominio = new nodoHashDominio*[largoVec];
        this->tablaPath = new nodoHashPath*[largoVec];
        for (int i = 0; i < largoVec; i++) {
            tablaDominio[i] = NULL;
            tablaPath[i] = NULL;
        }
    }

    void agregarRecurso(string d, string p, string t, int tiempo) {
        agregarRecursoPorDominio(d, p, t, tiempo);
        agregarRecursoPorPath(d, p, t, tiempo);
    }

    void obtenerRecurso(string d, string p) {
        int i = calculateIndex(d + p);
        nodoHashPath* pathElem = tablaPath[i];
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
        int i = calculateIndex(d + p);
        // Verificar si existe en tablaPath
        nodoHashPath* pathElem = tablaPath[i];
        bool encontrado = false;
        while (pathElem) {
            if (pathElem->dominio == d && pathElem->path == p) {
                encontrado = true;
                break;
            }
            pathElem = pathElem->sig;
        }
        if (!encontrado) return;

        // Borrar en ambas tablas
        limpiarPath(d, p);
        borrarRecursoPorDominio(d, p);
    }

    void perteneceRecurso(string d, string p) {
        int i = calculateIndex(d + p);
        nodoHashPath* pathElem = tablaPath[i];
        while (pathElem) {
            if (pathElem->dominio == d && pathElem->path == p) {
                cout << "true" << endl;
                return;
            }
            pathElem = pathElem->sig;
        }
        cout << "false" << endl;
    }

    void contarDominio(string d) {
        int i = calculateIndex(d);
        nodoHashDominio* dom = tablaDominio[i];
        while (dom) {
            if (dom->dominio == d) {
                cout << dom->cantRecursos << endl;
                return;
            }
            dom = dom->sig;
        }
        cout << 0 << endl;
    }

    void listarDominio(string d) {
        int i = calculateIndex(d);
        nodoHashDominio* dom = tablaDominio[i];
        while (dom) {
            if (dom->dominio == d) {
                nodoRecurso* aux = dom->raiz;
                if (!aux) {
                    cout << endl;
                    return;
                }
                while (aux) {
                    cout << aux->path;
                    aux = aux->sig;
                    if (aux) cout << " ";
                }
                cout << endl;
                return;
            }
            dom = dom->sig;
        }
        cout << endl;
    }

    void limpiarDominio(string d) {
        int i = calculateIndex(d);
        nodoHashDominio* dom = tablaDominio[i];
        nodoHashDominio* antDom = NULL;
        while (dom) {
            if (dom->dominio == d) {
                eliminarListaYPath(d, dom->raiz);
                dom->raiz = NULL;
                cant -= dom->cantRecursos;
                dom->cantRecursos = 0;
                return;
            }
            antDom = dom;
            dom = dom->sig;
        }
    }

    void totalRecursos() {
        cout << cant << endl;
    }

    void limpiar() {
        for (int i = 0; i < largoVec; i++) {
            nodoHashDominio* dom = tablaDominio[i];
            while (dom) {
                eliminarLista(dom->raiz);
                nodoHashDominio* aBorrar = dom;
                dom = dom->sig;
                delete aBorrar;
            }
            tablaDominio[i] = NULL;
            nodoHashPath* pathElem = tablaPath[i];
            while (pathElem) {
                nodoHashPath* aBorrar = pathElem;
                pathElem = pathElem->sig;
                delete aBorrar;
            }
            tablaPath[i] = NULL;
        }
        cant = 0;
    }
};
typedef repHash* Hash;