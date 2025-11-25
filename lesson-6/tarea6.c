#include <stdio.h>      // printf, perror, FILE, fopen, fscanf, fclose
#include <stdlib.h>     // malloc, free, exit, size_t
#include <string.h>     // memset
#include <unistd.h>     // sysconf
#ifdef __linux__
#include <malloc.h>     // malloc_usable_size en glibc (solo Linux)
#endif

/* Parámetros sencillos para experimentar.
   Pon valores más pequeños si tu máquina tiene poca RAM. */
#define N 50000           // número de objetos "pequeños"
#define SMALL_BYTES 32    // bytes por objeto pequeño

/* Tipo simple que representa el objeto pequeño */
typedef struct {
    char data[SMALL_BYTES];
} Small;

/* Función: lee el RSS (resident set size) en KB desde /proc/self/statm en Linux.
   Si no está en Linux devuelve 0 . */
long get_rss_kb(void) {
#ifdef __linux__
    FILE *f = fopen("/proc/self/statm", "r");    // abrir el archivo con info de memoria
    if (!f) return 0;                           // si falla, devolvemos 0
    long size_pages = 0, rss_pages = 0;         // variables temporales en páginas
    if (fscanf(f, "%ld %ld", &size_pages, &rss_pages) != 2) {
        fclose(f);
        return 0;                               // lectura fallida -> 0
    }
    fclose(f);                                  // cerramos el archivo
    long page_kb = sysconf(_SC_PAGESIZE) / 1024; // tamaño de página en KB
    return rss_pages * page_kb;                 // devolvemos RSS en KB
#else
    (void)0;
    return 0;
#endif
}

/* Función: intenta devolver cuántos bytes realmente reserva malloc
   para un puntero (incluye overhead). Solo en glibc (Linux). */
size_t usable_size(void *p) {
#ifdef __linux__
    if (!p) return 0;
    return malloc_usable_size(p);
#else
    (void)p;
    return 0;
#endif
}

int main(void) {
    /* Mensaje inicial para que el estudiante entienda qué va a pasar */
    printf("=== Comparacion: %d objetos de %d bytes VS 1 bloque de %d*%d bytes ===\n\n",
           N, SMALL_BYTES, N, SMALL_BYTES);

    /* Mostrar el tamaño teórico sin overhead (sizeof) */
    printf("sizeof(Small) = %zu bytes\n", sizeof(Small));
    printf("Tamaño teórico total (sizeof * N) = %zu bytes\n\n",
           sizeof(Small) * (size_t)N);

    /* Medimos RSS antes de cualquier malloc (valor de referencia) */
    long rss_before = get_rss_kb();
    printf("RSS antes de asignar: %ld KB\n", rss_before);

    /* ------------------ MUCHAS ASIGNACIONES PEQUEÑAS ------------------ */

    /* Reservo un array de punteros para guardar cada malloc pequeño */
    Small **arr = malloc((size_t)N * sizeof(Small*));
    if (!arr) { perror("malloc arr"); return 1; }

    /* Hacemos N llamadas a malloc(sizeof(Small)) */
    for (int i = 0; i < N; ++i) {
        arr[i] = malloc(sizeof(Small));        // asigno memoria para cada objeto
        if (!arr[i]) { perror("malloc arr[i]"); return 1; }
        memset(arr[i], 0xAA, sizeof(Small));   // "toco" la memoria para mapear páginas
    }

    /* Medimos RSS después de las muchas asignaciones pequeñas */
    long rss_after_small = get_rss_kb();
    printf("RSS después de %d mallocs pequeños: %ld KB (diferencia: %ld KB)\n",
           N, rss_after_small, rss_after_small - rss_before);

    /* Sumamos el usable_size (si está disponible) para ver overhead real */
    size_t total_usable_small = 0;
    for (int i = 0; i < N; ++i) {
        size_t u = usable_size(arr[i]);               // bytes realmente reservados por malloc
        total_usable_small += (u ? u : sizeof(Small));
    }
    printf("Suma usable_size (o sizeof si no disponible) de los pequeños: %zu bytes\n\n",
           total_usable_small);

    /* Liberamos todos los objetos pequeños */
    for (int i = 0; i < N; ++i) {
        free(arr[i]);
        arr[i] = NULL;    // buena práctica para evitar punteros colgantes
    }

    /* Medimos RSS después de liberar los pequeños */
    long rss_after_free_small = get_rss_kb();
    printf("RSS tras free() de los pequeños: %ld KB (diferencia: %ld KB)\n\n",
           rss_after_free_small, rss_after_free_small - rss_before);

    /*UN UNICO BLOQUE GRANDE */

    /* Asignamos un bloque contiguo grande de N * sizeof(Small) */
    Small *big = malloc((size_t)N * sizeof(Small));
    if (!big) { perror("malloc big"); free(arr); return 1; }

    /* Tocamos la memoria para forzar su mapeo físico */
    memset(big, 0xBB, (size_t)N * sizeof(Small));

    /* Medimos RSS tras el malloc grande */
    long rss_after_big = get_rss_kb();
    printf("RSS después de malloc grande: %ld KB (diferencia: %ld KB)\n",
           rss_after_big, rss_after_big - rss_before);

    /* Mostramos usable_size del bloque grande si está disponible */
    size_t usable_big = usable_size(big);
    printf("malloc_usable_size (bloque grande): %zu bytes\n", usable_big);
    printf("Tamaño teórico bloque grande (sizeof * N): %zu bytes\n\n",
           sizeof(Small) * (size_t)N);

    /* Limpiamos todo antes de salir */
    free(big);
    free(arr);

    long rss_end = get_rss_kb();
    printf("RSS final tras liberar todo: %ld KB (puede no bajar exactamente al inicial)\n", rss_end);

    return 0;
}