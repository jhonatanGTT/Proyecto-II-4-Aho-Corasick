#include <stdlib.h>
#include <stdio.h>
#include "aho.h"
#include <string.h>

int contadorNodos = 0;
int maxPatron = 0;

TrieNode* crearNodo() {

    TrieNode *nuevo = (TrieNode*)malloc(sizeof(TrieNode));
		nuevo->id = contadorNodos++;
		nuevo->failure = NULL;
		nuevo->patron = NULL;
		
    for(int i = 0; i < ALFABETO; i++) {
        nuevo->children[i] = NULL;
    }

    nuevo->esFinPalabra = 0;
    return nuevo;
}

void insertarPatron(TrieNode *root, const char *patron)
{
    int len = strlen(patron);

    if(len > maxPatron)
    {
        maxPatron = len;
    }

    TrieNode *actual = root;
    for(int i = 0; patron[i] != '\0'; i++)
    {
        int idx = patron[i] - 'a';

        if(actual->children[idx] == NULL)
        {
            actual->children[idx] = crearNodo();
        }
        actual = actual->children[idx];
    }
    actual->esFinPalabra = 1;
    actual->patron = (char*)patron;
}

void imprimirTrie(TrieNode *node, char *buffer, int nivel)
{
    if(node == NULL)
        return;

    if(node->esFinPalabra)
    {
        buffer[nivel] = '\0';
        printf("ID=%d -> %s\n", node->id, buffer);
    }

    for(int i = 0; i < ALFABETO; i++)
    {
        if(node->children[i] != NULL)
        {
            buffer[nivel] = 'a' + i;
            imprimirTrie(node->children[i],buffer,nivel + 1);
        }
    }
}

void construirFailureLinks(TrieNode *root)
{
    Queue q;
    initQueue(&q);
    root->failure = root;

    for(int i = 0; i < ALFABETO; i++)
    {
        if(root->children[i] != NULL)
        {
            root->children[i]->failure = root;
            enqueue(&q, root->children[i]);
        }
    }

    while(!isEmpty(&q))
    {
        TrieNode *actual = dequeue(&q);

        for(int i = 0; i < ALFABETO; i++)
        {
            TrieNode *hijo = actual->children[i];

            if(hijo == NULL)
                continue;

            TrieNode *f = actual->failure;

            if(f->children[i] != NULL)
            {
                hijo->failure = f->children[i];
            }
            else
            {
                hijo->failure = root;
            }

            enqueue(&q, hijo);
        }
    }
}

void imprimirFailures(TrieNode *node)
{
    if(node == NULL)
        return;

    printf("Nodo %d -> ", node->id);

    if(node->failure != NULL)
        printf("failure=%d\n", node->failure->id);
    else
        printf("failure=NULL\n");

    for(int i = 0; i < ALFABETO; i++)
    {
        if(node->children[i] != NULL)
        {
            imprimirFailures(node->children[i]);
        }
    }
}

int buscarSegmento(TrieNode *root,const char *texto,int inicio,int fin, int inicio_real, int fin_real) 
{
    TrieNode *actual = root;

    int coincidencias = 0;

    for(int i = inicio; i <= fin; i++)
    {
        int idx = texto[i] - 'a';

        if(idx < 0 || idx >= ALFABETO)
        {
            actual = root;
            continue;
        }

        while(actual != root && actual->children[idx] == NULL)
        {
            actual = actual->failure;
        }

        if(actual->children[idx] != NULL)
        {
            actual = actual->children[idx];
        }

        TrieNode *temp = actual;

        while(temp != root)
        {
            if(temp->esFinPalabra)
            {
                if(i >= inicio_real && i <= fin_real)
                {
                    coincidencias++;

                    // printf("Encontrado: %s termina en %d\n",temp->patron,i);
                }
            }
            temp = temp->failure;
        }
    }
    return coincidencias;
}

void *trabajador(void *arg)
{
    DatosHilo *datos = (DatosHilo*)arg;

    datos->coincidencias =
        buscarSegmento(
            datos->root,
            datos->texto,
            datos->inicio,
            datos->fin,
            datos->inicio_real,
            datos->fin_real
        );

    return NULL;
}

void initQueue(Queue *q)
{
    q->front = 0;
    q->rear = 0;
}

int isEmpty(Queue *q)
{
    return q->front == q->rear;
}

void enqueue(Queue *q, TrieNode *node)
{
    q->items[q->rear++] = node;
}

TrieNode* dequeue(Queue *q)
{
    return q->items[q->front++];
}

char *leerArchivo(const char *nombreArchivo)
{
    FILE *archivo = fopen(nombreArchivo, "r");

    if(archivo == NULL)
    {
        return NULL;
    }

    fseek(archivo, 0, SEEK_END);

    long tam = ftell(archivo);

    rewind(archivo);

    char *buffer = malloc(tam + 1);

    if(buffer == NULL)
    {
        fclose(archivo);
        return NULL;
    }

    fread(buffer, 1, tam, archivo);

    buffer[tam] = '\0';

    fclose(archivo);

    return buffer;
}