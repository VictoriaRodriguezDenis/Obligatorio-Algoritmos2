#include <iostream>
using namespace std;

/*
    BFS + IDDFS Backtracking hiper-optimizado.
    - BFS manual sin STL
    - Backtracking con poda A*
    - Iterative Deepening para cortar ramas eternas
    - Orden dinámico de movimientos según BFS
    - Atajo dist=1
*/

struct Punto
{
    int i, j;
};

int gi[4] = {-1, 1, 0, 0};
int gj[4] = {0, 0, -1, 1};

bool esValido(int i, int j, int M, int N)
{
    return i >= 0 && j >= 0 && i < M && j < N;
}

/* ===========================================================
   BFS MANUAL (sin STL)
   =========================================================== */
void bfsDistancias(char mapa[55][55], int dist[55][55],
                   Punto objetivo, int M, int N)
{
    // Cola manual
    Punto cola[3500];
    int ini = 0, fin = 0;

    // Reset distancias
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            dist[i][j] = -1;

    dist[objetivo.i][objetivo.j] = 0;
    cola[fin++] = objetivo;

    while (ini < fin)
    {
        Punto p = cola[ini++];

        for (int k = 0; k < 4; k++)
        {
            int ni = p.i + gi[k];
            int nj = p.j + gj[k];

            if (!esValido(ni, nj, M, N))
                continue;

            char c = mapa[ni][nj];
            if ((c == 'C' || c == mapa[objetivo.i][objetivo.j]) &&
                dist[ni][nj] == -1)
            {
                dist[ni][nj] = dist[p.i][p.j] + 1;
                cola[fin++] = {ni, nj};
            }
        }
    }
}

/* ===========================================================
   BACKTRACKING CON PODAS + IDDFS
   =========================================================== */
bool btDepthLimit(int i, int j,
                  int depthLimit,
                  char mapa[55][55],
                  int dist[55][55],
                  bool visit[55][55],
                  int pasosActual,
                  Punto objetivo,
                  int M, int N)
{
    // A* pruning
    if (pasosActual + dist[i][j] > depthLimit)
        return false;

    // dist -1 no tiene camino
    if (dist[i][j] == -1)
        return false;

    // si estoy a 1 paso → corto y gano
    if (dist[i][j] == 1 && pasosActual + 1 <= depthLimit)
        return true;

    // ¿Objetivo?
    if (i == objetivo.i && j == objetivo.j)
        return true;

    // Orden dinámico de movimientos: probar primero los más cerca según BFS
    int ord[4] = {0, 1, 2, 3};
    for (int a = 0; a < 4; a++)
        for (int b = a + 1; b < 4; b++)
            if (dist[i + gi[ord[b]]][j + gj[ord[b]]] <
                dist[i + gi[ord[a]]][j + gj[ord[a]]])
            {
                int t = ord[a];
                ord[a] = ord[b];
                ord[b] = t;
            }

    for (int z = 0; z < 4; z++)
    {
        int k = ord[z];
        int ni = i + gi[k];
        int nj = j + gj[k];

        if (!esValido(ni, nj, M, N))
            continue;

        char c = mapa[ni][nj];
        if (c != 'C' && c != mapa[objetivo.i][objetivo.j])
            continue;

        if (!visit[ni][nj])
        {
            visit[ni][nj] = true;

            if (btDepthLimit(ni, nj, depthLimit,
                             mapa, dist, visit, pasosActual + 1,
                             objetivo, M, N))
                return true;

            visit[ni][nj] = false;
        }
    }
    return false;
}

/* ===========================================================
   RESOLVER UN MAPA COMPLETO (IDDFS)
   =========================================================== */
int resolverFC(char buscado, char mapa[55][55], int M, int N)
{
    Punto objetivo = {-1, -1};

    // Buscar objetivo
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            if (mapa[i][j] == buscado)
                objetivo = {i, j};

    if (objetivo.i == -1)
        return -1;

    // BFS mínima
    int dist[55][55];
    bfsDistancias(mapa, dist, objetivo, M, N);

    if (dist[0][0] == -1)
        return -1; // imposible

    // IDDFS
    bool visit[55][55];
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            visit[i][j] = false;

    visit[0][0] = true;

    // límite inferior = BFS
    int minimo = dist[0][0];

    // límite superior = BFS + 200 por seguridad
    for (int limite = minimo; limite <= minimo + 200; limite++)
    {
        if (btDepthLimit(0, 0, limite, mapa, dist, visit, 0, objetivo, M, N))
            return limite;
    }

    return -1;
}
