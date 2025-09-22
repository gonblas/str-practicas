# Ejercicio 1:

En un sistema de tiempo real con las siguientes tareas:

| Tarea | Tiempo de ejecución | Período/Plazo |
| :---: | :-----------------: | :-----------: |
|   A   |          2          |      12       |
|   B   |          2          |      24       |
|   C   |          2          |       6       |
|   D   |          1          |       3       |

**(a)** Comprueba si existe una planificación de tiempo real viable.

**(b)** Desarrolla un plan cíclico para la ejecución de estas tareas, calculando el periodo principal y secundario y mostrando la tabla de tareas para el ejecutivo cíclico.

## Resolución

### (a)

El factor de utilización (fracción de la CPU que se utiliza en el sistema) se calcula como:

\[
U = \sum_{i=1}^{N} \frac{C_i}{T_i}
\]

Cálculo por tarea:

- A: \(2/12 = 0.1667\)
- B: \(2/24 = 0.0833\)
- C: \(2/6 = 0.3333\)
- D: \(1/3 = 0.3333\)

\[
U = 0.1667 + 0.0833 + 0.3333 + 0.3333 = 0.9166
\]

Comprobamos las condiciones para aplicar cada planificación:

- **Rate Monotonic (RMS):** Límite de utilizabilidad de Liu & Layland para 4 tareas:

  \[
  U\_\text{RMS} = n(2^{1/n}-1) = 4(2^{1/4}-1) \approx 0.7568
  \]

  Comparación:

  \[
  U = 0.9166 > 0.7568
  \]

  Con RMS **no hay garantía de planificación**.

- **Earliest Deadline First (EDF):**

  Condición: \(U \le 1\)

  \[
  U = 0.9166 \le 1
  \]

  Con EDF **sí es planificable**.

---

### (b) 

Determinamos el período principal (hiperperíodo)

El **hiperperíodo** (ciclo completo tras el cual las tareas se repiten) \(H\) es el **mínimo común múltiplo (MCM)** de todos los períodos de todas las tareas:

\[
H = \text{MCM}(3, 6, 12, 24) = 24
\]


El **Período secundario** \(f\) debe cumplir estas condiciones:

1. \(f \ge \text{máximo tiempo de ejecución}\) → \(f \ge 2\)
2. Cada período divisible por \(f\) o \((2f - MCD(T_i, f)) \le D_i\)
3. Frame entero dentro del hiperperíodo: \(H/f\) debe ser entero

**Elegimos**: \(f = 2\) unidades

- Cumple:
  - \(f \ge \max(C_i) = 2\)
  - \(2f - MCD(T_i, f) \le D_i\) → OK
    - D: \(2f−MCD⁡(3,2)=4−1=3≤3\)  
    - C: \(2f−MCD⁡(6,2)=4−2=2≤6\)
    - A: \(2f−MCD⁡(12,2)=4−2=2≤12\)
    - B: \(2f−MCD⁡(24,2)=4−2=2≤24\)
  - Hiperperíodo dividido en frames: \(24 / 2 = 12\) frames (es entero).

Para crear la tabla de ejecución del ejecutivo cíclico dividimos el hiperperíodo en **frames de 2 unidades** y asignamos las tareas respetando su **periodo y tiempo de ejecución**.

| Frame | Tiempo | Tareas ejecutadas      |
| ----- | ------ | ---------------------- |
| 1     | 0-2    | D (1) + C (1 restante) |
| 2     | 2-4    | C (1) + A (1)          |
| 3     | 4-6    | A (1) + D (1)          |
| 4     | 6-8    | C (2)                  |
| 5     | 8-10   | D (1) + B (1)          |
| 6     | 10-12  | A (2)                  |
| 7     | 12-14  | D (1) + C (1)          |
| 8     | 14-16  | C (1) + A (1)          |
| 9     | 16-18  | B (2)                  |
| 10    | 18-20  | D (1) + C (1)          |
| 11    | 20-22  | A (2)                  |
| 12    | 22-24  | B (2)                  |

Dado que el sistema es planificable en la duración de un hiperperiodo, lo será también durante toda la vida del sistema. Puesto que esa planificación se repite infinitamente.
