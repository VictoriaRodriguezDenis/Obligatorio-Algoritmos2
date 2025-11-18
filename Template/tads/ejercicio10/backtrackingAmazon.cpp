#include <iostream>
using namespace std;

// Movimientos dinámicos (los 4 únicos permitidos)
int movFil[4] = {-1, 1, 0, 0};
int movCol[4] = {0, 0, -1, 1};

struct Pos
{
    int fil, col;
};

// Chequeo de límites dinámico
bool dentro(int f, int c, int filas, int cols)
{
    return f >= 0 && c >= 0 && f < filas && c < cols;
}

// ============================================================
// BFS desde el objetivo → distancias mínimas
// ============================================================
void calcularDistancias(char **mapa, int **dist, Pos objetivo, int F, int C)
{
    Pos *cola = new Pos[F * C];
    int ini = 0, fin = 0;

    for (int i = 0; i < F; i++)
        for (int j = 0; j < C; j++)
            dist[i][j] = -1;

    dist[objetivo.fil][objetivo.col] = 0;
    cola[fin++] = objetivo;

    while (ini < fin)
    {
        Pos act = cola[ini++];

        for (int k = 0; k < 4; k++)
        {
            int nf = act.fil + movFil[k];
            int nc = act.col + movCol[k];

            if (!dentro(nf, nc, F, C))
                continue;

            char celda = mapa[nf][nc];

            if ((celda == 'C' || celda == mapa[objetivo.fil][objetivo.col]) && dist[nf][nc] == -1)
            {
                dist[nf][nc] = dist[act.fil][act.col] + 1;
                cola[fin++] = {nf, nc};
            }
        }
    }

    delete[] cola;
}

// ============================================================
// Backtracking con poda A*
// ============================================================
void backtrack(int fil, int col, int pasos,
               char **mapa, int **dist, bool **visitado,
               Pos objetivo, int F, int C,
               int &mejor)
{
    if (mejor != -1 && pasos >= mejor)
        return;

    if (dist[fil][col] == -1)
        return;

    if (mejor != -1 && pasos + dist[fil][col] >= mejor)
        return;

    if (fil == objetivo.fil && col == objetivo.col)
    {
        if (mejor == -1 || pasos < mejor)
            mejor = pasos;
        return;
    }

    int orden[4] = {0, 1, 2, 3};

    // Ordenar movimientos según distancias
    for (int a = 0; a < 4; a++)
        for (int b = a + 1; b < 4; b++)
        {
            int f1 = fil + movFil[orden[a]];
            int c1 = col + movCol[orden[a]];
            int f2 = fil + movFil[orden[b]];
            int c2 = col + movCol[orden[b]];

            int d1 = dentro(f1, c1, F, C) ? dist[f1][c1] : 999999;
            int d2 = dentro(f2, c2, F, C) ? dist[f2][c2] : 999999;

            if (d1 > d2)
                swap(orden[a], orden[b]);
        }

    for (int t = 0; t < 4; t++)
    {
        int k = orden[t];
        int nf = fil + movFil[k];
        int nc = col + movCol[k];

        if (!dentro(nf, nc, F, C))
            continue;

        char celda = mapa[nf][nc];

        if (celda != 'C' && celda != mapa[objetivo.fil][objetivo.col])
            continue;

        if (!visitado[nf][nc])
        {
            visitado[nf][nc] = true;

            backtrack(nf, nc, pasos + 1,
                      mapa, dist, visitado,
                      objetivo, F, C,
                      mejor);

            visitado[nf][nc] = false;
        }
    }
}

// ============================================================
// Resolver un solo FC
// ============================================================
int resolverFC(char objetivo, char **mapa, int F, int C)
{
    Pos objetivoPos = {-1, -1};

    // Encontrar el producto
    for (int i = 0; i < F; i++)
        for (int j = 0; j < C; j++)
            if (mapa[i][j] == objetivo)
                objetivoPos = {i, j};

    // Crear tablas dinámicas
    int **dist = new int *[F];
    bool **visitado = new bool *[F];

    for (int i = 0; i < F; i++)
    {
        dist[i] = new int[C];
        visitado[i] = new bool[C];
    }

    calcularDistancias(mapa, dist, objetivoPos, F, C);

    if (dist[0][0] == -1)
    {
        for (int i = 0; i < F; i++)
        {
            delete[] dist[i];
            delete[] visitado[i];
        }
        delete[] dist;
        delete[] visitado;
        return -1;
    }

    for (int i = 0; i < F; i++)
        for (int j = 0; j < C; j++)
            visitado[i][j] = false;

    visitado[0][0] = true;

    int mejor = -1;

    backtrack(0, 0, 0,
              mapa, dist, visitado,
              objetivoPos,
              F, C, mejor);

    for (int i = 0; i < F; i++)
    {
        delete[] dist[i];
        delete[] visitado[i];
    }
    delete[] dist;
    delete[] visitado;

    return mejor;
}