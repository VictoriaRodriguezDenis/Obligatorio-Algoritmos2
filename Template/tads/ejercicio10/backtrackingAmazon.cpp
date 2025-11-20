#include <iostream>
using namespace std;

// Movimientos permitidos
int movFil[4] = {1, -1, 0, 0};
int movCol[4] = {0, 0, 1, -1};

// Verifica si puedo moverme a la celda (f,c)
bool celdaValida(char **mapa, bool **visitado, int F, int C,
                 int f, int c, char objetivo)
{
    if (f < 0 || c < 0 || f >= F || c >= C)
        return false;

    if (visitado[f][c])
        return false;

    // Se puede pisar corredor o la celda del producto
    if (mapa[f][c] == 'C' || mapa[f][c] == objetivo)
        return true;

    return false;
}

// Backtracking
void backtrackBuscar(char **mapa, bool **visitado, int **dist,
                     int F, int C,
                     int f, int c,
                     int pasos,
                     char objetivo,
                     int &mejor)
{
    // Si ya encontré el objetivo
    if (mapa[f][c] == objetivo)
    {
        if (pasos < mejor)
            mejor = pasos;
        return;
    }

    // Si ya soy peor que el mejor → poda fuerte
    if (pasos >= mejor)
        return;

    // Si llegué a esta celda antes con menos pasos → no sirve seguir
    if (pasos >= dist[f][c])
        return;

    // Actualizo la mejor distancia con la que llegué a esta celda
    dist[f][c] = pasos;

    // Explorar vecinos
    for (int k = 0; k < 4; k++)
    {
        int nf = f + movFil[k];
        int nc = c + movCol[k];

        if (celdaValida(mapa, visitado, F, C, nf, nc, objetivo))
        {

            visitado[nf][nc] = true;

            backtrackBuscar(mapa, visitado, dist,
                            F, C,
                            nf, nc,
                            pasos + 1,
                            objetivo,
                            mejor);

            visitado[nf][nc] = false;
        }
    }
}

// Resolver un FC completo
int resolverFC(char objetivo, char **mapa, int F, int C)
{
    // Si la celda inicial no es transitable → imposible
    if (!(mapa[0][0] == 'C' || mapa[0][0] == objetivo))
        return 1000000000;

    // Tablas dinámicas
    bool **visitado = new bool *[F];
    int **dist = new int *[F];

    for (int i = 0; i < F; i++)
    {
        visitado[i] = new bool[C];
        dist[i] = new int[C];

        for (int j = 0; j < C; j++)
        {
            visitado[i][j] = false;
            dist[i][j] = 1000000000; // muy grande
        }
    }

    int mejor = 1000000000;

    visitado[0][0] = true;

    backtrackBuscar(mapa, visitado, dist,
                    F, C,
                    0, 0,
                    0,
                    objetivo,
                    mejor);

    // Liberar memoria
    for (int i = 0; i < F; i++)
    {
        delete[] visitado[i];
        delete[] dist[i];
    }
    delete[] visitado;
    delete[] dist;

    return mejor;
}
