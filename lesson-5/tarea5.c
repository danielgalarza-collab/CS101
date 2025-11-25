
// Compilar: gcc -O2 -std=c11 -o tarea_bigO_corto tarea_bigO_corto.c -lrt
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

static double ahora(){ struct timespec t; clock_gettime(CLOCK_MONOTONIC,&t); return t.tv_sec + t.tv_nsec/1e9; }

/* 1) O(n^2) */
void bucles(size_t n){
    volatile uint64_t acc=0;
    double t0=ahora();
    for(size_t i=0;i<n;++i) for(size_t j=0;j<n;++j) acc += (uint64_t)(i^j);
    printf("bucles: n=%zu tiempo=%.6f s acc=%llu\n", n, ahora()-t0, (unsigned long long)acc);
}

/* 2) O(n) two-pointer sobre array ordenado */
void two_pointer(size_t n){
    int *a = malloc(n*sizeof(int));
    if(!a){ perror("malloc"); return; }
    for(size_t i=0;i<n;++i) a[i]=(int)i;
    size_t l=0, r = n? n-1:0, found=0;
    int target = (int)(n-1);
    double t0=ahora();
    while(l<r){
        int s=a[l]+a[r];
        if(s==target){ ++found; ++l; --r; }
        else if(s<target) ++l;
        else --r;
    }
    printf("two_pointer: n=%zu tiempo=%.6f s pares=%zu\n", n, ahora()-t0, found);
    free(a);
}

/* 3) Tabla hash sencilla (encadenamiento) */
typedef struct N{int k; struct N*nx;}N;
size_t h(int k,size_t b){ uint32_t x=(uint32_t)k; x^=x>>16; x*=0x7feb352d; x^=x>>15; return x%b; }

void hash_ej(size_t n){
    size_t buckets = (n/4)+1;
    N **t = calloc(buckets,sizeof(N*));
    if(!t){ perror("calloc"); return; }
    double t0=ahora();
    for(size_t i=0;i<n;++i){ size_t idx=h((int)i,buckets); N*no=malloc(sizeof(N)); if(!no) continue; no->k=(int)i; no->nx=t[idx]; t[idx]=no; }
    printf("hash_insertar: n=%zu buckets=%zu tiempo=%.6f s\n", n, buckets, ahora()-t0);
    t0=ahora();
    size_t hits=0;
    for(size_t i=0;i<n;++i){
        size_t idx=h((int)i,buckets);
        for(N*cur=t[idx]; cur; cur=cur->nx) if(cur->k==(int)i){ ++hits; break; }
    }
    printf("hash_buscar: n=%zu tiempo=%.6f s hits=%zu\n", n, ahora()-t0, hits);
    for(size_t i=0;i<buckets;++i){ N*cur=t[i]; while(cur){ N*tmp=cur; cur=cur->nx; free(tmp);} }
    free(t);
}

int main(int argc,char**argv){
    size_t n = 10000;
    if(argc>=2) n = (size_t)strtoull(argv[1],NULL,10);
    printf("Ejecutando con n=%zu\n", n);
    bucles(n);
    two_pointer(n);
    hash_ej(n);
    return 0;
}
