#include <iostream>
#include "tads/ejercicio8/dpCristales3D.cpp"
using namespace std;

int main()
{
    int N;
    cin >> N;

    int *colores = new int[N];
    for (int i = 0; i < N; i++)
        cin >> colores[i];

    int ***dpMemo = new int **[N];

    for (int i = 0; i < N; i++)
    {
        dpMemo[i] = new int *[N];
        for (int j = 0; j < N; j++)
        {
            dpMemo[i][j] = new int[N];
            for (int k = 0; k < N; k++)
                dpMemo[i][j][k] = -1;
        }
    }

    int ans = calcMemo(0, N - 1, 0, colores, dpMemo);
    cout << ans << "\n";

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
