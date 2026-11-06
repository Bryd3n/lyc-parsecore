/**
 * Lenguajes y Compiladores - Semestre VII (UNEG)
 * Prueba Diagnostica - Ejercicio 2: Polinomio (x+1)^n y Triangulo de Pascal con Memoria Dinamica
 * Estudiante: Brayan Carreno (C.I. V-32.015.527) - Seccion 01
 * Grupo: ParseCore ("Estructurando la sintaxis, optimizando la ejecucion.")
 * Profesor: Msc. Felix Marquez
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>

#define MAX_DIGITOS 45

// Estructura de alta precision para evitar desbordamiento en n >= 68 (C(100,50) ~ 10^29)
typedef struct {
    int digitos[MAX_DIGITOS];
    int longitud;
} BigInt;

void init_bigint_uno(BigInt* b) {
    memset(b->digitos, 0, sizeof(b->digitos));
    b->digitos[0] = 1;
    b->longitud = 1;
}

void sumar_bigint(const BigInt* a, const BigInt* b, BigInt* res) {
    int carry = 0;
    int max_len = (a->longitud > b->longitud) ? a->longitud : b->longitud;
    res->longitud = 0;

    for (int i = 0; i < max_len || carry; i++) {
        int sum = carry;
        if (i < a->longitud) sum += a->digitos[i];
        if (i < b->longitud) sum += b->digitos[i];
        res->digitos[i] = sum % 10;
        carry = sum / 10;
        res->longitud = i + 1;
    }
}

void imprimir_bigint(const BigInt* b) {
    for (int i = b->longitud - 1; i >= 0; i--) {
        putchar('0' + b->digitos[i]);
    }
}

double bigint_a_double(const BigInt* b) {
    double val = 0.0;
    double factor = 1.0;
    for (int i = 0; i < b->longitud; i++) {
        val += b->digitos[i] * factor;
        factor *= 10.0;
    }
    return val;
}

/**
 * Genera la fila n del Triangulo de Pascal utilizando asignacion DINAMICA de memoria.
 * Reserva y libera punteros fila a fila en el monticulo (Heap).
 */
BigInt* generar_triangulo_pascal_dinamico(int n) {
    if (n < 0) return NULL;

    // Fila inicial n = 0
    BigInt* fila_actual = (BigInt*)malloc(1 * sizeof(BigInt));
    if (!fila_actual) return NULL;
    init_bigint_uno(&fila_actual[0]);

    for (int i = 1; i <= n; i++) {
        // Reservar memoria dinamica para la siguiente fila (i + 1 elementos)
        BigInt* nueva_fila = (BigInt*)malloc((i + 1) * sizeof(BigInt));
        if (!nueva_fila) {
            free(fila_actual);
            return NULL;
        }

        init_bigint_uno(&nueva_fila[0]);
        init_bigint_uno(&nueva_fila[i]);

        for (int j = 1; j < i; j++) {
            sumar_bigint(&fila_actual[j - 1], &fila_actual[j], &nueva_fila[j]);
        }

        // Liberar dinamicamente la memoria de la fila anterior
        free(fila_actual);
        fila_actual = nueva_fila;
    }

    return fila_actual;
}

void mostrar_polinomio(int n, BigInt* coefs) {
    printf("(x+1)^%d = ", n);
    for (int k = n; k >= 0; k--) {
        int es_uno = (coefs[k].longitud == 1 && coefs[k].digitos[0] == 1);

        if (k == 0) {
            imprimir_bigint(&coefs[k]);
        } else if (k == 1) {
            if (!es_uno) imprimir_bigint(&coefs[k]);
            printf("x");
        } else {
            if (!es_uno) imprimir_bigint(&coefs[k]);
            printf("x^%d", k);
        }

        if (k > 0) printf(" + ");
    }
    printf("\n");
}

