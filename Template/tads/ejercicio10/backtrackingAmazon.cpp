#include <iostream>
using namespace std;

#define MAXF 60
#define MAXC 60

// Representa una posición dentro del mapa (fila, columna)
struct Pos
{
    int fil, col;
};

// Movimientos permitidos: arriba, abajo, izquierda, derecha
int movFil[4] = {-1, 1, 0, 0};
int movCol[4] = {0, 0, -1, 1};

// Verifica límites del mapa
bool dentro(int f, int c, int cantFilas, int cantCols)
{
    return f >= 0 && c >= 0 && f < cantFilas && c < cantCols;
}

/* ============================================================
   BFS desde la posición del producto buscado.
   dist[f][c] guarda la distancia mínima desde (f,c) al objetivo.
   Si dist[f][c] = -1 → esa celda NO puede alcanzar el producto.

   Esto permite podas muy agresivas en el backtracking.
   ============================================================ */
void calcularDistancias(char **mapa,
                        int **dist,
                        Pos objetivoPos,
                        int cantFilas, int cantCols)
{
    Pos *cola = new Pos[cantFilas * cantCols]; // cola lineal manual
    int ini = 0, fin = 0;                      // índices de la cola

    // Inicializamos distancias como desconocidas
    for (int f = 0; f < cantFilas; f++)
        for (int c = 0; c < cantCols; c++)
            dist[f][c] = -1;

    dist[objetivoPos.fil][objetivoPos.col] = 0; // el objetivo está a distancia 0 de sí mismo
    cola[fin++] = objetivoPos;                  // encolar inicio del BFS

    // BFS estándar usando cola manual
    while (ini < fin)
    {
        Pos actual = cola[ini++];

        for (int k = 0; k < 4; k++)
        {
            int filDestino = actual.fil + movFil[k];
            int colDestino = actual.col + movCol[k];

            if (!dentro(filDestino, colDestino, cantFilas, cantCols))
                continue;

            char celda = mapa[filDestino][colDestino];

            // Sólo propagamos por corredores 'C' o por la celda del objetivo
            if ((celda == 'C' || celda == mapa[objetivoPos.fil][objetivoPos.col]) &&
                dist[filDestino][colDestino] == -1)
            {
                dist[filDestino][colDestino] = dist[actual.fil][actual.col] + 1;

                // Encolamos la celda recién alcanzada
                Pos siguiente = {filDestino, colDestino};
                cola[fin++] = siguiente;
            }
        }
    }

    delete[] cola;
}

/* ============================================================
   BACKTRACKING que explora todos los caminos posibles, con podas
   basadas en el BFS previo:
   - si dist == -1 → nunca se llega al objetivo desde ahí
   - si pasos >= mejor → ya es peor que lo encontrado
   - si pasos + dist >= mejor → aunque sigamos, será peor

   Los movimientos también se ordenan según la distancia BFS
   para explorar primero lo más prometedor.
   ============================================================ */
void buscarBT(int filActual, int colActual,
              int pasos,
              char **mapa,
              int **dist,
              bool **visitado,
              Pos objetivoPos,
              int cantFilas, int cantCols,
              int &mejor)
{
    // Si ya encontramos una mejor solución, no seguir por aquí
    if (mejor != -1 && pasos >= mejor)
        return;

    // Esta celda jamás podrá llegar al objetivo
    if (dist[filActual][colActual] == -1)
        return;

    // Aunque sigamos por el mejor camino posible, no superamos
    if (mejor != -1 && pasos + dist[filActual][colActual] >= mejor)
        return;

    // Caso base: llegamos al producto
    if (filActual == objetivoPos.fil && colActual == objetivoPos.col)
    {
        if (mejor == -1 || pasos < mejor)
            mejor = pasos;
        return;
    }

    // Ordenamiento de los 4 movimientos según lo cerca que estén del objetivo
    int orden[4] = {0, 1, 2, 3};

    for (int a = 0; a < 4; a++)
        for (int b = a + 1; b < 4; b++)
        {
            int f1 = filActual + movFil[orden[a]];
            int c1 = colActual + movCol[orden[a]];
            int f2 = filActual + movFil[orden[b]];
            int c2 = colActual + movCol[orden[b]];

            int dist1 = 9999;
            if (dentro(f1, c1, cantFilas, cantCols))
                dist1 = dist[f1][c1];

            int dist2 = 9999;
            if (dentro(f2, c2, cantFilas, cantCols))
                dist2 = dist[f2][c2];

            // Si el movimiento b tiene mejor distancia, intercambiamos
            if (dist1 > dist2)
            {
                int aux = orden[a];
                orden[a] = orden[b];
                orden[b] = aux;
            }
        }

    // Intentar los movimientos en el orden elegido
    for (int t = 0; t < 4; t++)
    {
        int k = orden[t];

        int filSig = filActual + movFil[k];
        int colSig = colActual + movCol[k];

        if (!dentro(filSig, colSig, cantFilas, cantCols))
            continue;

        char celda = mapa[filSig][colSig];

        // Sólo podemos pisar corredores o la celda final con el producto
        if (celda != 'C' && celda != mapa[objetivoPos.fil][objetivoPos.col])
            continue;

        // Evitar ciclos
        if (!visitado[filSig][colSig])
        {
            visitado[filSig][colSig] = true;

            // Continuar recursión
            buscarBT(filSig, colSig, pasos + 1,
                     mapa, dist, visitado,
                     objetivoPos,
                     cantFilas, cantCols,
                     mejor);

            visitado[filSig][colSig] = false; // backtrack
        }
    }
}

/* ============================================================
   FUNCIÓN PRINCIPAL QUE RESUELVE UN SOLO FC
   Devuelve:
   - menor número de pasos desde (0,0) hasta el objetivo
   - -1 si no es posible llegar
   ============================================================ */
int buscarProducto(char objetivo,
                   char **mapa,
                   int cantFilas, int cantCols)
{
    // Buscar la posición exacta del producto
    Pos objetivoPos = {-1, -1};

    for (int f = 0; f < cantFilas; f++)
        for (int c = 0; c < cantCols; c++)
            if (mapa[f][c] == objetivo)
                objetivoPos = {f, c};

    // Reservar matrices dinámicas
    int **dist = new int *[cantFilas];
    bool **visitado = new bool *[cantFilas];

    for (int i = 0; i < cantFilas; i++)
    {
        dist[i] = new int[cantCols];
        visitado[i] = new bool[cantCols];
    }

    // Precalcular distancia mínima de cada celda al objetivo
    calcularDistancias(mapa, dist, objetivoPos, cantFilas, cantCols);

    // Si desde (0,0) no hay forma de llegar al producto
    if (dist[0][0] == -1)
        return -1;

    // Inicializar visitado
    for (int f = 0; f < cantFilas; f++)
        for (int c = 0; c < cantCols; c++)
            visitado[f][c] = false;

    visitado[0][0] = true; // arrancamos desde la entrada

    // Backtracking
    int mejor = -1;

    buscarBT(0, 0, 0,
             mapa, dist, visitado,
             objetivoPos,
             cantFilas, cantCols,
             mejor);

    return mejor;
}
