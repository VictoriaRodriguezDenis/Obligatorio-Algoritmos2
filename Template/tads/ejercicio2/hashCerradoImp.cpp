#include <string>
#include <iostream>
using namespace std;

class nodoRecurso
{
public:
    string path;
    string titulo;
    int tiempo;
    nodoRecurso *sig;

    nodoRecurso(string unPath, string unTitulo, int unTiempo) : path(unPath), titulo(unTitulo), tiempo(unTiempo), sig(NULL) {}
};

class nodoHashPath
{
public:
    string dominio;
    string path;
    string titulo;
    int tiempo;
    bool estaBorrado;

    nodoHashPath(string unDominio, string unPath, string unTitulo, int unTiempo) : dominio(unDominio), path(unPath), titulo(unTitulo), tiempo(unTiempo), estaBorrado(false) {}
};

class nodoHashDominio
{
public:
    nodoRecurso *raiz;
    string dominio;
    int cantRecursos;
    bool estaBorrado;

    nodoHashDominio(string unDominio) : dominio(unDominio), cantRecursos(0), estaBorrado(false), raiz(NULL) {}
};

class repHash
{
private:
    nodoHashDominio **tablaDominio;
    nodoHashPath **tablaPath;
    int tope;
    int cant;
    int largoVec;

    int fhash1(string key)
    {
        int h = 0;
        for (int i = 0; i < key.length(); i++)
            h = h + int(key[i]);
        return h;
    }

    /*
    int fhash2(string key)
    {
        int h = 0;
        for (int i = 0; i < key.length(); i++)
            h = 31 * h + int(key[i]);
        return h;
    }*/

    /*
    int fhash1(string &key) {
        long long h = 0;
        long long p = 31;
        for (char c : key) {
            h = (h * p + c) % 1000000007; // un primo grande
        }
        return int(h);
    }*/

    int fhash2(string &key) {
        long long h = 0;
        long long p = 37; // distinto de fhash1
        for (char c : key) {
            h = (h * p + c) % 1000000009; // otro primo grande
        }
        h = h * 2 + 1; // aseguramos que sea impar (requisito doble hashing)
        return int(h);
    }

    int calculateIndex(string key, int tryCount)
    {
        int val = abs(fhash1(key) + tryCount * fhash2(key));
        return val % largoVec;
    }

    bool esPrimo(int num)
    {
        if (num <= 1)
            return false;
        if (num == 2)
            return true;
        if (num % 2 == 0)
            return false;
        for (int i = 3; i * i <= num; i += 2)
        {
            if (num % i == 0)
                return false;
        }
        return true;
    }

    int primoSupMinimo(int dato)
    {
        while (!esPrimo(dato))
        {
            dato++;
        }
        return dato;
    }

    void agregarAlPrincipio(nodoRecurso *&l, string p, string t, int tiempo)
    {
        nodoRecurso *nuevo = new nodoRecurso(p, t, tiempo);
        nuevo->sig = l;
        l = nuevo;
    }

    void eliminarLista(nodoRecurso *&l)
    {
        while (l)
        {
            nodoRecurso *aBorrar = l;
            l = l->sig;
            delete aBorrar;
        }
    }

    void eliminarListaYPath(string d, nodoRecurso *&l)
    {
        while (l)
        {
            limpiarPath(d, l->path);
            nodoRecurso *aBorrar = l;
            l = l->sig;
            delete aBorrar;
        }
    }

    void agregarRecursoPorDominio(string d, string p, string t, int tiempo)
    {
        int intento = 0;
        int i = calculateIndex(d, intento);
        while (tablaDominio[i] != NULL)
        {
            if (!tablaDominio[i]->estaBorrado && tablaDominio[i]->dominio == d)
            {
                nodoRecurso *ant = nullptr;
                nodoRecurso *act = tablaDominio[i]->raiz;
                while (act)
                {
                    if (act->path == p)
                    {
                        act->titulo = t;
                        act->tiempo = tiempo;
                        if (ant)
                        { 
                            ant->sig = act->sig;
                            act->sig = tablaDominio[i]->raiz;
                            tablaDominio[i]->raiz = act;
                        }
                        return;
                    }
                    ant = act;
                    act = act->sig;
                }
                agregarAlPrincipio(tablaDominio[i]->raiz, p, t, tiempo);
                tablaDominio[i]->cantRecursos++;
                cant++;
                return;
            }
            intento++;
            i = calculateIndex(d, intento);
        }
        if (tablaDominio[i] != NULL)
        {
            tablaDominio[i]->estaBorrado = false;
            tablaDominio[i]->dominio = d;
            tablaDominio[i]->raiz = NULL;
        }
        else
        {
            tablaDominio[i] = new nodoHashDominio(d);
        }
        agregarAlPrincipio(tablaDominio[i]->raiz, p, t, tiempo);
        tablaDominio[i]->cantRecursos++;
        cant++;                      
    }

    void agregarRecursoPorPath(string d, string p, string t, int tiempo)
    {
        int intento = 0;
        int i = calculateIndex(d + p, intento);
        while (tablaPath[i] != NULL && !tablaPath[i]->estaBorrado)
        {
            if (tablaPath[i]->dominio == d && tablaPath[i]->path == p)
            {
                tablaPath[i]->titulo = t;
                tablaPath[i]->tiempo = tiempo;
                return;
            }
            intento++;
            i = calculateIndex(d + p, intento);
        }
        if (tablaPath[i] != NULL)
        {
            tablaPath[i]->estaBorrado = false;
            tablaPath[i]->dominio = d;
            tablaPath[i]->path = p;
            tablaPath[i]->titulo = t;
            tablaPath[i]->tiempo = tiempo;
        }
        else
        {
            tablaPath[i] = new nodoHashPath(d, p, t, tiempo);
        }
    }

