# 🧠 Ejercicio 10 – Búsqueda de Producto en Amazon

## Explicación absoluta (teórica + práctica + recorrido del código)

# 0. ¿Qué problema estamos resolviendo?

Tenés **P centros logísticos (FCs)**.  
Cada uno es un mapa **M×N** donde:

- `'C'` → corredor (se puede caminar)
- cualquier otra letra → producto  
  (se puede entrar **solo si** es el producto buscado)

### ✔ Movimiento permitido

- 4 direcciones (arriba, abajo, izquierda, derecha)

### ✔ Posición inicial

- Siempre `(0,0)`

### ✔ Meta

Encontrar el **camino más corto** hasta el producto buscado.

### ❗ Backtracking puro es explosivo

- 50×50 = 2500 celdas,
- cada celda tiene 4 vecinos,
- caminos posibles → **exponencial**, intratable.

👉 Por eso usamos **Backtracking + Poda A\***  
Una optimización **muy potente** basada en distancias reales mínimas.

# 1. Arquitectura general de la solución

La solución tiene **3 componentes**:

## (1) BFS desde el objetivo → `calcularDistancias(...)`

Normalmente buscás desde la entrada hacia la meta.  
Pero acá hacemos el **BFS al revés**, desde el objetivo hacia todo el mapa.

Esto llena una matriz:

```
dist[f][c] = distancia mínima REAL desde (f,c) al objetivo
```

Si dist[f][c] == -1 → esa celda **jamás puede** llegar al objetivo.

Esto nos da una heurística perfecta:
si desde (f,c) se necesitan al menos dist[f][c] pasos más,
entonces cualquier camino actual que ya tenga pasos + dist[f][c] >= mejor
nunca será óptimo.

Esta distancia se usa para la poda A\* dentro del backtracking.

## (2) Backtracking → `backtrack(...)`

Explora caminos posibles desde `(0,0)`:

- avanza por `'C'` o por el producto final
- marca visitado
- retrocede
- aplica podas A\*:
  - si ya soy peor que el mejor → corto
  - si esta celda no puede llegar al objetivo → corto
  - si los pasos actuales + mínimo posible ≥ mejor → corto

Además:

👉 **Ordena movimientos** según `dist`, probando primero los mejores.

Esto lo vuelve extremadamente eficiente.

## (3) Coordinación → `resolverFC(...)` y `main`

`resolverFC`:

- ubica el objetivo
- genera `dist`
- genera `visitado`
- corre el backtracking
- devuelve cantidad mínima de pasos

`main`:

- prueba todos los FCs
- se queda con el mejor (menor pasos)
- imprime índice y pasos

# 2. Explicación profunda del flujo REAL del código

## 🔹 2.1. `calcularDistancias(...)` – BFS inverso

Objetivo:

> “¿Cuántos pasos me faltan como mínimo para llegar desde cada celda al producto?”

### ¿Por qué BFS inverso?

Porque desde cualquier posición `(f,c)` queremos saber:

- ¿puedo llegar al objetivo?
- ¿cuál es la distancia mínima exacta?

Eso permite calcular:

```
pasos_actuales + dist[f][c]
```

Si ese número **ya no puede** ser mejor que el mejor encontrado:

→ **podo**.

### Flujo interno:

1. Inicializa todas las celdas con `dist = -1`
2. Pone el objetivo con `dist = 0`
3. BFS clásico:
   - toma una celda
   - revisa vecinos
   - si vecino es 'C' o es el producto → accesible
   - si dist era -1 → asigna dist = dist_actual + 1

### Resultado:

Una matriz que indica desde dónde es posible llegar al objetivo  
y cuántos pasos faltan.

👉 Poda A\* perfecta, porque es **distancia real**, no estimada.

## 🔹 2.2. `backtrack(...)` – búsqueda profunda + A\*

Esta es la parte central.

Parámetros:

- `fil`, `col` → posición actual
- `pasos` → pasos recorridos
- `dist[][]` → distancia mínima restante
- `visitado[][]` → para evitar ciclos
- `mejor` → mejor valor encontrado hasta ahora

