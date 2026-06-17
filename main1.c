#include <stdio.h>
#include "aho.h"

int main()
{

	TrieNode *root = crearNodo();
	printf("ID raiz: %d\n", root->id);

	if (root != NULL)
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

	printf("\nBusqueda:\n");

	char texto[] = "ushers";

	int total = buscarSegmento(
		root,
		texto,
		0,
		5);

	printf("\nTotal coincidencias: %d\n",total);

	return 0;
}
