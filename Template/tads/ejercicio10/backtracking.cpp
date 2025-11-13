#include <iostream>
using namespace std;

/*
    BFS + Backtracking SIN STL
    Todo hecho a mano: cola propia, matrices estáticas, podas fuertes.
*/

struct Punto
{
    int i, j;
};

bool esValido(int i, int j, int M, int N)
{
    return i >= 0 && j >= 0 && i < M && j < N;
}

/* ===========================================================
   BFS MANUAL → Llenar distancias mínimas al objetivo
   =========================================================== */
void bfsDistancias(char mapa[55][55], int dist[55][55],
                   Punto objetivo, int M, int N)
{
    // Cola manual
    Punto cola[3000];
    int ini = 0, fin = 0;

    // Inicializo distancias
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            dist[i][j] = -1;

    dist[objetivo.i][objetivo.j] = 0;
    cola[fin++] = objetivo;

    int di[4] = {-1, 1, 0, 0};
    int dj[4] = {0, 0, -1, 1};

    while (ini < fin)
    {
        Punto p = cola[ini++];
        for (int k = 0; k < 4; k++)
        {
            int ni = p.i + di[k];
            int nj = p.j + dj[k];

            if (esValido(ni, nj, M, N))
            {
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
}

/* ===========================================================
   BACKTRACKING + PODAS
   =========================================================== */
void bt(int i, int j,
        char mapa[55][55],
        int dist[55][55],
        bool visit[55][55],
        int pasosActual,
        int &mejorSol,
        Punto objetivo,
        int M, int N)
{
    // poda 1: ya peor que una solución existente
    if (mejorSol != -1 && pasosActual >= mejorSol)
        return;

    // poda 2: BFS indica que no existe camino desde aquí
    if (dist[i][j] == -1)
        return;

    // poda 3: heurística exacta → pasosActual + dist > mejorSol
    if (mejorSol != -1 && pasosActual + dist[i][j] > mejorSol)
        return;

    // ¿Llegué?
    if (i == objetivo.i && j == objetivo.j)
    {
        if (mejorSol == -1 || pasosActual < mejorSol)
            mejorSol = pasosActual;
        return;
    }

    int di[4] = {-1, 1, 0, 0};
    int dj[4] = {0, 0, -1, 1};

    for (int k = 0; k < 4; k++)
    {
        int ni = i + di[k];
        int nj = j + dj[k];

        if (!esValido(ni, nj, M, N))
            continue;

        char c = mapa[ni][nj];

        if (c != 'C' && c != mapa[objetivo.i][objetivo.j])
            continue;

        if (!visit[ni][nj])
        {
            visit[ni][nj] = true;
            bt(ni, nj, mapa, dist, visit, pasosActual + 1,
               mejorSol, objetivo, M, N);
            visit[ni][nj] = false;
        }
    }
}

/* ===========================================================
   RESOLVER UN FC COMPLETO
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

    // BFS manual de distancias
    int dist[55][55];
    bfsDistancias(mapa, dist, objetivo, M, N);

    // Si no existe camino desde 0,0 → descartar
    if (dist[0][0] == -1)
        return -1;

    // Backtracking
    bool visit[55][55];
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            visit[i][j] = false;

    int mejorSol = -1;
    visit[0][0] = true;

    bt(0, 0, mapa, dist, visit, 0, mejorSol, objetivo, M, N);

    return mejorSol;
}
