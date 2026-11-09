#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Función para generar los coeficientes con memoria dinámica
double* generar_coeficientes(int n) {
    // Uso obligatorio de memoria dinámica según el enunciado
    double* coef = (double*)malloc((n + 1) * sizeof(double));
    if (coef == NULL) {
        printf("Error asignando memoria.\n");
        exit(1);
    }
    
    coef[0] = 1;
    for (int i = 1; i <= n; i++) {
        coef[i] = 1;
        for (int j = i - 1; j > 0; j--) {
            coef[j] = coef[j] + coef[j - 1];
        }
    }
    return coef;
}

// a) Función para mostrar el polinomio generado
void mostrar_polinomio(int n, double* coef) {
    printf("\na) Polinomio generado:\n(x+1)^%d = ", n);
    for (int i = 0; i <= n; i++) {
        int exponente = n - i;
        if (coef[i] != 1 || exponente == 0) {
            printf("%.0f", coef[i]);
        }
        if (exponente > 0) {
            printf("x");
            if (exponente > 1) {
                printf("^%d", exponente);
            }
        }
        if (i < n) printf(" + ");
    }
    printf("\n");
}

// b) Función para mostrar el cálculo paso a paso
void calcular_paso_a_paso(int n, double* coef, double x) {
    printf("\nb) Calculo paso a paso para f(%.2f) = (%.2f+1)^%d:\n", x, x, n);
    
    // Paso 1: Sustitución
    printf("1. Sustituyendo x: \nf(%.2f) = ", x);
    for (int i = 0; i <= n; i++) {
        int exponente = n - i;
        if (exponente == 0) {
            printf("%.0f", coef[i]);
        } else {
            printf("%.0f*(%.2f)^%d", coef[i], x, exponente);
        }
        if (i < n) printf(" + ");
    }
    printf("\n\n");

    // Paso 2: Resolución de potencias
    printf("2. Resolviendo potencias: \nf(%.2f) = ", x);
    for (int i = 0; i <= n; i++) {
        int exponente = n - i;
        if (exponente == 0) {
            printf("%.0f", coef[i]);
        } else {
            printf("%.0f*(%.2f)", coef[i], pow(x, exponente));
        }
        if (i < n) printf(" + ");
    }
    printf("\n\n");

    // Paso 3: Multiplicación y suma final
    double total = 0;
    printf("3. Multiplicando terminos: \nf(%.2f) = ", x);
    for (int i = 0; i <= n; i++) {
        int exponente = n - i;
        double termino = coef[i] * pow(x, exponente);
        total += termino;
        printf("%.2f", termino);
        if (i < n) printf(" + ");
    }
    printf("\n\nResultado final: %.2f\n", total);
}

int main() {
    int n;
    double x;

    printf("--- GENERADOR DE POLINOMIOS (TRIANGULO DE PASCAL) ---\n");
    printf("Ingrese el valor de n (entero no negativo): ");
    scanf("%d", &n);
    
    // Generar coeficientes con memoria dinámica
    double* coeficientes = generar_coeficientes(n);
    
    // Mostrar polinomio
    mostrar_polinomio(n, coeficientes);

    printf("\nIngrese el valor de x para el calculo: ");
    scanf("%lf", &x);

    // Mostrar pasos
    calcular_paso_a_paso(n, coeficientes, x);

    // Liberar la memoria dinámica una vez finalizado su uso
    free(coeficientes);

    // Prueba de rendimiento solicitada para n=100 (con 10,000 iteraciones para ver decimales reales)
    printf("\n--- PRUEBA DE RENDIMIENTO EN C (n=100 x 10000 iteraciones) ---\n");
    clock_t inicio = clock();
    
    for (int rep = 0; rep < 10000; rep++) {
        double* coef_100 = generar_coeficientes(100);
        free(coef_100);
    }
    
    clock_t fin = clock();
    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    
    printf("Tiempo total para 10,000 ejecuciones de n=100: %f segundos.\n", tiempo);

    return 0;
}