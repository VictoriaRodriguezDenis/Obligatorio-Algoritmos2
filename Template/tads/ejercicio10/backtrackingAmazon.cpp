#include <iostream>
using namespace std;

#define MAXF 60
#define MAXC 60

struct Punto
{
    int f, c;
};

int df[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

bool dentro(int f, int c, int F, int C)
{
    return f >= 0 && c >= 0 && f < F && c < C;
}

// =====================================================
// Preprocesamiento mínimo (distancias desde la meta)
// =====================================================
void calcularDist(char mapa[MAXF][MAXC],
                  int dist[MAXF][MAXC],
                  Punto meta, int F, int C)
{
    int qf[MAXF * MAXC], qc[MAXF * MAXC];
    int ini = 0, fin = 0;

    for (int i = 0; i < F; i++)
        for (int j = 0; j < C; j++)
            dist[i][j] = -1;

    dist[meta.f][meta.c] = 0;
    qf[fin] = meta.f;
    qc[fin] = meta.c;
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

            if (!dentro(nf, nc, F, C))
                continue;

            char cel = mapa[nf][nc];

            if ((cel == 'C' || cel == mapa[meta.f][meta.c]) &&
                dist[nf][nc] == -1)
            {
                dist[nf][nc] = dist[f][c] + 1;
                qf[fin] = nf;
                qc[fin] = nc;
                fin++;
            }
        }
    }
}

// =====================================================
//      BACKTRACKING ESTILO CABALLO (BT puro)
// =====================================================
bool BT(int f, int c,
        int pasos, int limite,
        char mapa[MAXF][MAXC],
        int dist[MAXF][MAXC],
        bool visit[MAXF][MAXC],
        Punto meta, int F, int C)
{
    // ¿Llegó?
    if (f == meta.f && c == meta.c)
        return true;

    // podas suaves y simples
    if (dist[f][c] == -1)
        return false;
    if (pasos + dist[f][c] > limite)
        return false;

    // probar 4 movimientos como el caballo prueba 8
    for (int k = 0; k < 4; k++)
    {
        int nf = f + df[k];
        int nc = c + dc[k];

        if (!dentro(nf, nc, F, C))
            continue;

        char cel = mapa[nf][nc];

        if (cel != 'C' && cel != mapa[meta.f][meta.c])
            continue;

        if (!visit[nf][nc])
        {
            visit[nf][nc] = true;

            if (BT(nf, nc, pasos + 1, limite,
                   mapa, dist, visit,
                   meta, F, C))
                return true;

            visit[nf][nc] = false;
        }
    }

    return false;
}

// =====================================================
//                 RESOLVER UN CENTRO
// =====================================================
int resolverCentro(char objetivo,
                   char mapa[MAXF][MAXC],
                   int F, int C)
{
    // buscar meta
    Punto meta{-1, -1};
    for (int f = 0; f < F; f++)
        for (int c = 0; c < C; c++)
            if (mapa[f][c] == objetivo)
                meta = {f, c};

    if (meta.f == -1)
        return -1;

    int dist[MAXF][MAXC];
    calcularDist(mapa, dist, meta, F, C);

    if (dist[0][0] == -1)
        return -1;

    bool visit[MAXF][MAXC];
    for (int f = 0; f < F; f++)
        for (int c = 0; c < C; c++)
            visit[f][c] = false;

    visit[0][0] = true;

    int limite = dist[0][0] + 20; // margen fijo simple

    if (BT(0, 0, 0, limite, mapa, dist, visit, meta, F, C))
        return limite;

    return -1;
}
