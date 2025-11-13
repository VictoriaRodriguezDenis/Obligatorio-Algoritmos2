#include <iostream>
using namespace std;

#define MAXF 60
#define MAXC 60

struct Punto
{
    int fila, col;
};

int df[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

bool dentro(int f, int c, int filas, int columnas)
{
    return f >= 0 && c >= 0 && f < filas && c < columnas;
}

void bfsMinimo(char mapa[MAXF][MAXC], int distancias[MAXF][MAXC],
               Punto meta, int filas, int columnas)
{
    int qf[MAXF * MAXC];
    int qc[MAXF * MAXC];
    int ini = 0, fin = 0;

    // reset distancias
    for (int f = 0; f < filas; f++)
        for (int c = 0; c < columnas; c++)
            distancias[f][c] = -1;

    distancias[meta.fila][meta.col] = 0;
    qf[fin] = meta.fila;
    qc[fin] = meta.col;
    fin++;

    while (ini < fin)
    {
        int f = qf[ini];
        int c = qc[ini];
        ini++;

        for (int k = 0; k < 4; k++)
        {
            int nf = f + df[k];
            int nc = c + dc[k];

            if (!dentro(nf, nc, filas, columnas))
                continue;

            char celda = mapa[nf][nc];

            if ((celda == 'C' || celda == mapa[meta.fila][meta.col]) &&
                distancias[nf][nc] == -1)
            {
                distancias[nf][nc] = distancias[f][c] + 1;
                qf[fin] = nf;
                qc[fin] = nc;
                fin++;
            }
        }
    }
}

bool btLimite(int f, int c,
              int limiteProf,
              char mapa[MAXF][MAXC],
              int distancias[MAXF][MAXC],
              bool camino[MAXF][MAXC],
              int pasos,
              Punto meta,
              int filas, int columnas)
{
    // poda heurística básica
    if (distancias[f][c] == -1)
        return false;

    if (pasos + distancias[f][c] > limiteProf)
        return false;

    // atajo
    if (f == meta.fila && c == meta.col)
        return true;

    if (distancias[f][c] == 1 && pasos + 1 <= limiteProf)
        return true;

    for (int k = 0; k < 4; k++)
    {
        int nf = f + df[k];
        int nc = c + dc[k];

        if (!dentro(nf, nc, filas, columnas))
            continue;

        char celda = mapa[nf][nc];
        if (celda != 'C' && celda != mapa[meta.fila][meta.col])
            continue;

        if (!camino[nf][nc])
        {
            camino[nf][nc] = true;

            if (btLimite(nf, nc, limiteProf,
                         mapa, distancias, camino,
                         pasos + 1, meta, filas, columnas))
                return true;

            camino[nf][nc] = false;
        }
    }

    return false;
}

int resolverCentro(char caracter, char mapa[MAXF][MAXC],
                   int filas, int columnas)
{
    Punto meta = {-1, -1};

    // buscar producto
    for (int f = 0; f < filas; f++)
        for (int c = 0; c < columnas; c++)
            if (mapa[f][c] == caracter)
                meta = {f, c};

    if (meta.fila == -1)
        return -1;

    int distancias[MAXF][MAXC];
    bfsMinimo(mapa, distancias, meta, filas, columnas);

    if (distancias[0][0] == -1)
        return -1;

    bool camino[MAXF][MAXC];
    for (int f = 0; f < filas; f++)
        for (int c = 0; c < columnas; c++)
            camino[f][c] = false;

    camino[0][0] = true;

    int minimo = distancias[0][0];

    // IDDFS más simple (no tan agresivo como antes)
    for (int limite = minimo; limite <= minimo + 150; limite++)
        if (btLimite(0, 0, limite, mapa, distancias, camino,
                     0, meta, filas, columnas))
            return limite;

    return -1;
}