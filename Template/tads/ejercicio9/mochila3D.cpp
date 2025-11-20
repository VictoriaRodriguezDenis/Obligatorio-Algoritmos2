#include <iostream>
using namespace std;

class Elemento
{
public:
    int tamano; // tamaño del archivo (MB)
    int lineas; // cant. líneas del archivo
    int puntos; // puntaje del ejercicio

    Elemento(int t, int l, int p) : tamano(t), lineas(l), puntos(p) {}
};

// -------------------------------------------------------
//  max propio (sin <algorithm>)
// -------------------------------------------------------
int miMax(int a, int b)
{
    return (a > b ? a : b);
}

// -------------------------------------------------------
//  DP 3D — Tabulación O(N * S * L)
// -------------------------------------------------------
void mochilaDP(Elemento **elementos, int N, int S, int L)
{
    // dp[i][j][k] → usando los primeros i elementos,
    // con j MB y k líneas → máximo puntaje
    int ***dp = new int **[N + 1];

    for (int i = 0; i <= N; i++)
    {
        dp[i] = new int *[S + 1];
        for (int j = 0; j <= S; j++)
        {
            dp[i][j] = new int[L + 1];

            for (int k = 0; k <= L; k++)
                dp[i][j][k] = 0; // caso base: 0 puntos
        }
    }

    // ---------------------------------------------------
    // Tabulación: vamos cargando dp fila por fila
    // ---------------------------------------------------
    for (int i = 1; i <= N; i++)
    {

        int t = elementos[i - 1]->tamano;
        int ln = elementos[i - 1]->lineas;
        int p = elementos[i - 1]->puntos;

        for (int j = 0; j <= S; j++)
        {
            for (int k = 0; k <= L; k++)
            {

                // NO tomar el elemento i
                dp[i][j][k] = dp[i - 1][j][k];

                // Tomarlo (si entra)
                if (j >= t && k >= ln)
                {
                    int candidato = p + dp[i - 1][j - t][k - ln];
                    dp[i][j][k] = miMax(dp[i][j][k], candidato);
                }
            }
        }
    }

    // ---------------------------------------------------
    // Resultado final
    // ---------------------------------------------------
    cout << dp[N][S][L] << endl;

    // ---------------------------------------------------
    // Liberar memoria
    // ---------------------------------------------------
    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j <= S; j++)
            delete[] dp[i][j];
        delete[] dp[i];
    }
    delete[] dp;
}