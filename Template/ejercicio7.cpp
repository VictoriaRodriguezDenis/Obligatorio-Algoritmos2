#include <string>
#include <iostream>
#include "tads\ejercicio7\AVLRanking.cpp"
using namespace std;

int main() {
    // Optimización para entrada/salida rápida
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int cantidadEstudiantes;
    cin >> cantidadEstudiantes;

    // Arrays para guardar los rankings
    static string rankingOficial[MAX_ESTUDIANTES];
    static string rankingAyudante[MAX_ESTUDIANTES];
    static int posicionesNumericas[MAX_ESTUDIANTES];

    // Leer el ranking oficial (el correcto)
    for (int i = 0; i < cantidadEstudiantes; i++) {
        cin >> rankingOficial[i];
    }

    // Crear un mapa para búsqueda rápida O(log N) en lugar de O(N)
    map<string, int> mapaPos;
    for (int i = 0; i < cantidadEstudiantes; i++) {
        mapaPos[rankingOficial[i]] = i;
    }

    // Leer el ranking del ayudante y convertir directamente
    for (int i = 0; i < cantidadEstudiantes; i++) {
        cin >> rankingAyudante[i];
        posicionesNumericas[i] = mapaPos[rankingAyudante[i]];
    }

    // Ahora contamos cuántas inversiones hay
    // Una inversión = un par que está en orden distinto
    long long totalInversiones = contarInversiones(posicionesNumericas, 
                                                    cantidadEstudiantes);

    cout << totalInversiones << endl;

    return 0;
}