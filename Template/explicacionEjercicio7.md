# 🧠 Ejercicio 7 – Ranking de Parciales (versión defensa con ejemplo)

## 1. ¿Qué problema estamos resolviendo?

Tenemos dos rankings de estudiantes:

- **El oficial** (orden correcto).
- **El del ayudante**, que está mezclado.

Queremos contar cuántos pares de estudiantes están “al revés” entre un ranking y otro.  
A eso se le llama **inversiones**.

Un par (A, B) es una inversión si:

- A aparece antes que B en el ranking oficial.
- B aparece antes que A en el ranking del ayudante.

## 2. ¿Cómo convertimos nombres en algo manipulable?

A cada estudiante le asignamos su posición oficial:

Ejemplo:

Oficial:

```
Ana, Beto, Carla, Diego
```

Entonces:

| Nombre | Posición oficial |
| ------ | ---------------- |
| Ana    | 0                |
| Beto   | 1                |
| Carla  | 2                |
| Diego  | 3                |

Luego transformamos el ranking del ayudante usando esa tabla.

Si el ayudante publica:

```
Beto, Ana, Diego, Carla
```

Se vuelve:

```
[1, 0, 3, 2]
```

Ahora el problema se reduce a:

👉 **Contar inversiones en ese arreglo numérico.**

## 3. ¿Qué es una inversión en un arreglo?

Un par (i, j) es una inversión si:

```
i < j  y  arr[i] > arr[j]
```

Ejemplo con:

```
[1, 0, 3, 2]
```

Inversiones:

- (1 > 0) → ✓
- (3 > 2) → ✓

**Total: 2.**

## 4. ¿Por qué necesitamos Merge Sort modificado?

Porque N puede ser hasta **100.000**.  
La fuerza bruta sería:

```
N^2 = 10^10 comparaciones → imposible
```

El enunciado pide **O(N log N)** → exactamente la complejidad de Merge Sort.

Merge Sort permite contar inversiones en la etapa de combinación:

Si durante la mezcla encontramos:

```
izq[i] > der[j]
```

entonces hay **tantas inversiones como elementos quedan en la mitad izquierda**.

Ese truco nos da la velocidad óptima.

## 5. Ejemplo completo paso a paso

Arreglo a analizar:

```
[1, 0, 3, 2]
```

### Paso 1: dividir

Mitad izquierda: `[1, 0]`  
Mitad derecha: `[3, 2]`

### Paso 2: resolver cada mitad

#### Izquierda → `[1,0]`

Se divide:

- [1]
- [0]

Al mezclar:

1 > 0 → inversión  
Resultado ordenado: `[0,1]`  
Inversiones acumuladas: **1**

#### Derecha → `[3,2]`

Se divide:

- [3]
- [2]

Al mezclar:

3 > 2 → inversión  
Resultado: `[2,3]`  
Inversiones acumuladas: **1**

### Paso 3: Mezcla final

Mezclamos `[0,1]` con `[2,3]`

No se generan inversiones porque todo está en buen orden.

Total final = 1 + 1 = **2 inversiones**

## 6. ¿Cómo encaja esto con los estudiantes?

Con el ejemplo original:

- arr = [1,0,3,2]
- Inversiones detectadas:
  - (1,0) → Beto antes que Ana → está al revés respecto al oficial
  - (3,2) → Diego antes que Carla → otro al revés

Lo cual corresponde exactamente a:

```
(Ana, Beto)
(Carla, Diego)
```

## 7. Uso del Hash Cerrado

Para transformar nombres en posiciones oficiales de manera eficiente, implementamos un **hash cerrado con doble hashing**, ya que el enunciado no permite usar `unordered_map`.

El hash permite:

- Insertar: O(1) promedio
- Buscar: O(1) promedio

Su único propósito es transformar nombres → índices numéricos.

## 8. Flujo del programa (main)

1. Se lee N.
2. Se carga el ranking oficial en el hash.
3. Se lee el ranking del ayudante y se transforma en un arreglo de posiciones.
4. Se llama:

```
contarInversiones(arreglo, N)
```

5. Se imprime el número total.

## 9. Complejidad

### Tiempo:

- Construir Hash: **O(N)**
- Buscar en Hash: **O(N)**
- Merge Sort + conteo: **O(N log N)**

Total:

```
O(N log N)
```

### Espacio:

- Hash cerrado: O(N)
- Arreglo numérico: O(N)
- Arreglo auxiliar: O(N)

Total:

```
O(N)
```

## 10. Resumen final (para argumentar en defensa)

- Convertimos nombres en índices usando un hash cerrado eficiente.
- El segundo ranking pasa a ser un arreglo de enteros.
- El número de inversiones entre rankings es exactamente el número de inversiones del arreglo.
- Usamos Merge Sort modificado para contar inversiones sin superar el tiempo requerido.
- `long long` es obligatorio para evitar overflow.
- Complejidad final: `O(N log N)`.

Con esto el ejercicio queda sólidamente armado y defendible.
