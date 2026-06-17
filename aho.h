#ifndef AHO_H
#define AHO_H

#define ALFABETO 26

typedef struct TrieNode {
		int id;
    struct TrieNode *children[ALFABETO];
    struct TrieNode *failure;
    int esFinPalabra;
    char *patron;
} TrieNode;

typedef struct {
    TrieNode *items[1000];
    int front;
    int rear;
} Queue;

typedef struct {
    TrieNode *root;
    const char *texto;

    int inicio;
    int fin;

    int inicio_real;
    int fin_real;

    int coincidencias;
} DatosHilo;

TrieNode* crearNodo();
void insertarPatron(TrieNode *root, const char *patron);
void imprimirTrie(TrieNode *node, char *buffer, int nivel);

void initQueue(Queue *q);
int isEmpty(Queue *q);
void enqueue(Queue *q, TrieNode *node);
TrieNode* dequeue(Queue *q);

void construirFailureLinks(TrieNode *root);
void imprimirFailures(TrieNode *node);

int buscarSegmento(
    TrieNode *root,
    const char *texto,
    int inicio,
    int fin,
    int inicio_real,
    int fin_real
);

void *trabajador(void *arg);

extern int maxPatron;

char *leerArchivo(const char *nombreArchivo);

#endif
