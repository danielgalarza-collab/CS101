// cpu_processes.c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define NUM_PROCESOS 4
#define LIMITE 50000

int esPrimo(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int main() {
    clock_t inicio = clock();

    for (int i = 0; i < NUM_PROCESOS; i++) {
        pid_t pid = fork();

        if (pid == 0) { // hijo
            int cuenta = 0;
            for (int j = 0; j < LIMITE; j++) {
                if (esPrimo(j)) cuenta++;
            }
            printf("Proceso hijo %d encontró %d primos\n", i, cuenta);
            return 0; 
        }
    }

    for (int i = 0; i < NUM_PROCESOS; i++)
        wait(NULL);

    clock_t fin = clock();
    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

    printf("Tiempo usando procesos (CPU): %.3f segundos\n", tiempo);
    return 0;
}
