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

int resolverSkate(Pozo pozos[], int cantPozos,
                  Mejora mejoras[], int cantMejoras,
                  int destino)
{
    int posicion = 1;
    int poder = 1;
    int mejorasUsadas = 0;
    int indicePozo = 0;   // pozos que ya quedaron atrás
    int indiceMejora = 0; // mejoras aún no procesadas

    HeapMax *mejorasDisponibles = new HeapMax(cantMejoras);

    while (posicion < destino)
    {
        // Descartar pozos totalmente a la izquierda
        while (indicePozo < cantPozos && pozos[indicePozo].fin < posicion)
            indicePozo++;

        int alcance = posicion + poder;

        // Si ya puedo llegar con el poder actual
        if (alcance >= destino)
        {
            delete mejorasDisponibles;
            return mejorasUsadas;
        }

        // Agregar mejoras dentro del alcance
        while (indiceMejora < cantMejoras &&
               mejoras[indiceMejora].posicion <= alcance)
        {
            mejorasDisponibles->encolar(mejoras[indiceMejora].aumento);
            indiceMejora++;
        }

        // Buscar si el pozo relevante bloquea el salto
        int j = indicePozo;
        // avanzar hasta encontrar un pozo que pueda afectar el alcance
        while (j < cantPozos && pozos[j].fin < alcance)
            j++;

        // ¿El salto cae dentro del pozo j?
        if (j < cantPozos &&
            pozos[j].inicio <= alcance &&
            pozos[j].inicio > posicion)
        {
            alcance = pozos[j].inicio - 1;
        }

        // Si puedo avanzar, avanzo
        if (alcance > posicion)
        {
            posicion = alcance;
        }
        else
        {
            // Me quedé sin poder para avanzar, necesito mejora
            if (mejorasDisponibles->estaVacio())
            {
                delete mejorasDisponibles;
                return -1; // imposible llegar
            }

            poder += mejorasDisponibles->obtenerMaximo();
            mejorasDisponibles->desencolar();
            mejorasUsadas++;
        }
    }

    delete mejorasDisponibles;
    return mejorasUsadas;
}
