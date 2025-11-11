#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N1 10000
#define N2 100000

int busqueda_lineal(int arr[], int n, int valor) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == valor) return i;
    }
    return -1;
}

int busqueda_binaria(int arr[], int n, int valor) {
    int izq = 0, der = n - 1;
    while (izq <= der) {
        int medio = (izq + der) / 2;
        if (arr[medio] == valor) return medio;
        if (arr[medio] < valor)
            izq = medio + 1;
        else
            der = medio - 1;
    }
    return -1;
}

void llenar(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = i + 1;
}

int main() {
    int *a1 = malloc(N1 * sizeof(int));
    int *a2 = malloc(N2 * sizeof(int));
    llenar(a1, N1);
    llenar(a2, N2);

    int valor = N2; // buscar el último número
    clock_t inicio, fin;
    double tiempo;

    printf("Busqueda en arreglo de 10.000 elementos\n");

    inicio = clock();
    busqueda_lineal(a1, N1, valor);
    fin = clock();
    tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Lineal: %.6f segundos\n", tiempo);

    inicio = clock();
    busqueda_binaria(a1, N1, valor);
    fin = clock();
    tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Binaria: %.6f segundos\n\n", tiempo);

    printf("Busqueda en arreglo de 100.000 elementos\n");

    inicio = clock();
    busqueda_lineal(a2, N2, valor);
    fin = clock();
    tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Lineal: %.6f segundos\n", tiempo);

    inicio = clock();
    busqueda_binaria(a2, N2, valor);
    fin = clock();
    tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Binaria: %.6f segundos\n", tiempo);

    free(a1);
    free(a2);

    printf("\nResumen:\n");
    printf("- La busqueda lineal tarda mas porque recorre todo el arreglo.\n");
    printf("- La busqueda binaria es mucho mas rapida porque va dividiendo a la mitad.\n");
    printf("- A mayor cantidad de datos, se nota mucho la diferencia.\n");

    return 0;
}
