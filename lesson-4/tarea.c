#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//   Cola usando un array  //


#define MAX 100000 // tamaño máximo del array

// Estructura para cola con array
typedef struct {
    int datos[MAX];
    int frente;
    int final;
    int tamaño;
} ColaArray;

// Inicializa la cola
void inicializarColaArray(ColaArray *cola) {
    cola->frente = 0;
    cola->final = -1;
    cola->tamaño = 0;
}

// Agrega un elemento al final de la cola
void encolarArray(ColaArray *cola, int valor) {
    if (cola->tamaño < MAX) {
        cola->final++;
        cola->datos[cola->final] = valor;
        cola->tamaño++;
    }
}

// Saca un elemento del frente de la cola
int desencolarArray(ColaArray *cola) {
    if (cola->tamaño > 0) {
        int valor = cola->datos[cola->frente];
        cola->frente++;
        cola->tamaño--;
        return valor;
    }
    return -1; // si está vacía
}

//Cola usando nodos 


typedef struct Nodo {
    int valor;
    struct Nodo *siguiente;
} Nodo;

// Estructura de la cola con punteros
typedef struct {
    Nodo *frente;
    Nodo *final;
} ColaNodos;

// Inicializa la cola
void inicializarColaNodos(ColaNodos *cola) {
    cola->frente = NULL;
    cola->final = NULL;
}

// Agrega un elemento al final (como deque)
void encolarNodo(ColaNodos *cola, int valor) {
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->valor = valor;
    nuevo->siguiente = NULL;
    if (cola->final == NULL)
        cola->frente = cola->final = nuevo;
    else {
        cola->final->siguiente = nuevo;
        cola->final = nuevo;
    }
}

// Saca un elemento del frente
int desencolarNodo(ColaNodos *cola) {
    if (cola->frente == NULL) return -1;
    Nodo *temp = cola->frente;
    int valor = temp->valor;
    cola->frente = cola->frente->siguiente;
    if (cola->frente == NULL) cola->final = NULL;
    free(temp);
    return valor;
}

//Comparar rendimiento

int main() {
    ColaArray colaA;
    ColaNodos colaN;
    inicializarColaArray(&colaA);
    inicializarColaNodos(&colaN);

    clock_t inicio, fin;
    int i;

    //Cola con array
    inicio = clock();
    for (i = 0; i < 100000; i++) encolarArray(&colaA, i);
    for (i = 0; i < 100000; i++) desencolarArray(&colaA);
    fin = clock();
    double tiempoArray = (double)(fin - inicio) / CLOCKS_PER_SEC;

    //Cola con nodos
    inicio = clock();
    for (i = 0; i < 100000; i++) encolarNodo(&colaN, i);
    for (i = 0; i < 100000; i++) desencolarNodo(&colaN);
    fin = clock();
    double tiempoNodos = (double)(fin - inicio) / CLOCKS_PER_SEC;

    printf("Tiempo con array: %.4f segundos\n", tiempoArray);
    printf("Tiempo con punteros: %.4f segundos\n", tiempoNodos);

    return 0;
}
