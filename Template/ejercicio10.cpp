#include <string>
#include <iostream>
#include "tads/ejercicio10/backtracking.cpp"

using namespace std;

int main()
{
    char buscado;
    cin >> buscado;

    int P;
    cin >> P;

    int mejorIndice = -1;
    int mejorPasos = -1;

    for (int k = 1; k <= P; k++)
    {

        int M, N;
        cin >> M >> N;

        char mapa[55][55];
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                cin >> mapa[i][j];

        int pasos = resolverFC(buscado, mapa, M, N);

        if (pasos != -1)
        {
            if (mejorPasos == -1 || pasos < mejorPasos)
            {
                mejorPasos = pasos;
                mejorIndice = k;
            }
        }
    }

    cout << mejorIndice << " " << mejorPasos << endl;
    return 0;
}
