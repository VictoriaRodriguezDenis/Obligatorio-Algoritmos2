#include <iostream>
#include "tads/ejercicio9/mochila3D.cpp"

using namespace std;

int main()
{
    int N;
    cin >> N;

    int S, L;
    cin >> S >> L;

    Elemento **elementos = new Elemento *[N];

    for (int i = 0; i < N; i++)
    {
        int t, ln, p;
        cin >> t >> ln >> p;
        elementos[i] = new Elemento(t, ln, p);
    }

    mochilaDP(elementos, N, S, L);

    // liberar memoria
    for (int i = 0; i < N; i++)
        delete elementos[i];
    delete[] elementos;

    return 0;
}
