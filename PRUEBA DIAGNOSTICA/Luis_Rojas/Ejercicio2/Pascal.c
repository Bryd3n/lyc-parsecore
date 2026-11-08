/* pascal.c — Ejercicio 2: (x+1)^n con Triángulo de Pascal y memoria dinámica. */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef unsigned __int128 u128;

/* ---------- Impresión de u128 ---------- */
static void imprimir_u128(u128 v)
{
    if (v == 0) { putchar('0'); return; }
    char buf[64];
    int  i = 0;
    while (v > 0) { buf[i++] = (char)('0' + (int)(v % 10)); v /= 10; }
    while (i--) putchar(buf[i]);
}

/* ---------- Fila n del triángulo (memoria dinámica) ---------- */
static u128 *fila_pascal(int n)
{
    u128 *fila = (u128 *)malloc((size_t)(n + 1) * sizeof(u128));
    if (!fila) return NULL;
    fila[0] = 1;
    for (int i = 1; i <= n; i++) {
        fila[i] = 1;
        for (int j = i - 1; j >= 1; j--)
            fila[j] = fila[j] + fila[j - 1];
    }
    return fila;
}

/* ---------- Mostrar polinomio ---------- */
static void mostrar_polinomio(const u128 *c, int n)
{
    printf("(x+1)^%d = ", n);
    for (int k = 0; k <= n; k++) {
        int e = n - k;
        if (k > 0) printf(" + ");
        if (c[k] != 1 || e == 0) imprimir_u128(c[k]);
        if (e >= 1) putchar('x');
        if (e >= 2) printf("^%d", e);
    }
    putchar('\n');
}

/* ---------- Evaluación paso a paso ---------- */
static void evaluar_con_pasos(const u128 *c, int n, long long x)
{
    printf("f(%lld) = (x+1)^%d\n     = ", x, n);
    for (int k = 0; k <= n; k++) {
        int e = n - k;
        if (k) printf(" + ");
        imprimir_u128(c[k]);
        printf("*%lld^%d", x, e);
    }
    printf("\n     = ");

    u128 total = 0;
    for (int k = 0; k <= n; k++) {
        int  e  = n - k;
        u128 p  = 1;
        for (int t = 0; t < e; t++) p *= (u128)x;
        u128 v = c[k] * p;
        total += v;
        if (k) printf(" + ");
        imprimir_u128(v);
    }
    printf("\n     = ");
    imprimir_u128(total);
    putchar('\n');
}

/* ---------- Benchmark ---------- */
static void bench(void)
{
    const int ITERS = 100, N = 100;
    struct timespec t0, t1;

    clock_gettime(CLOCK_MONOTONIC, &t0);
    u128 control = 0;
    for (int r = 0; r < ITERS; r++) {
        u128 *f = fila_pascal(N);
        if (!f) { fprintf(stderr, "sin memoria\n"); return; }
        if (r == ITERS - 1) control = f[N / 2] % 1000;
        free(f);
    }
    clock_gettime(CLOCK_MONOTONIC, &t1);

    double dt = (double)(t1.tv_sec - t0.tv_sec)
              + (double)(t1.tv_nsec - t0.tv_nsec) / 1e9;

    printf("C      — n=%d, %d ejecuciones\n", N, ITERS);
    printf("  Tiempo total : %.6f s\n", dt);
    printf("  Por ejecucion: %.6f s\n", dt / ITERS);
    printf("  Digito control (coef central) = ");
    imprimir_u128(control);
    putchar('\n');
}

int main(int argc, char **argv)
{
    if (argc > 1 && strcmp(argv[1], "--bench") == 0) { bench(); return 0; }

    int n = (argc > 1) ? atoi(argv[1]) : 5;
    long long x = (argc > 2) ? atoll(argv[2]) : 2;
    if (n < 0) { fprintf(stderr, "n debe ser >= 0\n"); return 1; }

    u128 *c = fila_pascal(n);
    if (!c) { fprintf(stderr, "sin memoria\n"); return 1; }

    mostrar_polinomio(c, n);
    putchar('\n');
    evaluar_con_pasos(c, n, x);

    free(c);
    return 0;
}
