# 🧠 Ejercicio 8 – Crystal Cascade

## Explicación absoluta, completa y con recorrido función por función

## 🔰 0. Qué vamos a hacer

En esta explicación te cuento:

- 🟦 El problema con palabras simples
- 🟩 Por qué no alcanza con greedy / fuerza bruta
- 🟨 La idea clave de la DP (**dp[izq][der][extras]**) y qué significa cada cosa
- 🟧 La transición de la recurrencia: las dos decisiones importantes
- 🟥 Lectura detallada de tu función `calcMemo`
- 🟪 Recorrido conceptual con el Ejemplo 1 (`1 2 1 1 2`)
- 🟫 Recorrido conceptual con el Ejemplo 3 (`1 3 2 2 2 3 4 3 1`)
- ⚙️ Qué hace `main` y cómo se enlaza todo
- 🧩 Complejidad y por qué cumple con `O(N⁴)` / `O(N³)`

Todo usando tus **funciones**, tus **variables** y tu **código real**.

## 1. 📘 Re-explicando el problema desde cero

Tenemos una fila de cristales:

```
pos:   0  1  2  3  4  ...
color: c0 c1 c2 c3 c4 ...
```

Reglas del juego:

- Elegís **solo grupos consecutivos** del mismo color
- Si eliminás un grupo de tamaño `K`, ganás **K² puntos**
- Los fragmentos se corren hacia la izquierda
- No podés saltear colores
- Hay que eliminar **todo**, maximizando puntos

Ejemplo:

```
N = 5
colores = [1, 2, 1, 1, 2]
```

Estrategia óptima:

- Eliminar `2` solo → `1² = 1` → queda `[1,1,1,2]`
- Eliminar `[1,1,1]` → `3² = 9` → queda `[2]`
- Eliminar `[2]` → `1² = 1`

➡️ **Total = 11 puntos**

## 2. ❌ Por qué no alcanza con greedy

Greedy no sirve porque:

- Borrar el grupo más grande ahora puede **bloquear la formación de un grupo aún más grande después**
- Lo que eliminás hoy cambia la estructura de mañana
- El futuro depende del presente → característica clásica de DP

Ejemplo del enunciado:

- Estrategia óptima: **11**
- Estrategia greedy: **9**

Por eso necesitamos probar **todas** las posibilidades…  
Pero sin exponencial → **DP top‑down con memoización**.

## 3. 🧠 Idea fundamental de la DP: `dp[izq][der][extras]`

Tu función:

```cpp
long long calcMemo(int izq, int der, int extras, int N)
```

Significado:

- `izq` y `der`: trabajamos sobre el subarreglo `[izq..der]`
- `extras`: cuántos cristales **adicionales del mismo color que `colores[der]`**  
  están “reservados” a la derecha

Interpretación intuitiva:

> “Cuántos puntos puedo obtener borrando todo entre `izq` y `der`, considerando que además tengo `extras` cristales del color de `der` pegados al final.”

Esto permite representar **agrupar elementos iguales que estaban separados**.

Es la clave del problema “Remove Boxes”.

## 4. 🔄 La recurrencia: las dos decisiones

### 🔹 Opción 1 — Borrar el cristal `der` (y sus `extras`) ahora

```cpp
long long mejor =
    calcMemo(izq, der - 1, 0, N) + (extras + 1) * (extras + 1);
```

Interpretación:

- Primero resolvés `[izq..der‑1]`
- Luego eliminás un bloque de tamaño `extras + 1`

Esta opción es:

> “No quiero juntar más cristales de este color. Lo borro ahora.”

### 🔹 Opción 2 — Juntar el color `der` con otro igual a la izquierda

```cpp
for (int i = izq; i < der; i++)
    if (colores[i] == colores[der])
```

Si encontramos un índice `i` donde el color coincide:

```cpp
long long unir =
    calcMemo(izq, i, extras + 1, N) +
    calcMemo(i + 1, der - 1, 0, N);
```

Interpretación:

- Borro el medio `[i+1..der-1]`
- Dejo que `colores[i]` se una con `colores[der]` y sus extras
- El bloque final será MUCHO más grande → da más puntos

## 5. 📖 Lectura profunda de la función `calcMemo`

```cpp
if (izq > der) return 0;
```

Subarreglo vacío → no hay puntaje.

```cpp
long long &memo = dpMemo[izq][der][extras];
if (memo != -1) return memo;
```

Si ya lo calculamos → lo devolvemos.  
**Acá ocurre la memoización real.**

```cpp
long long mejor =
    calcMemo(izq, der - 1, 0, N) + (extras + 1) * (extras + 1);
```

Opción 1: borrar `der` ahora.

```cpp
for (int i = izq; i < der; i++)
{
    if (colores[i] == colores[der])
    {
        long long unir =
            calcMemo(izq, i, extras + 1, N) +
            calcMemo(i + 1, der - 1, 0, N);

        mejor = miMax(mejor, unir);
    }
}
```

Opción 2: juntar con iguales a la izquierda.

```cpp
memo = mejor;
return mejor;
```

Guardamos y devolvemos → **memoización final**.

## 6. 🧪 Recorrido conceptual – Ejemplo 1

```
colores = [1, 2, 1, 1, 2]
```

Llamada principal:

```
calcMemo(0, 4, 0)
```

`der = 4`, color = 2.

### Opción 1:

```
calcMemo(0,3,0) + 1²
```

### Opción 2:

Buscamos posiciones con el mismo color que `colores[4] = 2`:

- `i = 1`

Entonces:

```
calcMemo(0,1,1) + calcMemo(2,3,0)
```

Esto representa exactamente la estrategia óptima:

- Borrar uno de los `2`
- Juntar los `1,1,1`
- Borrarlos juntos
- Borrar el último `2`

➡️ El DP explora esta rama y obtiene el valor **11**.

## 7. 🧪 Recorrido conceptual – Ejemplo 3

```
colores = [1,3,2,2,2,3,4,3,1]
```

El DP:

- detecta que los `2` centrales pueden borrarse juntos
- luego se forman bloques más grandes de `3`
- finalmente junta los `1` de extremos

Esto aparece como varias ramas en la recurrencia donde:

- `i` recorre posiciones con colores iguales
- `extras` permite juntar cajas

➡️ El DP encuentra la solución óptima: **23**.

## 8. ⚙️ Qué hace main

1. Lee `N` y el arreglo `colores[]`
2. Reserva `dpMemo` como un arreglo 3D:
   ```
   dpMemo[N][N][N]
   ```
3. Inicializa todo a `-1`
4. Llama a:
   ```
   calcMemo(0, N-1, 0, N)
   ```
5. Imprime el resultado
6. Libera memoria

## 9. ⏱️ Complejidad

### Estados:

- `izq` → N
- `der` → N
- `extras` → N

Total: **N³**

### Cada estado hace hasta N combinaciones:

For interno → N

### Total:

- **Tiempo: `O(N⁴)`**
- **Espacio: `O(N³)`**

Perfecto para N = 100.

## 10. 📝 Resumen corto

- Problema tipo _Remove Boxes_
- Greedy falla → DP obligatoria
- DP 3D: `dp[izq][der][extras]`
- Dos decisiones:
  - borrar `der` ahora
  - unirlo con iguales a la izquierda
- Memoización en `dpMemo`
- Complejidad:
  - Tiempo: `O(N⁴)`
  - Espacio: `O(N³)`
