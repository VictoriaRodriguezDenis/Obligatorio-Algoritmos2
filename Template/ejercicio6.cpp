#include <string>
#include <iostream>
#include "tads\ejercicio6\skate.cpp"
using namespace std;

int main()
{
    int N, M, F;
    cin >> N >> M >> F;

    Pozo pozos[MAXN];
    for (int i = 0; i < N; i++)
        cin >> pozos[i].inicio >> pozos[i].fin;

    Mejora mejoras[MAXN];
    for (int i = 0; i < M; i++)
        cin >> mejoras[i].posicion >> mejoras[i].aumento;

    int resultado = resolverSkate(pozos, N, mejoras, M, F);

    if (resultado == -1)
        cout << "Imposible" << endl;
    else
        cout << resultado << endl;

    return 0;
}
