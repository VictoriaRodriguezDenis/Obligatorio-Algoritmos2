#include <string>
#include <iostream>
using namespace std;

class NodoHash
{
public:
    string clave;
    int valor;
    bool estaBorrado;

    NodoHash()
    {
        clave = "";
        valor = -1;
        estaBorrado = false;
    }
};

class HashCerrado
{
private:
    NodoHash *tabla;
    int largo;
    int cantidad;

    int fhash1(string key)
    {
        int h = 0;
        for (int i = 0; i < key.size(); i++)
            h = (h * 131 + (int)key[i]) % largo;
        return h;
    }

    int fhash2(string key)
    {
        int h = 0;
        for (int i = 0; i < key.size(); i++)
            h = (h * 37 + (int)key[i]) % largo;
        int r = (h * 2 + 1) % largo;
        if (r == 0)
            r = 1;
        return r;
    }

    int calcularIndice(string key, int intento)
    {
        return abs((fhash1(key) + intento * fhash2(key)) % largo);
    }

    bool esPrimo(int n)
    {
        if (n < 2)
            return false;
        if (n % 2 == 0)
            return n == 2;
        for (int i = 3; i * i <= n; i += 2)
            if (n % i == 0)
                return false;
        return true;
    }

    int primoSuperior(int n)
    {
        while (!esPrimo(n))
            n++;
        return n;
    }

public:
    HashCerrado(int tamAprox = 200000)
    {
        largo = primoSuperior(tamAprox);
        tabla = new NodoHash[largo];
        cantidad = 0;
    }

    ~HashCerrado()
    {
        delete[] tabla;
    }

    void insertar(string key, int valor)
    {
        int intento = 0;
        int pos = calcularIndice(key, intento);
        int primerBorrado = -1;

        while (tabla[pos].clave != "")
        {
            if (tabla[pos].clave == key && tabla[pos].estaBorrado == false)
            {
                tabla[pos].valor = valor;
                return;
            }
            if (tabla[pos].estaBorrado && primerBorrado == -1)
                primerBorrado = pos;

            intento++;
            pos = calcularIndice(key, intento);
        }

        if (primerBorrado != -1)
            pos = primerBorrado;

        tabla[pos].clave = key;
        tabla[pos].valor = valor;
        tabla[pos].estaBorrado = false;
        cantidad++;
    }

    int buscar(string key)
    {
        int intento = 0;
        int pos = calcularIndice(key, intento);

        while (tabla[pos].clave != "")
        {
            if (tabla[pos].clave == key && tabla[pos].estaBorrado == false)
                return tabla[pos].valor;
            intento++;
            pos = calcularIndice(key, intento);
        }
        return -1;
    }

    void borrar(string key)
    {
        int intento = 0;
        int pos = calcularIndice(key, intento);

        while (tabla[pos].clave != "")
        {
            if (tabla[pos].clave == key && tabla[pos].estaBorrado == false)
            {
                tabla[pos].estaBorrado = true;
                cantidad--;
                return;
            }
            intento++;
            pos = calcularIndice(key, intento);
        }
    }
};
