#include <string>
#include <iostream>
using namespace std;

class NodoHash
{
public:
    string clave;
    int valor;
    bool estaBorrado;

    NodoHash() : clave(""), valor(-1), estaBorrado(false) {}
};

class HashCerrado
{
private:
    NodoHash *tabla;
    int largo;
    int cantidad;

    // --- Funciones hash ---
    int fhash1(const string &key) const
    {
        unsigned long h = 0;
        for (char c : key)
            h = (h * 131 + (unsigned char)c) % largo;
        return (int)h;
    }

    int fhash2(const string &key) const
    {
        unsigned long h = 0;
        for (char c : key)
            h = (h * 37 + (unsigned char)c) % largo;
        int r = (int)(h * 2 + 1) % largo;
        return (r == 0) ? 1 : r; // evitar 0
    }

    int calcularIndice(const string &key, int intento) const
    {
        return abs((fhash1(key) + intento * fhash2(key)) % largo);
    }

    bool esPrimo(int num) const
    {
        if (num < 2)
            return false;
        if (num % 2 == 0)
            return num == 2;
        for (int i = 3; i * i <= num; i += 2)
            if (num % i == 0)
                return false;
        return true;
    }

    int primoSup(int n) const
    {
        while (!esPrimo(n))
            n++;
        return n;
    }

public:
    HashCerrado(int tamAprox = 200000)
    {
        largo = primoSup(tamAprox);
        tabla = new NodoHash[largo];
        cantidad = 0;
    }

    ~HashCerrado()
    {
        delete[] tabla;
    }

    void insertar(const string &key, int valor)
    {
        int intento = 0;
        int pos = calcularIndice(key, intento);
        int primerBorrado = -1;

        while (!tabla[pos].clave.empty())
        {
            if (tabla[pos].clave == key && !tabla[pos].estaBorrado)
            {
                tabla[pos].valor = valor;
                return;
            }
            if (tabla[pos].estaBorrado && primerBorrado == -1)
                primerBorrado = pos;
            intento++;
            pos = calcularIndice(key, intento);
        }

        // Si hay un borrado reutilizable
        if (primerBorrado != -1)
            pos = primerBorrado;

        tabla[pos].clave = key;
        tabla[pos].valor = valor;
        tabla[pos].estaBorrado = false;
        cantidad++;
    }

    int buscar(const string &key) const
    {
        int intento = 0;
        int pos = calcularIndice(key, intento);

        while (!tabla[pos].clave.empty())
        {
            if (!tabla[pos].estaBorrado && tabla[pos].clave == key)
                return tabla[pos].valor;
            intento++;
            pos = calcularIndice(key, intento);
        }
        return -1;
    }

    void borrar(const string &key)
    {
        int intento = 0;
        int pos = calcularIndice(key, intento);

        while (!tabla[pos].clave.empty())
        {
            if (!tabla[pos].estaBorrado && tabla[pos].clave == key)
            {
                tabla[pos].estaBorrado = true;
                cantidad--;
                return;
            }
            intento++;
            pos = calcularIndice(key, intento);
        }
    }

    int tamano() const
    {
        return cantidad;
    }
};
