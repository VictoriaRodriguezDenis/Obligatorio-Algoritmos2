/*using namespace std;
#include <iostream>


class Elemento {
    public:
        int tamano;   // tamaño del archivo (en 2D es peso)
        int lineas;   // cantidad de líneas del archivo (nueva restricción)
        int puntos;   // puntaje del ejercicio (en 2D es el valor)

        Elemento(int tamano, int lineas, int puntos) : tamano(tamano), lineas(lineas), puntos(puntos){}
};

void mochilaDP(Elemento** elementos, int cantElementos, int S, int L){
    // Matriz 3D: [elementos][tamaño+1][líneas+1]
    int*** matDP = new int**[cantElementos];
    for (int i = 0; i < cantElementos; i++) {
        matDP[i] = new int*[S+1];
        for (int j = 0; j <= S; j++) {
            matDP[i][j] = new int[L+1];
        }
    }
    
    // Inicializar todo en 0
    for (int i = 0; i < cantElementos; i++) {
        for (int j = 0; j <= S; j++) {
            for (int k = 0; k <= L; k++) {
                matDP[i][j][k] = 0;
            }
        }
    }
    
    // Primera "capa" (elemento 0)
    for (int j = 0; j <= S; j++) {
        for (int k = 0; k <= L; k++) {
            if (j >= elementos[0]->tamano && k >= elementos[0]->lineas) {
                matDP[0][j][k] = elementos[0]->puntos;
            }
        }
    }
    
    // El resto 
    for (int i = 1; i < cantElementos; i++) {
        for (int j = 0; j <= S; j++) {
            for (int k = 0; k <= L; k++) {
                // No incluir el elemento i
                matDP[i][j][k] = matDP[i-1][j][k];
                
                // Incluir el elemento i (si cabe)
                if (j >= elementos[i]->tamano && k >= elementos[i]->lineas) {
                    matDP[i][j][k] = max(matDP[i][j][k], elementos[i]->puntos + matDP[i-1][j - elementos[i]->tamano][k - elementos[i]->lineas]
                    );
                }
            }
        }
    }
    
    cout << matDP[cantElementos-1][S][L] << endl;
}*/

#include <iostream>
#include <algorithm>
using namespace std;

class Elemento {
public:
    int tamano;
    int lineas;
    int puntos;

    Elemento(int tamano, int lineas, int puntos)
        : tamano(tamano), lineas(lineas), puntos(puntos) {}
};

void mochilaDP(Elemento** elementos, int cantElementos, int S, int L) {

    // dp[i][j][k] = usare los primeros i elementos
    int*** dp = new int**[cantElementos + 1];

    for (int i = 0; i <= cantElementos; i++) {
        dp[i] = new int*[S + 1];
        for (int j = 0; j <= S; j++) {
            dp[i][j] = new int[L + 1];
            for (int k = 0; k <= L; k++) {
                dp[i][j][k] = 0;   // base: 0 elementos ⇒ todo en 0
            }
        }
    }

    for (int i = 1; i <= cantElementos; i++) {
        Elemento* e = elementos[i - 1];
        
        for (int j = 0; j <= S; j++) {
            for (int k = 0; k <= L; k++) {

                // No lo tomo
                dp[i][j][k] = dp[i - 1][j][k];

                // Lo tomo (si entra)
                if (j >= e->tamano && k >= e->lineas) {
                    dp[i][j][k] = max(
                        dp[i][j][k],
                        e->puntos + dp[i - 1][j - e->tamano][k - e->lineas]
                    );
                }
            }
        }
    }

    cout << dp[cantElementos][S][L] << endl;
}
