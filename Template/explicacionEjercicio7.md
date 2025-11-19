# 🧠 Ejercicio 7 – Ranking de Parciales

## Explicación absoluta, completa y con recorrido función por función

## 0. ¿Qué mide exactamente este ejercicio?

Tenemos:

- Un ranking oficial (orden correcto)
- Un ranking alternativo publicado por un ayudante

Queremos contar cuántos pares de estudiantes están "dados vuelta" entre ambos rankings.

Esto se llama **contar inversiones**.

Un par (A, B) es una inversión si:

- En el ranking oficial: A aparece antes que B
- En el del ayudante: B aparece antes que A

### Ejemplo real

Oficial: Ana ≺ Beto ≺ Carla ≺ Diego  
Ayudante: Beto ≺ Ana ≺ Diego ≺ Carla

Las inversiones son:

- (Ana, Beto)
- (Carla, Diego)

**Total: 2.**

## 1. ¿Cómo transformamos este problema en algo computable?

Representamos el ranking oficial como:

**nombre → posición**

Ejemplo:

- Ana → 0
- Beto → 1
- Carla → 2
- Diego → 3

Luego, el ranking del ayudante:

Beto, Ana, Diego, Carla

se transforma en:

```
[1, 0, 3, 2]
```

Y el número de inversiones entre rankings es exactamente el número de inversiones del arreglo.

## 2. ¿Qué es una inversión en un arreglo?

Un par (i, j) es inversión si:

- i < j
- arr[i] > arr[j]

Ejemplo en `[1,0,3,2]`:

- (0,1) → 1 > 0 → inversión
- (2,3) → 3 > 2 → inversión

**Total: 2.**

## 3. ¿Por qué no podemos usar fuerza bruta?

Comparar todos los pares sería:

```
N^2 = 100000^2 = 10^10 operaciones
```

→ imposible.

El enunciado exige **O(N log N)**.

La solución clásica es **Merge Sort modificado**.

## 4. Merge Sort que cuenta inversiones

Merge Sort:

1. Divide el arreglo en mitades
2. Mezcla ordenadamente
3. Durante la mezcla detecta inversiones cruzadas

Regla clave:

Si `izq[i] > der[j]`, entonces:

```
inversiones += (elementos restantes en izquierda)
```

Esto da el rendimiento O(N log N).

## 5. Recorrido TOTAL del ejemplo [1,0,3,2]

### 5.1 Llamada principal

```
contarInversiones(indicesNumericos, N)
```

Crea auxiliar y llama a:

```
mergeSortYContar(arr, aux, 0, 3)
```

### 5.2 Llamada recursiva

Divide:

- Izquierda: `[1,0]`
- Derecha: `[3,2]`

Llama:

```
mergeSortYContar(0,1)
mergeSortYContar(2,3)
combinarYContar(0,1,3)
```

### 5.3 Mitad izquierda: [1,0]

Divide en:

- [1]
- [0]

Se mezclan:

Comparación:

1 > 0 → inversión

Resultado:

```
[0,1]
inversiones = 1
```

### 5.4 Mitad derecha: [3,2]

Divide en:

- [3]
- [2]

Comparación:

3 > 2 → inversión

Resultado:

```
[2,3]
inversiones = 1
```

---

### 5.5 Mezcla final: [0,1] con [2,3]

Todas las comparaciones son correctas:

0 ≤ 2  
1 ≤ 2  
2 ≤ 3

No hay inversiones cruzadas.

**Total final = 1 + 1 + 0 = 2**

## 6. Mapeo de inversiones a estudiantes

Recordemos:

- 0 → Ana
- 1 → Beto
- 2 → Carla
- 3 → Diego

Inversiones:

- (1,0) → (Beto, Ana) → inversión real: **(Ana, Beto)**
- (3,2) → (Diego, Carla) → inversión real: **(Carla, Diego)**

## 7. Ejemplo 2: Ranking totalmente invertido

Arreglo:

```
[3,2,1,0]
```

Es completamente decreciente.

Inversiones:

```
N(N-1)/2 = 6
```

Merge Sort las detecta todas.

## 8. El Hash: cómo se insertan y buscan nombres

El TP exige no usar `unordered_map`.

Se implementa un Hash Cerrado con doble hashing:

Cada nodo:

- clave (string)
- valor (entero)
- estaBorrado (bool)

Hash:

- fhash1 base 131
- fhash2 base 37 (ajustado a impar)

Insertar:

```
pos = (h1 + intento*h2) % largo
```

Buscar:

```
Repite índices hasta hallar clave
```

Permite:

- Insertar O(1) promedio
- Buscar O(1) promedio

## 9. Recorrido del main

```
cin >> N;
```

Reserva arreglos.

### Leer ranking oficial

```
tabla.insertar(nombre, posición);
```

Queda:

- Ana → 0
- Beto → 1
- Carla → 2
- Diego → 3

### Leer ranking del ayudante

```
indicesNumericos[i] = tabla.buscar(nombre);
```

Obtiene:

```
[1,0,3,2]
```

### Contar inversiones

```
totalInversiones = contarInversiones(indicesNumericos, N);
```

### Imprimir resultado

```
cout << totalInversiones;
```

---

## 10. Complejidad

### Tiempo

- Crear hash: O(N)
- Buscar en hash: O(N)
- Merge Sort: O(N log N)

**Total: O(N log N)**

### Espacio

- Hash: O(N)
- Arreglos oficiales: O(N)
- numérico: O(N)
- auxiliar: O(N)

**Total: O(N)**
