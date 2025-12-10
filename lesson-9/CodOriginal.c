#include <stdio.h>

int calcular(int tipo, int a, int b) {
    int r;

    if (tipo == 1) r = a + b;
    else if (tipo == 2) r = a - b;
    else r = 0;

    printf("Resultado: %d\n", r);

    FILE *f = fopen("log.txt", "a");
    fprintf(f, "op %d = %d\n", tipo, r);
    fclose(f);

    return r;
}

int main() {
    calcular(1, 10, 5);
    return 0;
}
