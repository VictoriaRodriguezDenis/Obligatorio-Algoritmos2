#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

class nodoHashPath {
    public:
        string dominio;
        string path;
        string titulo;
        int tiempo;
        bool estaBorrado;

        nodoHashPath(string unDominio, string unPath, string unTitulo, int unTiempo) : dominio(unDominio), path(unPath), titulo(unTitulo), tiempo(unTiempo), estaBorrado(false) {}
};

class nodoHashDominio {
    public:
        nodoRecurso* raiz;
        string dominio;
        int cantRecursos;
        bool estaBorrado;

        nodoHashDominio(string unDominio) : dominio(unDominio), cantRecursos(0), estaBorrado(false), raiz(NULL) {}
};

class nodoRecurso {
    public:
        string path;
        string titulo;
        int tiempo;	
        nodoRecurso* sig;

        nodoRecurso(string unPath, string unTitulo, int unTiempo) : path(unPath), titulo(unTitulo), tiempo(unTiempo), sig(NULL) {}
};

class repHash {
	private:
        nodoHashDominio** tablaDominio;
        nodoHashPath** tablaPath;	
        int tope;
        int cant;
        int largoVec;

        int fhash1(string key) {
            int h = 0;
            for (int i = 0; i < key.length(); i++)
                h = h + key[i];
            return h;
        }

        int fhash2(string key) {
            int h = 0;
            for (int i = 0; i < key.length(); i++)
                h = 31 * h + int(key[i]);
            return h;
        }

        int calculateIndex(string key, int tryCount) {
            return abs(fhash1(key) + tryCount * fhash2(key)) % largoVec;
        }

        bool esPrimo(int num){
            if(num<=1 || num%2==0 && num!=2) return false;
            if(num==2) return true;
            for (int i = 3; i < num/2; i+=2)
            {
                if(num%i==0)
                {
                    return false;
                }
            }
            return true;    
        }

        int primoSupMinimo(int dato){
            while(!esPrimo(dato)){
                dato++;
            }
            return dato;
        }

        void agregarAlPrincipio(nodoRecurso*& l, string p, string t, int tiempo){
            nodoRecurso* nuevo = new nodoRecurso(p, t, tiempo);
            nuevo->sig = l;
            l = nuevo;
        }

        void eliminarLista (nodoRecurso*& l){
            while (l){
                nodoRecurso* aBorrar = l;
                l = l->sig;
                delete aBorrar;
            }
        }

        void eliminarListaYPath (string d, nodoRecurso*& l){
            while (l){
                limpiarPath(d, l->path);
                nodoRecurso* aBorrar = l;
                l = l->sig;
                delete aBorrar;
            }
        }

        void agregarRecursoPorDominio(string d, string p, string t, int tiempo){
            int intento = 0;
            int i = calculateIndex(d, intento);;
            while(tablaDominio[i] && !tablaDominio[i]->estaBorrado){
                if(tablaDominio[i]->dominio == d){
                    agregarAlPrincipio(tablaDominio[i]->raiz, p, t, tiempo);
                    return;
                }
                intento++;
                i = calculateIndex(d, intento);
            }
            if(tablaDominio[i]){
                //estaba borrado -> reuso el nodo
                tablaDominio[i]->estaBorrado=false;
                agregarAlPrincipio(tablaDominio[i]->raiz, p, t, tiempo);
            } else {
                // estaba vacio -> crea un nodo nuevo
                tablaDominio[i] = new nodoHashDominio(d);
                agregarAlPrincipio(tablaDominio[i]->raiz, p, t, tiempo);
            }
            tablaDominio[i]->cantRecursos++;
            cant++;
        }

        void agregarRecursoPorPath(string d, string p, string t, int tiempo){
            int intento = 0;
            int i = calculateIndex(d+p, intento);;
            while(tablaPath[i] && !tablaPath[i]->estaBorrado){
                if(tablaPath[i]->dominio == d && tablaPath[i]->path == p){
                    tablaPath[i]->titulo = t;
                    tablaPath[i]->tiempo = tiempo;
                    return;
                }
                intento++;
                i = calculateIndex(d+p, intento);
            }
            if(tablaPath[i]){
                tablaPath[i]->estaBorrado=false;
                tablaPath[i]->dominio = d;
                tablaPath[i]->path = p;
                tablaPath[i]->titulo = t;
                tablaPath[i]->tiempo = tiempo;
            } else {
                tablaPath[i] = new nodoHashPath(d, p, t, tiempo);
            }
        }

        void borrarRecursoPorPath(string d, string p){
            int intento = 0;
            int i = calculateIndex(d+p, intento);
            while(tablaPath[i] && !(tablaPath[i]->dominio == d && tablaPath[i]->path == p && !tablaPath[i]->estaBorrado)) {
                intento++;
                i = calculateIndex(d+p, intento);
            }
            if (tablaPath[i] && !tablaPath[i]->estaBorrado) tablaPath[i]->estaBorrado = true;
            else return; // No existe
        }
        
