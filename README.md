# Proyecto-II-4-Aho-Corasick

## Descripción

Implementación del algoritmo **Aho-Corasick** en lenguaje C para la búsqueda eficiente de múltiples patrones dentro de un texto. El proyecto incorpora paralelización mediante **Pthreads**, permitiendo dividir el texto de entrada entre varios hilos para acelerar el procesamiento de grandes volúmenes de información.

La solución utiliza una estructura Trie para almacenar los patrones, enlaces de fallo (*Failure Links*) construidos mediante recorrido BFS y procesamiento paralelo con regiones superpuestas (*Overlap*) para evitar la pérdida de coincidencias en los límites de los segmentos.

---

## Características

- Construcción de Trie para almacenamiento de patrones.
- Construcción de Failure Links mediante BFS.
- Búsqueda simultánea de múltiples patrones.
- Procesamiento paralelo utilizando Pthreads.
- División automática del texto entre hilos.
- Implementación de Overlap para evitar pérdidas de coincidencias.
- Lectura de texto desde archivos externos.
- Medición del tiempo de ejecución.
- Conteo total de coincidencias encontradas.

---

## Algoritmos Utilizados

### Trie

Los patrones se almacenan en una estructura Trie que comparte prefijos comunes, reduciendo el espacio necesario para almacenar múltiples cadenas.

### Failure Links

Los enlaces de fallo permiten reutilizar coincidencias parciales cuando una transición no existe, evitando reiniciar la búsqueda desde la raíz.

Los enlaces son construidos utilizando un recorrido BFS (Breadth First Search).

### Paralelización con Pthreads

El texto es dividido en segmentos procesados por múltiples hilos.

Para evitar perder coincidencias que cruzan los límites entre segmentos, se utiliza una región de superposición (*Overlap*) calculada como:

```text
Overlap = LongitudMáximaPatrón - 1
```

Cada hilo procesa una región expandida, pero únicamente contabiliza coincidencias dentro de su rango real asignado.

---

## Estructura del Proyecto

```text
.
├── main.c
├── aho.c
├── aho.h
├── benchmark.sh
├── texto.txt
├── texto_1mb.txt
├── texto_10mb.txt
├── Articulo_IEEE_Aho-Corasick.docx
└── README.md
```

---

## Compilación

```bash
gcc main.c aho.c -pthread -o aho
```

---

## Ejecución

```bash
./aho <archivo> <num_hilos>
```

### Ejemplo

```bash
./aho texto.txt 4
```

---

## Salida Esperada

```text
Archivo: texto.txt
Longitud texto: 461
Patrones: 4
Longitud maxima patron: 4
Overlap: 3
Hilos: 4
Coincidencias totales: 6
Tiempo: 0.000606 segundos
```

---

## Patrones de Prueba

Actualmente el proyecto utiliza los siguientes patrones:

```text
he
she
his
hers
```

Los patrones pueden modificarse directamente en el código fuente para realizar diferentes pruebas.

---

## Requisitos

- GCC
- Biblioteca Pthreads
- Sistema operativo Linux o compatible con POSIX

---

## Créditos

- Sergio Apaza Fernandez: Implementación del algoritmo Aho-Corasick y paralelización con Pthreads.
- Jhonatan Gutiérrez Ticona: Elaboración del informe técnico, documentación y gestión del repositorio.

---

## Objetivo Académico

Desarrollar un buscador de subcadenas paralelo basado en el algoritmo Aho-Corasick utilizando memoria compartida y Pthreads, evaluando el rendimiento del procesamiento concurrente sobre textos de gran tamaño.