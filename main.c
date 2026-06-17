#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#include "aho.h"

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Uso: %s <archivo> <num_hilos>\n",argv[0]);
        return 1;
    }

    char *texto = leerArchivo(argv[1]);

    if(texto == NULL)
    {
        printf("Error al abrir archivo\n");
        return 1;
    }

    TrieNode *root = crearNodo();

    insertarPatron(root, "he");
    insertarPatron(root, "she");
    insertarPatron(root, "his");
    insertarPatron(root, "hers");

    construirFailureLinks(root);

    int numHilos = atoi(argv[2]);//ascii to integer

    int longitud = strlen(texto);

    int overlap = maxPatron - 1;

    DatosHilo datos[numHilos];
    pthread_t hilos[numHilos];

    int tamSegmento = longitud / numHilos;

    clock_t inicioTiempo = clock();

    for(int i = 0; i < numHilos; i++)
    {
        datos[i].root = root;
        datos[i].texto = texto;

        datos[i].inicio_real = i * tamSegmento;

        if(i == numHilos - 1)
        {
            datos[i].fin_real = longitud - 1;
        }
        else
        {
            datos[i].fin_real =
                (i + 1) * tamSegmento - 1;
        }

        if(i == 0)
        {
            datos[i].inicio =
                datos[i].inicio_real;
        }
        else
        {
            datos[i].inicio =
                datos[i].inicio_real - overlap;

            if(datos[i].inicio < 0)
            {
                datos[i].inicio = 0;
            }
        }

        datos[i].fin = datos[i].fin_real;

        datos[i].coincidencias = 0;
    }

    for(int i = 0; i < numHilos; i++)
    {
        pthread_create(
            &hilos[i],
            NULL,
            trabajador,
            &datos[i]
        );
    }

    for(int i = 0; i < numHilos; i++)
    {
        pthread_join(
            hilos[i],
            NULL
        );
    }

    int total = 0;

    for(int i = 0; i < numHilos; i++)
    {
        total += datos[i].coincidencias;
    }

    clock_t finTiempo = clock();

    double tiempo =
        (double)(finTiempo - inicioTiempo)
        / CLOCKS_PER_SEC;

    printf("Archivo: %s\n", argv[1]);
    printf("Longitud texto: %d\n", longitud);
    printf("Patrones: 4\n");
    printf("Longitud maxima patron: %d\n", maxPatron);
    printf("Overlap: %d\n", overlap);
    printf("Hilos: %d\n", numHilos);
    printf("Coincidencias totales: %d\n", total);
    printf("Tiempo: %.6f segundos\n", tiempo);

    free(texto);

    return 0;
}