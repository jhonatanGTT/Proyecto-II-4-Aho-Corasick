#include <stdio.h>
#include "aho.h"
#include <pthread.h>
#include <string.h>

int main() {

    TrieNode *root = crearNodo();
    printf("ID raiz: %d\n", root->id);

    if(root != NULL)
        printf("Nodo raiz creado correctamente\n");
    else
        printf("Error al crear nodo\n");

	insertarPatron(root, "he");
	insertarPatron(root, "she");
	insertarPatron(root, "his");
	insertarPatron(root, "hers");
	
	char buffer[100];

	printf("Patrones almacenados:\n");
	imprimirTrie(root, buffer, 0);
	
	construirFailureLinks(root);

	printf("\nFailure links:\n");
	imprimirFailures(root);
	
	char texto[] = "ushers";

	int numHilos = 4;

	DatosHilo datos[numHilos];
	pthread_t hilos[numHilos];

	int longitud = strlen(texto);
	int tamSegmento = longitud / numHilos;
	int overlap = maxPatron - 1;
	
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
			datos[i].inicio = datos[i].inicio_real;
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

		printf(
			"Hilo %d: proc=%d..%d real=%d..%d\n",
			i,
			datos[i].inicio,
			datos[i].fin,
			datos[i].inicio_real,
			datos[i].fin_real
		);
		
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
		printf(
			"Hilo %d: %d coincidencias\n",
			i,
			datos[i].coincidencias
		);

		total += datos[i].coincidencias;
	}

	printf(
		"\nTotal coincidencias: %d\n",
		total
	);

    return 0;
}