        void borrarRecursoPorDominio(string d, string p){ // HAY QUE CAMBIARLO
            int intento = 0;
            int i = calculateIndex(d, intento);
            while(tablaDominio[i] && !(tablaDominio[i]->dominio == d && !tablaDominio[i]->estaBorrado)) {
                intento++;
                i = calculateIndex(d, intento);
            }
            if (tablaDominio[i] && !tablaDominio[i]->estaBorrado) {
                // un while con dos punteros
                tablaDominio[i]->estaBorrado = true;
            }
        }

    public:
        repHash(int tope){
            this->tope = tope;
            this->cant = 0;
            this->largoVec = 0;
            this->tablaDominio = new nodoHashDominio*[this->largoVec];
            this->tablaPath = new nodoHashPath*[this->largoVec];
            for (int i = 0; i < this->largoVec; i++)
            {
                this->tablaDominio[i] = NULL;
                this->tablaPath[i] = NULL;
            }
            
        }

        void agregarRecurso(string d, string p, string t, int tiempo){
            agregarRecursoPorDominio(d, p, t, tiempo);
            agregarRecursoPorPath(d, p, t, tiempo);
        }

        void obtenerRecurso(string d, string p){
            int intento = 0;
            int i = calculateIndex(d+p, intento);
            while(tablaPath[i]){
                if(!tablaPath[i]->estaBorrado && tablaPath[i]->dominio == d && tablaPath[i]->path == p){
                    cout << tablaPath[i]->titulo << " " << tablaPath[i]->tiempo << endl;
                    return;
                }
                intento++;
                i = calculateIndex(d+p, intento);
            }
            cout << "recurso_no_encontrado" << endl;
        }

        void borrarRecurso(string d, string p){
            borrarRecursoPorDominio(d, p);
            borrarRecursoPorPath(d, p);
            cant--;
        }

        void perteneceRecurso(string d, string p){
            int intento = 0;
            int i = calculateIndex(d+p, intento);
            while(tablaPath[i]){
                if(!tablaPath[i]->estaBorrado && tablaPath[i]->dominio == d && tablaPath[i]->path == p) {
                    cout << "true" << endl;
                    return;
                }
                intento++;
                i = calculateIndex(d+p, intento);
            }
            cout << "false" << endl;            
        }

        void contarDominio(string d){
            int intento = 0;
            int i = calculateIndex(d, intento);
            while(tablaDominio[i] && !tablaDominio[i]->estaBorrado){
                if(tablaDominio[i]->dominio == d){
                    cout << tablaDominio[i]->cantRecursos << endl;
                    return;
                }
                intento++;
                i = calculateIndex(d, intento);
            }
        }

        void listarDominio(string d){
            int intento = 0;
            int i = calculateIndex(d, intento);
            while(tablaDominio[i] && !tablaDominio[i]->estaBorrado){
                if(tablaDominio[i]->dominio == d){
                    if (!tablaDominio[i]->raiz) {
                        cout << " " << endl;
                        return;
                    }
                    while (tablaDominio[i]->raiz){    
                        cout << tablaDominio[i]->raiz->path << " " << endl;
                        tablaDominio[i]->raiz=tablaDominio[i]->raiz->sig;
                    }
                    
                    return;
                }
                intento++;
                i = calculateIndex(d, intento);
            }
            cout << " " << endl;
        }

        void limpiarDominio(string d){
            int intento = 0;
            int i = calculateIndex(d, intento);
            while(tablaDominio[i] && !tablaDominio[i]->estaBorrado){
                if(tablaDominio[i]->dominio == d){
                    // Conocer los paths.
                    eliminarListaYPath(d, tablaDominio[i]->raiz);
                    return;
                }
                intento++;
                i = calculateIndex(d, intento);
            }
            cout << " " << endl;
        }

        void limpiarPath(string d, string p){
            int intento = 0;
            int i = calculateIndex(d+p, intento);
            while(tablaDominio[i] && !tablaDominio[i]->estaBorrado){
                if(!tablaPath[i]->estaBorrado && tablaPath[i]->dominio == d && tablaPath[i]->path == p){
                    tablaPath[i]->estaBorrado = true;
                    return;
                }
                intento++;
                i = calculateIndex(d, intento);
            }
            cout << " " << endl;
        }

        void totalRecursos(){
            cout << cant << endl;
        }

        void limpiar(){
            for (int i = 0; i < largoVec; i++) {
                if (tablaDominio[i]) {
                    eliminarLista(tablaDominio[i]->raiz);
                    delete tablaDominio[i];
                    tablaDominio[i] = NULL;
                }
            }
            for (int i = 0; i < largoVec; i++) {
                if (tablaPath[i]) {
                    delete tablaPath[i];
                    tablaPath[i] = NULL;
                }
            }
            cant = 0;
       }
};
typedef repHash * Hash;

