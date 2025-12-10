#include <stdio.h>

typedef int (*op_func)(int, int);

int suma(int a, int b) { return a + b; }
int resta(int a, int b) { return a - b; }
int multi(int a, int b) { return a * b; } // operación nueva

void imprimir(int r) {
    printf("Resultado: %d\n", r);
}

void guardar_log(const char *nombre, int r) {
    FILE *f = fopen("log.txt", "a");
    fprintf(f, "%s = %d\n", nombre, r);
    fclose(f);
}

struct op_entry {
    const char *nombre;
    op_func f;
};

struct op_entry ops[] = {
    {"suma", suma},
    {"resta", resta},
    {"multi", multi}
};

int main() {
    int a = 10, b = 5;

    for (int i = 0; i < 3; i++) {
        int r = ops[i].f(a, b);
        imprimir(r);
        guardar_log(ops[i].nombre, r);
    }

    return 0;
}

#
/*Arreglé dos problemas:

La función hacía todo junto (cálculo, imprimir y escribir archivo). Lo separé en funciones distintas para que sea más fácil de leer.

El código tenía muchos if para elegir la operación. Lo cambié por una tabla con punteros a funciones. Si quiero agregar otra operación, solo agrego una línea más.

Trade-offs:

El código quedó un poco más largo, pero más ordenado.

Usar punteros a funciones en C cuesta un poco al principio, pero evita llenar el código de if.

Añadí también una operación nueva (multiplicación) para mostrar que ahora es fácil extenderlo.*/