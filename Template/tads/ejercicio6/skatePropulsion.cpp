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
            return;
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

int resolverSkate(Pozo pozos[], int cantPozos, Mejora mejoras[], int cantMejoras, int destino)
{
    int posicion = 1;
    int poder = 1;
    int mejorasUsadas = 0;
    int indicePozo = 0;
    int indiceMejora = 0;

    // apuntador para el pozo relevante respecto al alcance
    int indicePozoAlcance = 0;

    HeapMax *mejorasDisponibles = new HeapMax(cantMejoras);

    while (posicion < destino)
    {
        // avanzar pozos que quedan totalmente a la izquierda de la posición actual
        while (indicePozo < cantPozos && pozos[indicePozo].fin < posicion)
            indicePozo++;

        int alcance = posicion + poder;

        // si con el poder actual ya llego o paso el destino, listo
        if (alcance >= destino)
        {
            delete mejorasDisponibles;
            return mejorasUsadas;
        }

        // agregar todas las mejoras que estén en casas alcanzables
        while (indiceMejora < cantMejoras && mejoras[indiceMejora].posicion <= alcance)
        {
            mejorasDisponibles->encolar(mejoras[indiceMejora].aumento);
            indiceMejora++;
        }

        // ajustar el índice de pozo para no mirar pozos que ya quedaron atrás de la posición
        if (indicePozoAlcance < indicePozo)
            indicePozoAlcance = indicePozo;

        // avanzar el índice de pozo según el alcance:
        // buscamos el primer pozo cuyo fin sea >= alcance
        while (indicePozoAlcance < cantPozos && pozos[indicePozoAlcance].fin < alcance)
            indicePozoAlcance++;

        // si el alcance cae dentro de ese pozo, recorto el salto a la casa anterior al pozo
        if (indicePozoAlcance < cantPozos &&
            pozos[indicePozoAlcance].inicio <= alcance &&
            pozos[indicePozoAlcance].inicio > posicion)
        {
            alcance = pozos[indicePozoAlcance].inicio - 1;
        }

        // si puedo avanzar, avanzo
        if (alcance > posicion)
        {
            posicion = alcance;
        }
        else
        {
            // no puedo avanzar sin pedir mejoras
            if (mejorasDisponibles->estaVacio())
            {
                delete mejorasDisponibles;
                return -1;
            }
            poder += mejorasDisponibles->obtenerMaximo();
            mejorasDisponibles->desencolar();
            mejorasUsadas++;
        }
    }

    delete mejorasDisponibles;
    return mejorasUsadas;
}