    void borrarRecursoPorDominio(string d, string p) {
        int intento = 0;
        int i = calculateIndex(d, intento);
        while (tablaDominio[i] != NULL)
        {
            if (!tablaDominio[i]->estaBorrado && tablaDominio[i]->dominio == d)
            {
                nodoRecurso *ant = NULL;
                nodoRecurso *act = tablaDominio[i]->raiz;
                while (act && act->path != p)
                {
                    ant = act;
                    act = act->sig;
                }
                if (act)
                {
                    if (ant)
                        ant->sig = act->sig;
                    else
                        tablaDominio[i]->raiz = act->sig;
                    delete act;
                    tablaDominio[i]->cantRecursos--;
                    cant--;
                }
                return;
            }
            intento++;
            i = calculateIndex(d, intento);
        }
    }

    void limpiarPath(string d, string p) {
        int intento = 0;
        int i = calculateIndex(d + p, intento);
        while (tablaPath[i] != NULL) {
            if (!tablaPath[i]->estaBorrado && tablaPath[i]->dominio == d && tablaPath[i]->path == p) {
                tablaPath[i]->estaBorrado = true;
                return;
            }
            intento++;
            i = calculateIndex(d + p, intento);
        }
    }


public:
    repHash(int tope)
    {
        this->tope = tope;
        this->cant = 0;
        this->largoVec = primoSupMinimo(tope);
        this->tablaDominio = new nodoHashDominio *[this->largoVec];
        this->tablaPath = new nodoHashPath *[this->largoVec];
        for (int i = 0; i < this->largoVec; i++)
        {
            this->tablaDominio[i] = NULL;
            this->tablaPath[i] = NULL;
        }
    }

    void agregarRecurso(string d, string p, string t, int tiempo)
    {
        agregarRecursoPorDominio(d, p, t, tiempo);
        agregarRecursoPorPath(d, p, t, tiempo);
    }

    void obtenerRecurso(string d, string p)
    {
        int intento = 0;
        int i = calculateIndex(d + p, intento);
        while (tablaPath[i] != NULL)
        {
            if (!tablaPath[i]->estaBorrado && tablaPath[i]->dominio == d && tablaPath[i]->path == p)
            {
                cout << tablaPath[i]->titulo << " " << tablaPath[i]->tiempo << endl;
                return;
            }
            intento++;
            i = calculateIndex(d + p, intento);
        }
        cout << "recurso_no_encontrado" << endl;
    }

    void borrarRecurso(string d, string p) {
        int intento = 0;
        int i = calculateIndex(d + p, intento);
        bool encontrado = false;
        while (tablaPath[i] != NULL) {
            if (!tablaPath[i]->estaBorrado && tablaPath[i]->dominio == d && tablaPath[i]->path == p) {
                encontrado = true;
                break;
            }
            intento++;
            i = calculateIndex(d + p, intento);
        }
        if (!encontrado) return; 
        tablaPath[i]->estaBorrado = true;
        borrarRecursoPorDominio(d, p);
    }

    void perteneceRecurso(string d, string p)
    {
        int intento = 0;
        int i = calculateIndex(d + p, intento);
        while (tablaPath[i] != NULL)
        {
            if (!tablaPath[i]->estaBorrado && tablaPath[i]->dominio == d && tablaPath[i]->path == p)
            {
                cout << "true" << endl;
                return;
            }
            intento++;
            i = calculateIndex(d + p, intento);
        }
        cout << "false" << endl;
    }

    void contarDominio(string d)
    {
        int intento = 0;
        int i = calculateIndex(d, intento);
        while (tablaDominio[i] != NULL)
        {
            if (!tablaDominio[i]->estaBorrado && tablaDominio[i]->dominio == d)
            {
                cout << tablaDominio[i]->cantRecursos << endl;
                return;
            }
            intento++;
            i = calculateIndex(d, intento);
        }
        cout << 0 << endl;
    }

    void listarDominio(string d) {
        int intento = 0;
        int i = calculateIndex(d, intento);
        while (tablaDominio[i] != NULL) {
            if (!tablaDominio[i]->estaBorrado && tablaDominio[i]->dominio == d) {
                nodoRecurso *aux = tablaDominio[i]->raiz;
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
            intento++;
            i = calculateIndex(d, intento);
        }
        cout << endl;
    }

    void limpiarDominio(string d)
    {
        int intento = 0;
        int i = calculateIndex(d, intento);
        while (tablaDominio[i] != NULL)
        {
            if (!tablaDominio[i]->estaBorrado && tablaDominio[i]->dominio == d)
            {
                eliminarListaYPath(d, tablaDominio[i]->raiz);
                tablaDominio[i]->raiz = NULL;
                cant -= tablaDominio[i]->cantRecursos;
                tablaDominio[i]->cantRecursos = 0;
                return;
            }
            intento++;
            i = calculateIndex(d, intento);
        }
    }

    void totalRecursos()
    {
        cout << cant << endl;
    }

    void limpiar() {
        for (int i = 0; i < largoVec; i++) {
            if (tablaDominio[i] != NULL) {
                eliminarLista(tablaDominio[i]->raiz);
                delete tablaDominio[i];
                tablaDominio[i] = NULL;
            }
            if (tablaPath[i] != NULL) {
                delete tablaPath[i];
                tablaPath[i] = NULL;
            }
        }
        cant = 0;
    }
};
typedef repHash *Hash;