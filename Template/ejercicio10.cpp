#include <iostream>
#include "tads/ejercicio10/backtrackingAmazon.cpp"
using namespace std;

int main()
{
    char producto;
    cin >> producto;

    int P;
    cin >> P;

    int mejorCentro = -1;
    int mejorPasos = -1;

    for (int idx = 1; idx <= P; idx++)
    {
        int F, C;
        cin >> F >> C;

        char **mapa = new char *[F];
        for (int i = 0; i < F; i++)
            mapa[i] = new char[C];

        for (int i = 0; i < F; i++)
            for (int j = 0; j < C; j++)
                cin >> mapa[i][j];

        int pasos = resolverFC(producto, mapa, F, C);

        if (pasos != -1 &&
            (mejorPasos == -1 || pasos < mejorPasos))
        {
            mejorPasos = pasos;
            mejorCentro = idx;
        }

        for (int i = 0; i < F; i++)
            delete[] mapa[i];
        delete[] mapa;
    }

    cout << mejorCentro << " " << mejorPasos;

    return 0;
}
