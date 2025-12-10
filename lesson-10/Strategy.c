#include <stdio.h>

typedef int (*op_func)(int);

/* Estrategias */
int op_doble(int x) {
    return x * 2;
}

int op_suma10(int x) {
    return x + 10;
}

int op_resta5(int x) {
    return x - 5;
}

/* Estrategia nueva */
int op_desc_20(int x) {
    return x - (x * 20 / 100);
}

/* Selector de estrategia */
op_func elegir_op(int tipo) {
    switch (tipo) {
        case 1: return op_doble;
        case 2: return op_suma10;
        case 3: return op_resta5;
        case 4: return op_desc_20;
        default: return op_suma10;
    }
}

int aplicar(op_func f, int valor) {
    return f(valor);
}

int main() {
    int base = 100;

    for (int t = 1; t <= 4; t++) {
        op_func f = elegir_op(t);
        int r = aplicar(f, base);
        printf("Tipo %d -> %d\n", t, r);
    }

    return 0;
}