## 🔥 Podas aplicadas

### (1) Ya sos peor que el mejor

```cpp
if (mejor != -1 && pasos >= mejor) return;
```

Ejemplo:
Ya encontraste solución de 11 pasos.  
Otra ruta ya tiene 12 → no sirve → cortar.

### (2) Esta celda NO puede llegar al objetivo

```cpp
if (dist[fil][col] == -1) return;
```

distancia -1 significa:  
“desde acá **no existe** camino posible al objetivo”.

### (3) A\* real – aunque mejores, nunca ganas

```cpp
if (mejor != -1 && pasos + dist[fil][col] >= mejor) return;
```

Interpretación:

```
pasos + (dist mínima posible desde acá) >= mejor
```

Entonces **ni siquiera en el mejor caso** podés ganar → se corta.

## 🔥 Ordenamiento de vecinos (heurística A\*)

Antes de explorar vecinos, se reordenan:

```
según dist[nf][nc]
```

El movimiento “más prometedor” se prueba primero.

Así encontramos la solución óptima temprano  
→ eso baja “mejor”  
→ activa muchas más podas  
→ exploración mínima

## 🔥 Flujo operativo del backtracking

1. Si es subóptimo → cortar
2. Si no llega a objetivo → cortar
3. Si ni sumando lo mejor alcanza → cortar
4. Ordenar movimientos
5. Para cada vecino:
   - si está dentro del mapa
   - si es 'C' o el producto buscado
   - si no está visitado  
     → marcar, llamar recursivamente, desmarcar
6. Si `fil == objetivo.fil && col == objetivo.col`  
   → actualizar mejor, retornar

## 🔹 2.3. `resolverFC(...)`

Hace:

1. Busca la posición del producto
2. Crea matrices `dist` y `visitado`
3. Corre BFS inverso
4. Si `(0,0)` no llega → devolver -1
5. Crear visitado inicial
6. Ejecutar `backtrack(0,0,0)`
7. Liberar memoria
8. Devolver `mejor`

## 🔹 2.4. `main`

1. Lee producto
2. Lee P
3. Por cada FC:
   - lee mapa
   - corre `resolverFC`
   - actualiza mejor
4. Imprime:

```
<indice> <mejor_pasos>
```

# 3. Mini recorrido conceptual simplificado

Supongamos:

```
C C C
C X C
C S C
```

Producto `'S'` en `(2,1)`.

## 🙨 Fase 1: BFS inverso

dist queda:

```
(2,1) = 0
(1,1) = 1
(2,0) = 1
(2,2) = 1
(0,1) = 2
(1,0) = 2
(1,2) = 2
(0,0) = 3
```

Esto indica que la distancia mínima desde `(0,0)` vale **3**.

## 🙨 Fase 2: Backtracking

Inicio:

```
backtrack(0,0,0)
dist[0][0] = 3
→ mínimo posible total = 3
```

Explora vecinos ordenados:

- `(1,0)` dist=2
- `(0,1)` dist=2

Ve primero `(1,0)`:

```
backtrack(1,0,1)
→ dist=2 → total mínimo = 1+2 = 3
```

Luego llega a `(2,1)`:

```
backtrack(2,1,3)
→ encontró el objetivo
```

Actualiza:

```
mejor = 3
```

Ahora cualquier camino que supere 3 se poda automáticamente.

# 4. ¿Por qué es óptimo?

- Backtracking explora todas las rutas posibles.
- BFS inverso da la distancia mínima R-E-A-L.
- A\* evita explorar caminos inútiles.
- Ordenamiento acelera encontrar la solución óptima.

👉 Cumple con la consigna “usar backtracking”,  
pero sin perder eficiencia.

# 5. Complejidad

### Peor caso teórico:

exponencial → 4^(MN)

### Caso real gracias a BFS + A\*:

- se explora solo una franja pequeña alrededor del camino óptimo
- extremadamente rápido incluso si P = 10.000
