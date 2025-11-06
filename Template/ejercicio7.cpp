#include <iostream>
#include <string>
#include "tads/ejercicio7/hashCerrado.cpp"
#include "tads/ejercicio7/ContadorInversiones.cpp"
using namespace std;

int main()
{

    int n;
    cin >> n;
    if (n <= 0 || n > MAXN)
        return 1;

    string *oficial = new string[n];
    string *ayudante = new string[n];
    int *indices = new int[n];

    HashCerrado hash(n * 2); // espacio adicional por colisiones

    for (int i = 0; i < n; i++)
    {
        cin >> oficial[i];
        hash.insertar(oficial[i], i);
    }

    for (int i = 0; i < n; i++)
    {
        cin >> ayudante[i];
        indices[i] = hash.buscar(ayudante[i]);
        if (indices[i] == -1)
            return 1;
    }

    cout << contarInversiones(indices, n) << "\n";

    delete[] oficial;
    delete[] ayudante;
    delete[] indices;
    return 0;
}
