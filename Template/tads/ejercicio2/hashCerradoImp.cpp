#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

class nodoHash {
    public:
        string dominio;
        string path;
        string titulo;
        int tiempo;
        bool estaBorrado;

        nodoHash(string unDominio, string unPath, string unTitulo, int unTiempo) : dominio(unDominio), path(unPath), titulo(unTitulo), tiempo(unTiempo), estaBorrado(false) {}
};

class Hash{
    private:
        nodoHash** tablaDominio;
        nodoHash** tablaDomYPath;
        int maxElementos;
        int cantElementos;
        int largoVecDominio;
        int largoVecPath;

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

    public:
        Hash(int maxElementos){
            this->maxElementos = maxElementos;
            this->cantElementos = 0;
            this->largoVecDominio = primoSupMinimo(maxElementos);
            this->largoVecPath = primoSupMinimo(maxElementos);
            this->tablaDominio = new nodoHash*[this->largoVecDominio];
            this->tablaDomYPath = new nodoHash*[this->largoVecPath];
            for (int i = 0; i < this->largoVecDominio; i++)
            {
                this->tablaDominio[i] = NULL;
                this->tablaDomYPath[i] = NULL;
            }
        }

        void agregarRecurso(string d, string p, string t, int tiempo){
            agregarRecursoPorDominio(d, p, t, tiempo);
            agregarRecursoPorDomYPath(d, p, t, tiempo);
        }

        void agregarRecursoPorDominio(string d, string p, string t, int tiempo){

        }

        void agregarRecursoPorDomYPath(string d, string p, string t, int tiempo){

        }
};

int fHash1(string dato){
    return 0;
}

int fHash2(string dato){
    return 0;
}