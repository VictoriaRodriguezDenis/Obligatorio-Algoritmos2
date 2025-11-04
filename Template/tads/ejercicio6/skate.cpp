#include <iostream>
using namespace std;

const int MAXN = 100000;

struct Pozo
{
    int inicio, fin;
};

struct Mejora
{
    int posicion, aumento;
};

class HeapMax
{
private:
    int datos[MAXN + 5];
    int n;

    void flotar(int i)
    {
        while (i > 1 && datos[i] > datos[i / 2])
        {
            swap(datos[i], datos[i / 2]);
            i /= 2;
        }
    }

    void hundir(int i)
    {
        while (2 * i <= n)
        {
            int hijo = 2 * i;
            if (hijo < n && datos[hijo + 1] > datos[hijo])
                hijo++;
            if (datos[i] >= datos[hijo])
                break;
            swap(datos[i], datos[hijo]);
            i = hijo;
        }
    }

public:
    HeapMax() : n(0) {}

    bool vacio() { return n == 0; }

    void encolar(int valor)
    {
        datos[++n] = valor;
        flotar(n);
    }

    int maximo() { return datos[1]; }

    void desencolar()
    {
        datos[1] = datos[n--];
        hundir(1);
    }
};

int resolverSkate(Pozo pozos[], int N, Mejora mejoras[], int M, int destino)
{
    int posicion = 1, poder = 1, mejorasUsadas = 0;
    int idxPozo = 0, idxMejora = 0;
    HeapMax heap;

    while (posicion < destino)
    {
        // Saltar pozos que ya dejamos atrás
        while (idxPozo < N && pozos[idxPozo].fin < posicion)
            idxPozo++;

        int alcanceMaximo = posicion + poder;

        // ¿Ya llegamos?
        if (alcanceMaximo >= destino)
            return mejorasUsadas;

        // Recolectar todas las mejoras al alcance
        while (idxMejora < M && mejoras[idxMejora].posicion <= alcanceMaximo)
        {
            heap.encolar(mejoras[idxMejora].aumento);
            idxMejora++;
        }

        // Ajustar alcance si hay un pozo que lo bloquea parcialmente
        if (idxPozo < N && pozos[idxPozo].inicio <= alcanceMaximo && pozos[idxPozo].inicio > posicion)
        {
            if (pozos[idxPozo].fin >= alcanceMaximo)
                alcanceMaximo = pozos[idxPozo].inicio - 1;
        }

        // ¿Podemos avanzar?
        if (alcanceMaximo > posicion)
        {
            posicion = alcanceMaximo;
        }
        else
        {
            // Necesitamos una mejora para desbloquear
            if (heap.vacio())
                return -1;

            poder += heap.maximo();
            heap.desencolar();
            mejorasUsadas++;
        }
    }

    return mejorasUsadas;
}