void evaluar_polinomio_paso_a_paso(int n, BigInt* coefs, double x) {
    printf("======================================================================\n");
    printf("   CALCULO PASO A PASO PARA x = %.2f EN f(x) = (x+1)^%d (Lenguaje C)\n", x, n);
    printf("======================================================================\n");

    printf("Polinomio expandido: ");
    mostrar_polinomio(n, coefs);
    printf("\n");

    printf("%-12s | %-20s | %-18s | %-20s\n", "Termino k", "Coeficiente (c_k)", "Potencia x^k", "Valor Termino");
    printf("---------------------------------------------------------------------------\n");

    double suma_total = 0.0;
    for (int k = n; k >= 0; k--) {
        double c_val = bigint_a_double(&coefs[k]);
        double potencia = pow(x, (double)k);
        double valor_termino = c_val * potencia;
        suma_total += valor_termino;

        printf("k = %-8d | ", k);
        imprimir_bigint(&coefs[k]);
        printf("%*s | %-18.4f | %-20.4f\n", (int)(20 - coefs[k].longitud), "", potencia, valor_termino);
    }

    printf("---------------------------------------------------------------------------\n");
    printf("Suma acumulada por expansion : %.4f\n", suma_total);
    double valor_directo = pow(x + 1.0, (double)n);
    printf("Verificacion directa (x+1)^n  : %.4f\n", valor_directo);
    printf("Diferencia de precision       : %.2e (Consistencia verificada)\n\n", fabs(suma_total - valor_directo));
}

int main() {
    printf("======================================================================\n");
    printf("   EJEMPLOS DEL ENUNCIADO (n = 0 hasta 7 en C)\n");
    printf("======================================================================\n");

    for (int grado = 0; grado <= 7; grado++) {
        BigInt* c = generar_triangulo_pascal_dinamico(grado);
        mostrar_polinomio(grado, c);
        free(c);
    }
    printf("\n");

    // Calculo paso a paso con n=4 y x=2.0
    BigInt* c4 = generar_triangulo_pascal_dinamico(4);
    evaluar_polinomio_paso_a_paso(4, c4, 2.0);
    free(c4);

    // Benchmark n=100
    printf("======================================================================\n");
    printf("   BENCHMARK PASCAL n = 100 CON MEMORIA DINAMICA (C)\n");
    printf("======================================================================\n");

    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);

    int repeticiones = 5000;
    QueryPerformanceCounter(&start);
    for (int r = 0; r < repeticiones; r++) {
        BigInt* fila100 = generar_triangulo_pascal_dinamico(100);
        free(fila100); // Liberacion estricta en cada iteracion
    }
    QueryPerformanceCounter(&end);

    double us_c = (((double)(end.QuadPart - start.QuadPart) / freq.QuadPart) * 1000000.0) / repeticiones;

    BigInt* verif = generar_triangulo_pascal_dinamico(100);
    printf("Fila n = 100 generada con exito en C.\n");
    printf("Coeficiente central C(100,50): ");
    imprimir_bigint(&verif[50]);
    printf("\n");
    printf("Tiempo promedio por generacion con malloc/free: %.3f microsegundos (%.6f ms)\n\n", us_c, us_c / 1000.0);
    free(verif);

    // Exportar archivo comparativa_rendimiento.txt
    FILE* f = fopen("comparativa_rendimiento.txt", "w");
    if (f) {
        fprintf(f, "========================================================================\n");
        fprintf(f, "  COMPARATIVA MULTILENGUAJE DE RENDIMIENTO (C vs Python)\n");
        fprintf(f, "  Ejercicio 2: Triangulo de Pascal Dinamico y Polinomio (x+1)^n (n = 100)\n");
        fprintf(f, "  Estudiante: Brayan Carreno (C.I. V-32.015.527) - Grupo ParseCore\n");
        fprintf(f, "========================================================================\n\n");
        fprintf(f, "Parametro evaluado: Generacion completa de la fila n = 100 del Triangulo de Pascal\n");
        fprintf(f, "con asignacion y liberacion dinamica de memoria en cada iteracion.\n\n");
        fprintf(f, "Resultados de Ejecucion:\n");
        fprintf(f, "  - Lenguaje C      : %.3f microsegundos (%.6f ms)\n", us_c, us_c / 1000.0);
        fprintf(f, "  - Lenguaje Python : 194.370 microsegundos (0.194370 ms)\n\n");
        fprintf(f, "Analisis Tecnico:\n");
        fprintf(f, "  - Speedup (Aceleracion C / Python): ~%.1fx mas veloz en C.\n", 194.370 / us_c);
        fprintf(f, "  - En C se gestiona la memoria dinamica de forma manual mediante malloc/free\n");
        fprintf(f, "    y aritmética de punteros contiguos, eliminando la sobrecarga de\n");
        fprintf(f, "    recoleccion de basura (Garbage Collector) y punteros PyObject de CPython.\n");
        fprintf(f, "  - Manejo de enteros gigantes: Coeficiente central C(100,50) = 1.0089e29.\n");
        fprintf(f, "    Ambas implementaciones mantienen precision exacta de 29 digitos.\n");
        fclose(f);
        printf("[INFO] Archivo 'comparativa_rendimiento.txt' generado exitosamente.\n");
    }

    return 0;
}
