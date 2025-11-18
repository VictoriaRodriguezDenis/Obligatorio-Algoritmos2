#include <string>
#include <iostream>
#include "tads/ejercicio8/dpCristales3D.cpp"
using namespace std;

int main()
{
    int N;
    cin >> N;

    colores = new int[N];
    for (int i = 0; i < N; i++)
        cin >> colores[i];

    // crear dpMemo dinámicamente como dp[N][N][N]
    dpMemo = new long long **[N];
    for (int i = 0; i < N; i++)
    {
        dpMemo[i] = new long long *[N];
        for (int j = 0; j < N; j++)
        {
            dpMemo[i][j] = new long long[N];
            for (int k = 0; k < N; k++)
                dpMemo[i][j][k] = -1;
        }
    }

    long long ans = calcMemo(0, N - 1, 0, N);
    cout << ans << "\n";

    // liberar memoria
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            delete[] dpMemo[i][j];
        delete[] dpMemo[i];
    }
    delete[] dpMemo;

    delete[] colores;

    return 0;
}
