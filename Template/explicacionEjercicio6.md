# Ejercicio 6 — Skate a Propulsión (explicación profunda y corregida)

## 0. Qué vamos a hacer en esta explicación

En este archivo explico:

1. **El problema con palabras simples**
2. **La idea intuitiva del greedy** (por qué funciona)
3. **Cómo se manejan los pozos**
4. **El paso a paso del algoritmo**
5. **Por qué usamos un HeapMax**
6. **Lectura detallada de `resolverSkate`**
7. **Complejidad temporal y espacial**

# 1. Re-explicando el problema desde cero

Tenemos casas numeradas:

```
1, 2, 3, 4, 5, 6, 7, ... , F
```

Mike está en la casa **1**.  
Su amigo vive en la casa **F**.

Hay tramos con pozos donde **no puede iniciar** ni **terminar** un salto.  
Cada pozo se da como intervalo `[I_i, D_i]`.

Ejemplo:

```
casas:   1   2   3   4   5   6   7
calle:   M   -   #   #   -   -   -
          ^   ^   ^   ^
       Mike  bien pozo
```

Además, algunos vecinos ofrecen mejoras:

- Casa `X_i`
- Aumento `P_i`
- Nunca dentro de pozos
- Ordenadas por posición

## Potencia del skate

Mike empieza con:

```
P = 1
```

Desde la casa `X` puede saltar a cualquier casa en:

```
[X, X+P]
```

siempre y cuando:

- No inicie dentro de un pozo
- No termine dentro de un pozo

## Mejoras

Si Mike pasa por una casa con mejora puede:

- Usarla → sumar `P_i`
- Ignorarla

Las mejoras se acumulan.

## Objetivo

Llegar a `F` usando **la menor cantidad de mejoras posibles**.

Si no puede llegar → imprimir `"Imposible"`.

# 2. Intuición del enfoque greedy

Queremos **minimizar la cantidad de mejoras pedidas**.

El enfoque correcto consiste en:

1. Avanzar todo lo posible con la potencia actual.
2. Mientras avanzamos, agregamos al heap todas las mejoras alcanzables.
3. Solo pedimos una mejora cuando estamos **trancados**.
4. Y siempre tomamos **la de mayor potencia**.

Es equivalente a:

> “Avanzo hasta donde pueda. Si no llego, cargo del surtidor más grande entre los que pasé.”

## ¿Por qué usar la mejora más grande?

Si estamos obligados a usar **una**, da igual cuál en términos de conteo:

- Todas cuestan 1 en el total.

Pero la que tiene mayor `P_i`:

- Permite avanzar más lejos.
- Aumenta el rango en el próximo paso.
- Evita pedir mejoras futuras.

Ese es el principio greedy fundamental.

# 3. Cómo se manejan los pozos (versión final sin `indicePozoAlcance`)

El código usa **un único índice global** para pozos:

### ✔ `indicePozo`

Sirve para descartar pozos que ya quedaron **atrás**:

```
pozos[indicePozo].fin < posicion
```

Estos pozos no vuelven a afectar el recorrido.

## Detectar pozos que bloquean un salto

Para saber si un pozo bloquea el salto desde `posicion` hasta `alcance`, se usa un **índice auxiliar local**:

```cpp
int j = indicePozo;
while (j < cantPozos && pozos[j].fin < alcance)
    j++;
```

Después se pregunta:

```cpp
if (j < cantPozos &&
    pozos[j].inicio <= alcance &&
    pozos[j].inicio > posicion)
{
    alcance = pozos[j].inicio - 1;
}
```

Este `j`:

- Nunca retrocede.
- Recorre cada pozo como mucho una vez.
- Mantiene la complejidad en **O(N)**.

No existe más `indicePozoAlcance` ni ninguna estructura adicional.

# 4. Paso a paso del algoritmo completo

Mientras `posicion < destino`:

## **1. Descartar pozos atrás**

```
pozo.fin < posicion
```

No afectan más.

## **2. Calcular alcance**

```
alcance = posicion + poder
```

Si alcanza el destino → terminamos.

## **3. Agregar mejoras alcanzables**

Todas las que cumplan:

```
mejora.posicion ≤ alcance
```

se encolan en el HeapMax (aún no se usan).

## **4. Detectar si algún pozo bloquea el salto**

Se revisa el primer pozo cuyo inicio esté dentro de:

```
(posicion, alcance]
```

Si bloquea el salto, recortamos:

```
alcance = inicioPozo - 1
```

## **5. Avanzar o usar mejora**

- Si `alcance > posicion` → avanzar.
- Si `alcance == posicion`:
  - Si heap vacío → “Imposible”.
  - Si heap no vacío → usar la **mejor mejora disponible**.

# 5. El HeapMax

Implementa una **cola de prioridad de máximos**.

## Operaciones

- Insertar → `O(log M)`
- Obtener máximo → `O(1)`
- Sacar máximo → `O(log M)`

Es esencial porque:

- Las mejoras no están ordenadas por `P_i`.
- Necesitamos siempre “la mejor disponible”.

# 6. Lectura detallada de `resolverSkate`

Fragmentos clave:

### Descartar pozos atrás

```cpp
while (indicePozo < cantPozos && pozos[indicePozo].fin < posicion)
    indicePozo++;
```

### Calcular alcance

```cpp
int alcance = posicion + poder;
if (alcance >= destino)
    return mejorasUsadas;
```

### Agregar mejoras al heap

```cpp
while (indiceMejora < cantMejoras && mejoras[indiceMejora].posicion <= alcance)
{
    mejorasDisponibles->encolar(mejoras[indiceMejora].aumento);
    indiceMejora++;
}
```

### Detectar pozo que bloquea

```cpp
int j = indicePozo;
while (j < cantPozos && pozos[j].fin < alcance)
    j++;

if (j < cantPozos &&
    pozos[j].inicio <= alcance &&
    pozos[j].inicio > posicion)
{
    alcance = pozos[j].inicio - 1;
}
```

### Avanzar o mejorar

```cpp
if (alcance > posicion)
{
    posicion = alcance;
}
else
{
    if (mejorasDisponibles->estaVacio())
        return -1;

    poder += mejorasDisponibles->obtenerMaximo();
    mejorasDisponibles->desencolar();
    mejorasUsadas++;
}
```

# 7. Complejidad

### ✔ Complejidad temporal

| Etapa             | Costo                | Justificación                           |
| ----------------- | -------------------- | --------------------------------------- |
| Descarte de pozos | `O(N)`               | Cada pozo se procesa una sola vez       |
| Agregar mejoras   | `O(M log M)`         | Cada mejora se inserta en heap una vez  |
| Usar mejoras      | `O(M log M)`         | A lo sumo se extrae cada mejora una vez |
| **Total**         | **O((N + M) log M)** | Dominado por operaciones del heap       |
| **Espacio**       | **O(N + M)**         | Arrays + heap                           |

Cumple exactamente lo pedido: **O(N log M)**.
