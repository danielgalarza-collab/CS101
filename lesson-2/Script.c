#include <stdio.h>

void mostrarBinario(int num) {
    for (int i = 7; i >= 0; i--) {
        int bit = (num >> i) & 1;
        printf("%d", bit);
    }
}

int main() {
    printf("DECIMAL\tBINARIO\t\tHEXADECIMAL\n");
    printf("-------------------------------------\n");

    for (int i = 0; i <= 255; i++) {
        printf("%3d\t", i);
        mostrarBinario(i);
        printf("\t0x%02X\n", i);
    }

    printf("\nPresiona Enter para salir...");
}
