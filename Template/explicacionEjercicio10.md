# 🧠 Ejercicio 10 – Búsqueda de Producto en Amazon

## 1. Introducción

Este ejercicio pide determinar en cuál de varios centros logísticos (FC) se encuentra un producto específico en la menor cantidad de pasos posibles, comenzando siempre desde la celda (0,0). El mapa de cada FC es una grilla donde las celdas pueden ser corredores ('C') o productos (otras letras). Solo se puede atravesar corredores, excepto si la celda contiene el producto buscado.

La solución se implementa con **backtracking** y varias **podas** para evitar recorridos innecesarios. Las funciones principales del desarrollo son:

- `celdaValida(...)`
- `backtrackBuscar(...)`
- `resolverCentro(...)`
- `main`

A continuación se detalla cómo funciona cada parte.

## 2. Explicación de la Solución

### 2.1 Recorrido general del algoritmo

Para cada FC:

1. Se lee su mapa.
2. Se valida que (0,0) sea una celda transitable.
3. Se inicializan:
   - `visitado[F][C]` para evitar ciclos.
   - `dist[F][C]` para registrar la menor cantidad de pasos con los que se llegó a cada celda.
4. Se ejecuta `backtrackBuscar(...)`, que explora caminos válidos y actualiza el mínimo de pasos para llegar al objetivo.
5. Se devuelve el mínimo encontrado.

Entre todos los FCs, el `main` elige el que obtuvo el menor número de pasos.

### 2.2 celdaValida

La función:

```cpp
bool celdaValida(char **mapa, bool **visitado, int F, int C,
                 int f, int c, char objetivo)
```

Verifica tres condiciones:

- Que la celda esté dentro del mapa.
- Que no haya sido visitada previamente.
- Que sea corredor (`'C'`) o sea el producto buscado.

Solo esas celdas pueden pisarse.

### 2.3 backtrackBuscar

```cpp
void backtrackBuscar(char **mapa, bool **visitado, int **dist,
                     int F, int C,
                     int f, int c,
                     int pasos,
                     char objetivo,
                     int &mejor)
```

Esta es la función más importante. Implementa un **backtracking con múltiples podas**:

1. **Caso base**: si la celda actual contiene el objetivo, actualiza `mejor`.
2. **Poda por suboptimalidad**: si `pasos >= mejor`, el camino no sirve.
3. **Poda por peor llegada previa**: si ya se llegó antes a esta celda con menos pasos (`dist[f][c] <= pasos`), tampoco tiene sentido seguir.
4. Se actualiza `dist[f][c] = pasos`.
5. Se exploran las 4 direcciones posibles recursivamente, marcando la celda como visitada antes de entrar y desmarcándola al salir.

Esto recorre solo caminos simples y evita bucles o caminos que ya quedaron descartados.

### 2.4 resolverCentro

```cpp
int resolverCentro(char objetivo, char **mapa, int F, int C)
```

Realiza la gestión completa para un FC:

- Verifica si (0,0) es transitable.
- Crea las matrices `visitado` y `dist`.
- Llama a `backtrackBuscar`.
- Libera memoria.
- Devuelve la cantidad mínima de pasos.

### 2.5 main

Procesa todos los centros logísticos:

- Lee el producto a buscar.
- Lee la cantidad de FCs.
- Por cada FC:
  - Carga el mapa.
  - Llama a `resolverCentro`.
- Imprime el índice del FC ganador y su cantidad de pasos.

## 3. Ejemplos ilustrativos

### Ejemplo 1 (simples pasillos)

```
C C C
C X C
C S C
```

- El producto es `S`.
- El camino óptimo baja por la columna izquierda.
- Resultado: 3 pasos.

### Ejemplo 2 (producto bloqueado salvo por un corredor estrecho)

```
C C P
X X C
C C S
```

El explorador prueba múltiples caminos, pero las podas evitan ramas inútiles.

### Ejemplo 3 (varios productos pero solo uno es el objetivo)

```
C A C B C
C C C C C
D C S C E
```

Se encuentra el producto `S` avanzando hacia abajo.

## 4. Complejidad

Aunque el backtracking puro sería teóricamente exponencial en el peor caso, las podas aplicadas reducen drásticamente la exploración real.

- **Peor caso teórico:** O(3^(F·C))  
  (cada celda puede continuar como máximo 3 movimientos sin volver)

- **Caso práctico:** cercano a O(F·C), porque:
  - Se evita repetir celdas con peor cantidad de pasos.
  - Se corta inmediatamente cuando se supera la mejor solución.
  - No se exploran caminos sin salida.

## 5. Declaración de Autoría

Este ejercicio fue desarrollado íntegramente por nuestro grupo. La estructura de poda y exploración está inspirada en técnicas vistas en clase, especialmente las aplicadas al recorrido del caballo en ajedrez, donde se optimiza la búsqueda para reducir drásticamente las ramas inválidas. Toda la implementación del algoritmo específico para los centros logísticos, así como la gestión completa de estructuras auxiliares y memoria, fue realizada por el grupo sin emplear código externo ni herramientas generativas.
