# Ejercicio 6 -- Skate a Propulsión (explicación profunda)

## 0. Qué vamos a hacer

En este archivo te explico:

1.  **El problema con palabras simples**
2.  **La idea intuitiva del greedy** (por qué funciona y qué está
    "optimizando")
3.  **Cómo se integra el tema de los pozos**
4.  **Paso a paso del algoritmo que implementa tu código**
5.  **Explicación del `HeapMax` y por qué lo usamos**
6.  **Lectura detallada de `resolverSkate` línea por línea (a nivel
    idea)**
7.  **Complejidad y por qué cumple lo que pide el enunciado**

## 1. Re-explicando el problema desde cero

Tenemos una ciudad con casas numeradas:

```text
1, 2, 3, 4, 5, 6, 7, ... , F
```

Mike empieza en la casa 1.

Su amigo vive en la casa F (destino).

Hay tramos con pozos donde no puede pararse (no puede ni arrancar ni
terminar un salto dentro del pozo).\
Esos tramos se dan como intervalos `[I_i, D_i]`.

Ejemplo:

```text
casas:   1   2   3   4   5   6   7
calle:   M   -   #   #   -   -   -
          ^   ^   ^   ^
       Mike  bien pozo
```

Además hay vecinos que ofrecen mejoras de potencia.

Cada mejora se da en una casa `X_i` con un aumento de potencia `P_i`.

Nunca hay una mejora en una casa que esté dentro de un pozo.

### Potencia del skate

Mike empieza con potencia `P = 1`.

Si está en la casa `X`, puede saltar a cualquier casa en el rango
`[X, X + P]`,\
siempre y cuando:

- No inicie en un pozo.
- No termine en un pozo.

### Mejoras

Si Mike pasa por una casa que tiene una mejora, puede decidir:

- Usarla → se suma su `P_i` a la potencia actual.
- No usarla.

La potencia se acumula:\
Si `P = 1` y usa mejoras de `+2` y `+3` → `P = 6`.

El objetivo es **llegar a la casa F usando la menor cantidad de mejoras
posibles**.

Si no es posible llegar: imprimir `"Imposible"`.

## 2. Intuición del enfoque greedy

La clave:\
**Queremos minimizar la cantidad de mejoras pedidas.**

### Idea general

1.  Mientras podamos **avanzar con la potencia actual**, avancemos.
2.  Mientras avanzamos, "vemos" mejoras que están en casas que ya
    podemos alcanzar.
3.  Las guardamos como **candidatas**.
4.  Solo cuando **no podemos avanzar más**, usamos una mejora.
5.  Y elegimos **la mejor mejora disponible** → la de mayor `P_i`.

Esto es idéntico al patrón:

> “Tengo estaciones de combustible a lo largo de la ruta. Recorro lo que pueda con el combustible actual. Si me quedo sin alcanzar la meta, elijo cargar del surtidor más grande de entre todos los que pasé.”

### ¿Por qué la mayor mejora?

Si ya estamos obligados a usar una mejora:

- Usar cualquier mejora cuenta como **1** en el total.
- Entonces queremos elegir aquella que nos dé **más potencia
  posible**, para:
  - Llegar más lejos.
  - Reducir la cantidad de mejoras futuras.

→ Esa es la esencia del greedy:
Siempre que tenga que usar una mejora, uso la de mayor poder disponible.

Esto requiere una estructura que nos permita sacar **el máximo** rápido
→ un **Heap Máximo**.

## 3. Cómo se manejan los pozos

Recordemos:

- No se puede **caer** en un pozo.
- Pero sí se puede **saltar por encima**.

Ejemplo:

    posicion = 2
    potencia = 3
    alcance = 2 + 3 = 5

    pozo = [3, 4]

Casas:

      1   2   3   4   5   6
      -   M   #   #   -   -

El rango teórico es `[2, 5]`.
Pero `3,4` es un pozo → no podemos caer ahí.

El código revisa:

- Si el pozo empieza dentro de `(posicion, alcance]`
- Y si bloquea nuestro salto
- Ajustamos el alcance a la casa antes de que empiece el pozo:\
  `alcance = inicioPozo - 1`.

En este caso:

- Rango: `(2, 5]`
- Pozo empieza en 3\
  → Ajustamos para no caer allí.

Resultado:\
Solo podemos caer en `5`.

En resumen:
Antes de decidir tu nueva posición (posicion = alcance), se ajusta el alcance para no caer en pozos.

## 4. Idea del algoritmo completo

Variables:

- `posicion`: dónde está Mike (inicia en 1).
- `poder`: potencia del skate (inicia en 1).
- `mejorasUsadas`: cuántas mejoras pedimos.
- Arreglo de `pozos[]`, ordenados por posición.
- Arreglo de `mejoras[]`, ordenados por posición.
- Un HeapMax donde vamos guardando los P_i de mejoras que están dentro de nuestro alcance actual.

Índices:

- `indicePozo`: por dónde vamos en el arreglo de pozos.
- `indiceMejora`: por dónde vamos en el arreglo de mejoras.

### Bucle principal

Mientras `posicion < destino`:

1.  **Descartar pozos atrás**\
    Avanzamos `indicePozo` mientras `pozo.fin < posicion` (ya no afecta, quedó atrás).

2.  **Calcular nuevo alcance**\
    `alcance = posicion + poder`.

    Si `alcance >= destino`: terminamos (ya podemos llegar al maigo).

