#include <iostream>
using namespace std;

struct Pozo
{
    int inicio;
    int fin;
};

struct Mejora
{
    int posicion;
    int aumento;
};

// --- TAD Heap Máximo (implementación sin vector ni MAXN) ---
class HeapMax
{
private:
    int *elementos;
    int cantidad;
    int capacidad;

    void flotar(int i)
    {
        while (i > 1 && elementos[i] > elementos[i / 2])
        {
            swap(elementos[i], elementos[i / 2]);
            i /= 2;
        }
    }

    void hundir(int i)
    {
        while (2 * i <= cantidad)
        {
            int hijoMayor = 2 * i;
            if (hijoMayor < cantidad && elementos[hijoMayor + 1] > elementos[hijoMayor])
                hijoMayor++;
            if (elementos[i] >= elementos[hijoMayor])
                break;
            swap(elementos[i], elementos[hijoMayor]);
            i = hijoMayor;
        }
    }

public:
    HeapMax(int maxElementos)
    {
        capacidad = maxElementos + 5;
        elementos = new int[capacidad];
        cantidad = 0;
    }

    ~HeapMax()
    {
        delete[] elementos;
    }

    bool estaVacio()
    {
        return cantidad == 0;
    }

    void encolar(int valor)
    {
        if (cantidad + 1 >= capacidad)
            return; // protección por seguridad
        elementos[++cantidad] = valor;
        flotar(cantidad);
    }

    int obtenerMaximo()
    {
        return elementos[1];
    }

    void desencolar()
    {
        if (cantidad == 0)
            return;
        elementos[1] = elementos[cantidad--];
        hundir(1);
    }
};

// --- Lógica principal del problema ---
int resolverSkate(Pozo pozos[], int cantPozos, Mejora mejoras[], int cantMejoras, int destino)
{
    int posicion = 1;
    int poder = 1;
    int mejorasUsadas = 0;
    int indicePozo = 0;
    int indiceMejora = 0;

    HeapMax mejorasDisponibles(cantMejoras);

    while (posicion < destino)
    {
        // Ignorar pozos que ya pasamos
        while (indicePozo < cantPozos && pozos[indicePozo].fin < posicion)
            indicePozo++;

        int alcance = posicion + poder;

        // Si ya llegamos
        if (alcance >= destino)
            return mejorasUsadas;

        // Agregar mejoras alcanzables
        while (indiceMejora < cantMejoras && mejoras[indiceMejora].posicion <= alcance)
        {
            mejorasDisponibles.encolar(mejoras[indiceMejora].aumento);
            indiceMejora++;
        }

        // Ajustar alcance si hay pozo bloqueando
        if (indicePozo < cantPozos &&
            pozos[indicePozo].inicio <= alcance &&
            pozos[indicePozo].inicio > posicion)
        {
            if (pozos[indicePozo].fin >= alcance)
                alcance = pozos[indicePozo].inicio - 1;
        }

        // Si podemos avanzar sin pedir ayuda
        if (alcance > posicion)
        {
            posicion = alcance;
        }
        else
        {
            // Si no podemos avanzar, pedimos una mejora
            if (mejorasDisponibles.estaVacio())
                return -1;
            poder += mejorasDisponibles.obtenerMaximo();
            mejorasDisponibles.desencolar();
            mejorasUsadas++;
        }
    }

    return mejorasUsadas;
}
