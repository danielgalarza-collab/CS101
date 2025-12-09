// io_threads.c
#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4

void* escribir(void* arg) {
    FILE* f = fopen("salida.txt", "a");
    if (!f) return NULL;

    for (int i = 0; i < 50000; i++) {
        fprintf(f, "Linea %d del hilo %ld\n", i, (long)arg);
    }

    fclose(f);
    return NULL;
}

int main() {
    pthread_t hilos[NUM_THREADS];
    clock_t inicio = clock();

    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&hilos[i], NULL, escribir, (void*)i);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(hilos[i], NULL);
    }

    clock_t fin = clock();
    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

    printf("Tiempo usando threads (I/O): %.3f segundos\n", tiempo);
    return 0;
}