3.  **Agregar mejoras alcanzables al heap**\
    Mientras `mejoras[indiceMejora].posicion <= alcance`, encolar `P_i`.

    → El heap ahora contiene todas las mejoras que ya podríamos haber pedido.

4.  **Ajustar por pozo si corresponde**\
    Si el pozo actual:

- Empieza dentro del rango (posicion, alcance], y
- Nos “bloquea” caer donde queríamos,

  entonces se modifica alcance = inicioPozo - 1.

5.  **Decidir avanzar o mejorar**

    - Si `alcance > posicion` → avanzar.\
    - Si `alcance <= posicion`: estamos trabados.
      - Si heap vacío → "Imposible".
      - Si no: usar la mejora **más grande**.

El ciclo se repite hasta llegar o declarar "Imposible".

## 5. El HeapMax

Un **heap máximo** permite:

- Insertar: `O(log M)`
- Obtener máximo: `O(1)`
- Remover máximo: `O(log M)`

Se implementa con un arreglo que representa un árbol binario casi
completo.

Propiedad:\
Cada padre es ≥ que sus hijos.

### Métodos

- `flotar(i)`: cuando insertamos.
- `hundir(i)`: cuando removemos el máximo.
- `encolar(valor)`
- `obtenerMaximo()`
- `desencolar()`

### ¿Por qué sirve acá?

Porque:

- Durante el recorrido vamos agregando mejoras.
- Cuando necesitamos una, queremos **la mayor**.

Esto es operación típica de **priority queue**.

Con un heap mantenemos cada operación en O(log M),
y así la complejidad total se mantiene en O((N + M) log M).

## 6. Entendiendo `resolverSkate`

```cpp
int resolverSkate(Pozo pozos[], int cantPozos, Mejora mejoras[], int cantMejoras, int destino)
{
    int posicion = 1;
    int poder = 1;
    int mejorasUsadas = 0;
    int indicePozo = 0;
    int indiceMejora = 0;

    HeapMax *mejorasDisponibles = new HeapMax(cantMejoras);
```

- `posicion = 1`: inicio.
- `poder = 1`: potencia inicial.
- `mejorasUsadas = 0`: contador.
- `indicePozo`, `indiceMejora`: recorremos los arreglos sin
  retroceder.
- `mejorasDisponibles`: heap donde guardamos los `P_i` disponibles.

### Bucle principal

```cpp
while (posicion < destino)
{
```

Seguimos hasta llegar a `destino`.

### Descartar pozos atrás

```cpp
while (indicePozo < cantPozos && pozos[indicePozo].fin < posicion)
    indicePozo++;
```

- Los pozos que ya pasamos no afectan.

### Calcular alcance

```cpp
int alcance = posicion + poder;
if (alcance >= destino)
{
    delete mejorasDisponibles;
    return mejorasUsadas;
}
```

Si ya llegamos, salimos.

### Agregar mejoras alcanzables

```cpp
while (indiceMejora < cantMejoras && mejoras[indiceMejora].posicion <= alcance)
{
    mejorasDisponibles->encolar(mejoras[indiceMejora].aumento);
    indiceMejora++;
}
```

Esto mete todas las mejoras accesibles en el heap.\
Ojo: agregarlas al heap no significa que ya las usamos, solo que podríamos usarlas.

### Ajustar por pozo

```cpp
if (indicePozo < cantPozos &&
    pozos[indicePozo].inicio <= alcance &&
    pozos[indicePozo].inicio > posicion)
{
    if (pozos[indicePozo].fin >= alcance)
        alcance = pozos[indicePozo].inicio - 1;
}
```

Si el salto cae dentro de un pozo, recortamos.

### Avanzar o pedir mejora

```cpp
if (alcance > posicion)
{
    posicion = alcance;
}
else
{
    if (mejorasDisponibles->estaVacio())
    {
        delete mejorasDisponibles;
        return -1;
    }
    poder += mejorasDisponibles->obtenerMaximo();
    mejorasDisponibles->desencolar();
    mejorasUsadas++;
}
```

- Si podemos avanzar → avanzar.
- Si no:
  - Si heap vacío → "Imposible".
  - Si no, usar mejor mejora.

### Final

```cpp
delete mejorasDisponibles;
return mejorasUsadas;
```

## 7. main -- lectura de datos y salida

```cpp
int main()
{
    int cantPozos, cantMejoras, destino;
    cin >> cantPozos >> cantMejoras >> destino;

    Pozo *pozos = new Pozo[cantPozos];
    for (int i = 0; i < cantPozos; i++)
        cin >> pozos[i].inicio >> pozos[i].fin;

    Mejora *mejoras = new Mejora[cantMejoras];
    for (int i = 0; i < cantMejoras; i++)
        cin >> mejoras[i].posicion >> mejoras[i].aumento;

    int resultado = resolverSkate(pozos, cantPozos, mejoras, cantMejoras, destino);

    if (resultado == -1)
        cout << "Imposible\n";
    else
        cout << resultado << "\n";

    delete[] pozos;
    delete[] mejoras;

    return 0;
}
```

- Lee pozos y mejoras.
- Llama a `resolverSkate`.
- Imprime el resultado.

## 8. Complejidad

- Cada pozo se procesa una sola vez → `O(N)`
- Cada mejora se inserta y se saca del heap → `O(M log M)`

Total:

    Tiempo:  O((N + M) log M)
    Espacio: O(N + M)

Cumple exactamente con lo requerido.
