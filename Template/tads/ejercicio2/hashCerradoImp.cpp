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

class repHash{
    private:
        nodoHash** tablaDominio;
        nodoHash** tablaDomYPath;
        int tope;
        int cant;
        int largoVec;
        
        int fHash1(string dominio) {
            int suma = 0;
            for (char c : dominio) {
                suma += c;
            }
            return suma % largoVec;
        }

        int fHash2(string dominio, string path) {
            int suma = 0;
            string clave = dominio + path;
            for (char c : clave) {
                suma += c;
            }
            return 1 + (suma % (largoVec - 1));
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

        void agregarRecursoPorDominio(string d, string p, string t, int tiempo){
            int i = fHash1(d)%largoVec;
            int j = fHash2(d, p)%largoVec;
            while(tablaDominio[i] && !tablaDominio[i]->estaBorrado){
                if(tablaDominio[i]->dominio == d && tablaDominio[i]->path == p){
                    tablaDominio[i]->titulo = t;
                    tablaDominio[i]->tiempo = tiempo;
                    return;
                }
                i = (i + j) % largoVec;
            }
            if(tablaDominio[i]){
                //estaba borrado -> reuso el nodo
                tablaDominio[i]->estaBorrado=false;
                tablaDominio[i]->dominio = d;
                tablaDominio[i]->path = p;
                tablaDominio[i]->titulo = t;
                tablaDominio[i]->tiempo = tiempo;
            } else {
                // estaba vacio -> crea un nodo nuevo
                tablaDominio[i] = new nodoHash(d, p, t, tiempo);
            }
            cant++;
        }

        void agregarRecursoPorDomYPath(string d, string p, string t, int tiempo){
            int i = fHash1(d);
            int j = fHash2(d, p);
            while(tablaDomYPath[j] && !tablaDomYPath[j]->estaBorrado){
                if(tablaDomYPath[j]->dominio == d && tablaDomYPath[j]->path == p){
                    tablaDomYPath[j]->titulo = t;
                    tablaDomYPath[j]->tiempo = tiempo;
                    return;
                }
                j = (i + j) % largoVec;
            }
            if(tablaDomYPath[j]){
                tablaDomYPath[j]->estaBorrado=false;
                tablaDomYPath[j]->dominio = d;
                tablaDomYPath[j]->path = p;
                tablaDomYPath[j]->titulo = t;
                tablaDomYPath[j]->tiempo = tiempo;
            } else {
                tablaDomYPath[j] = new nodoHash(d, p, t, tiempo);
            }
        }

    public:
        repHash(int tope){
            this->tope = tope;
            this->cant = 0;
            this->largoVec = primoSupMinimo(tope);
            this->tablaDominio = new nodoHash*[this->largoVec];
            this->tablaDomYPath = new nodoHash*[this->largoVec];
            for (int i = 0; i < this->largoVec; i++)
            {
                this->tablaDominio[i] = NULL;
                this->tablaDomYPath[i] = NULL;
            }
        }

        void agregarRecurso(string d, string p, string t, int tiempo){
            agregarRecursoPorDominio(d, p, t, tiempo);
            agregarRecursoPorDomYPath(d, p, t, tiempo);
        }

        void obtenerRecurso(string d, string p){
            int i = fHash1(d)%largoVec;
            int j = fHash2(d, p)%largoVec;
            while(tablaDomYPath[i]){
                if(!tablaDomYPath[i]->estaBorrado && tablaDomYPath[i]->dominio == d && tablaDomYPath[i]->path == p){
                    cout << tablaDomYPath[i]->titulo << " " << tablaDomYPath[i]->tiempo << endl;
                    return;
                }
                i = (i + j) % largoVec; // rari
            }
            cout << "recurso_no_encontrado" << endl;
        }
   
        void borrarRecurso(string d, string p){
            int i = fHash1(d)%largoVec;
            int j = fHash2(d, p)%largoVec;
            while(tablaDomYPath[i] && !(tablaDomYPath[i]->dominio == d && tablaDomYPath[i]->path == p && !tablaDomYPath[i]->estaBorrado)) {
                i = (i + j) % largoVec;
            }
            if (tablaDomYPath[i] && !tablaDomYPath[i]->estaBorrado) tablaDomYPath[i]->estaBorrado = true;
            else return; // No existe

            int nuevoi = fHash1(d) % largoVec;
            int nuevoj = fHash2(d, p) % largoVec;
            while(tablaDominio[nuevoi] && !(tablaDominio[nuevoi]->dominio == d && tablaDominio[nuevoi]->path == p && !tablaDominio[nuevoi]->estaBorrado)) {
                nuevoi = (nuevoi + nuevoj) % largoVec;
            }
            if (tablaDominio[nuevoi] && !tablaDominio[nuevoi]->estaBorrado) tablaDominio[nuevoi]->estaBorrado = true;
            cant--;
        }

        void perteneceRecurso(string d, string p){
            int i = fHash1(d)%largoVec;
            int j = fHash2(d, p)%largoVec;
            while(tablaDomYPath[i]){
                if(!tablaDomYPath[i]->estaBorrado && tablaDomYPath[i]->dominio == d && tablaDomYPath[i]->path == p) {
                    cout << "true" << endl;
                    return;
                }
                i = (i + j) % largoVec; // rari
            }
            cout << "false" << endl;            
        }

        int contadorDominio(string dominio){
                      
            
            //ver el orden
             /*
        class Hash {
        private:n
            // ... (todo lo que ya tienes)
            unordered_map<string, it> contadorPorDominio;

        public:
            // ... (tus funciones existentes)

            void agregarRecursoPorDominio(string d, string p, string t, int tiempo) {
                // ... (tu código existente de agregar)
                // PERO agregar esta línea al final:
                contadorPorDominio[d]++;
            }

            void borrarRecurso(string d, string p) {
                // ... (tu código existente de borrar)
                // PERO agregar esta línea al final:
                contadorPorDominio[d]--;
            }

            int countDomain(string dominio) {
                return contadorPorDominio[dominio];
            }
        };
        */
        }

        void listarDominio(string d){
            int i = fHash1(d)%largoVec;
            int j = fHash2(d, d)%largoVec;
            while(tablaDominio[i] && !tablaDominio[i]->estaBorrado){
                if(tablaDominio[i]->dominio == d){
                    cout << tablaDominio[i]->path << endl;
                }
                i = (i + j) % largoVec;
            }
            cout << "" << endl;     
        }

/*
void listarDominio(string d) {
    // arreglo auxiliar para guardar paths
    string lista[1000];  // si querés hacerlo más genérico, podrías usar cant o largoVec
    int cantPaths = 0;

    // recolectar todos los paths del dominio
    for (int i = 0; i < largoVec; i++) {
        if (tablaDominio[i] && !tablaDominio[i]->estaBorrado && tablaDominio[i]->dominio == d) {
            lista[cantPaths++] = tablaDominio[i]->path;
        }
    }

    // imprimir en orden inverso (más reciente primero)
    for (int i = cantPaths - 1; i >= 0; i--) {
        cout << lista[i];
        if (i > 0) cout << " ";
    }
    cout << endl;
}

*/


        void totalRecursos(){
            cout << cant << endl;
        }

        void limpiar(){
            for (int i = 0; i < largoVec; i++) {
                if (tablaDominio[i]) {
                    delete tablaDominio[i];
                    tablaDominio[i] = NULL;
                }
            }
            for (int i = 0; i < largoVec; i++) {
                if (tablaDomYPath[i]) {
                    delete tablaDomYPath[i];
                    tablaDomYPath[i] = NULL;
                }
            }
            cant = 0;
       }
};
typedef repHash * Hash;

//cuales funciones van en el private y cuales van en el public, van las que usamos en el main
