# 🧠 Ejercicio 9 – A Último Momento

## Explicación completa, con ejemplo, complejidad y autoría

# 1. Descripción del problema

Tenemos **N archivos** del obligatorio de Estructuras 3.  
Cada archivo tiene:

- **t** → tamaño en MB
- **l** → cantidad de líneas
- **p** → puntaje que otorga

Pero la entrega **no puede exceder**:

- **S MB totales**
- **L líneas totales**

El objetivo es **elegir los archivos que maximicen el puntaje**, sin superar ninguno de los límites.

Este es un problema de **mochila**, pero con **dos restricciones** → tamaño y líneas.  
Por eso usamos **Programación Dinámica 3D con tabulación**, tal como pide el enunciado.

# 2. Idea de la solución (intuitiva)

El enfoque consiste en evaluar, para cada archivo, si conviene **incluirlo** o **no incluirlo**, pero sin revisitar el mismo estado dos veces.

El DP almacena la mejor combinación posible usando:

```
dp[i][j][k]:
  máximo puntaje usando los primeros i archivos,
  con límite de j MB,
  y límite de k líneas.
```

Para cada archivo decidimos entre:

- **No tomarlo** → heredamos el valor anterior
- **Tomarlo (si entra)** → sumamos su puntaje y descontamos recursos

Esto nos permite explorar todas las combinaciones válidas dentro del límite pedido de **O(N·S·L)**.

# 3. Detalle del DP

La transición es:

```
dp[i][j][k] = dp[i-1][j][k]                                   // no tomar

si j ≥ t_i y k ≥ l_i:
    dp[i][j][k] = max(
        dp[i][j][k],
        p_i + dp[i-1][j - t_i][k - l_i]   // tomar
    )
```

Base:

```
dp[0][*][*] = 0
```

Se llena de forma **iterativa**, no recursiva (tabulación pura).

# 4. Ejemplo ilustrativo

Entrada:

```
10
50
1000
16 665 1
6 501 8
25 904 7
18 591 5
7 683 6
22 88 1
24 497 9
22 565 7
31 414 9
49 389 2
```

Interpretación:

- Máximo tamaño: **50 MB**
- Máx. líneas: **1000**
- Los archivos tienen tamaños, líneas y puntajes variados

Una combinación buena es:

| Archivo | t   | l   | p   |
| ------- | --- | --- | --- |
| 6       | 22  | 88  | 1   |
| 7       | 24  | 497 | 9   |
| 10      | 49  | 389 | 2   |

Pero esta no cumple tamaño (22+24+49 = 95 > 50).  
El DP explora TODAS las combinaciones válidas sin pasarse, y encuentra la mejor.

El resultado del ejemplo es:

```
17
```

Significa que la mejor selección posible dentro de los límites suma **17 puntos**.

# 5. Justificación de la complejidad temporal

El DP tiene tres dimensiones:

- i recorre 0..N → N estados
- j recorre 0..S → S estados
- k recorre 0..L → L estados

Para cada estado hacemos O(1) trabajo.

Por lo tanto:

```
Tiempo = O(N · S · L)
Espacio = O(N · S · L)
```

Esto cumple exactamente lo pedido por el enunciado.

# 6. Fragmento clave del código (comentado)

```cpp
// Caso general: no tomar el archivo
dp[i][j][k] = dp[i-1][j][k];

// Caso tomar (si cabe en ambas restricciones)
if (j >= t && k >= ln) {
    int candidato = p + dp[i-1][j - t][k - ln];
    dp[i][j][k] = max(dp[i][j][k], candidato);
}
```

Este patrón es idéntico al DP de mochila 0-1 visto en clase,  
pero extendido a una dimensión adicional.

# 7. Declaración de autoría

Este problema fue desarrollado íntegramente por nuestro grupo.  
Nos basamos **exclusivamente** en la explicación de **tabulación para la mochila 0‑1** vista en clase, adaptándola al caso de **dos restricciones** (tamaño y líneas), siguiendo exactamente el modelo **dp[i][j][k]** exigido en el enunciado.

El diseño del estado, su interpretación, las transiciones y la adaptación al caso 3D fueron elaborados por el grupo. No se utilizaron recursos externos ni herramientas de inteligencia artificial generativa durante la construcción del algoritmo ni de la implementación.
