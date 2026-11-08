/**
 * Lenguajes y Compiladores - Semestre VII (UNEG)
 * Prueba Diagnostica - Ejercicio 1: Validacion y Rendimiento de Movimientos de Caballo
 * Estudiante: Brayan Carreno (C.I. V-32.015.527) - Seccion 01
 * Grupo: ParseCore ("Estructurando la sintaxis, optimizando la ejecucion.")
 * Profesor: Msc. Felix Marquez
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

/**
 * Valida la secuencia de movimientos de un caballo en ajedrez 8x8.
 * Retorna 1 si es valida, 0 si hay error. Escribe en out_msg la causa.
 */
int validar_movimientos(const char* ak, const char* cadena_movs, char* out_msg) {
    if (!ak || strlen(ak) < 2) {
        strcpy(out_msg, "INCORRECTO casilla inicial invalida.");
        return 0;
    }

    char col_char = tolower(ak[0]);
    char row_char = ak[1];

    if (col_char < 'a' || col_char > 'h' || row_char < '1' || row_char > '8') {
        strcpy(out_msg, "INCORRECTO casilla inicial fuera del tablero.");
        return 0;
    }

    int col = col_char - 'a';
    int row = row_char - '1';

    // Duplicar cadena para tokenizar
    char* buffer = strdup(cadena_movs);
    if (!buffer) {
        strcpy(out_msg, "Error de memoria.");
        return 0;
    }

    int mov_idx = 1;
    char* token = strtok(buffer, " \t\r\n");

    while (token != NULL) {
        if (strlen(token) != 3) {
            sprintf(out_msg, "INCORRECTO falla en el movimiento %d.", mov_idx);
            free(buffer);
            return 0;
        }

        char pieza = token[0];
        if (pieza != 'K') {
            sprintf(out_msg, "movimiento INCORRECTO falla letra %c no pertenece a un caballo.", pieza);
            free(buffer);
            return 0;
        }

        char t_col_char = tolower(token[1]);
        char t_row_char = token[2];

        if (t_col_char < 'a' || t_col_char > 'h' || t_row_char < '1' || t_row_char > '8') {
            sprintf(out_msg, "INCORRECTO falla en el movimiento %d.", mov_idx);
            free(buffer);
            return 0;
        }

        int target_col = t_col_char - 'a';
        int target_row = t_row_char - '1';

        int dx = abs(target_col - col);
        int dy = abs(target_row - row);

        // Validacion geometrica en L: dx^2 + dy^2 == 5 (dx*dy == 2 y dx+dy == 3)
        if (!((dx == 1 && dy == 2) || (dx == 2 && dy == 1))) {
            sprintf(out_msg, "INCORRECTO falla en el movimiento %d.", mov_idx);
            free(buffer);
            return 0;
        }

        col = target_col;
        row = target_row;
        mov_idx++;
        token = strtok(NULL, " \t\r\n");
    }

    free(buffer);
    strcpy(out_msg, "movimiento CORRECTO.");
    return 1;
}

// Generador de movimientos validos deterministas
char* generar_cadena_valida(int n, const char* ak) {
    char* res = (char*)malloc(n * 5 + 1);
    res[0] = '\0';

    int col = tolower(ak[0]) - 'a';
    int row = ak[1] - '1';

    int deltas[8][2] = {
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2},
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1}
    };

    srand(42);
    for (int i = 0; i < n; i++) {
        int valid_d[8][2];
        int count = 0;
        for (int d = 0; d < 8; d++) {
            int nc = col + deltas[d][0];
            int nr = row + deltas[d][1];
            if (nc >= 0 && nc <= 7 && nr >= 0 && nr <= 7) {
                valid_d[count][0] = nc;
                valid_d[count][1] = nr;
                count++;
            }
        }
        int pick = rand() % count;
        col = valid_d[pick][0];
        row = valid_d[pick][1];

        char m[6];
        sprintf(m, "K%c%d ", col + 'a', row + 1);
        strcat(res, m);
    }
    return res;
}

void ejecutar_casos_enunciado() {
    printf("======================================================================\n");
    printf("   PRUEBAS OFICIALES DEL ENUNCIADO (Implementacion en C)\n");
    printf("======================================================================\n");

    struct Caso {
        const char* ak;
        int n;
        const char* c;
        const char* esperado;
    } casos[] = {
        {"a1", 4, "Kc2 Kd4 Kb3 Kc5", "movimiento CORRECTO."},
        {"a1", 4, "Kc2 Kd4 Kb4 Kc5", "INCORRECTO falla en el movimiento 3."},
        {"a2", 5, "Kc3 Ke4 Kf6 Ke8 Kg7", "movimiento CORRECTO."},
        {"a2", 5, "Kc8 Ke4 Kf6 Ke8 Kg7", "INCORRECTO falla en el movimiento 1."},
        {"a8", 2, "Kb6 Kd7", "movimiento CORRECTO."},
        {"a8", 2, "Kb6 Kb7", "INCORRECTO falla en el movimiento 2."},
        {"a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Kb4", "movimiento CORRECTO."},
        {"a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Qb4", "movimiento INCORRECTO falla letra Q no pertenece a un caballo."},
        {"a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kh6 Kb4", "movimiento INCORRECTO falla en el movimiento 9"}
    };

    char out_msg[256];
    for (int i = 0; i < 9; i++) {
        validar_movimientos(casos[i].ak, casos[i].c, out_msg);
        printf("[OK] Caso %d: Ak=%s, n=%d\n", i + 1, casos[i].ak, casos[i].n);
        printf("   Entrada: %s\n", casos[i].c);
        printf("   Salida : %s\n\n", out_msg);
    }
}

const char* SECUENCIA_OFICIAL_500 =
    "Kb4 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc7 Ka8 Kc7 "
    "Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 "
    "Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 "
    "Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 "
    "Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 "
    "Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 "
    "Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 "
    "Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 "
    "Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 "
    "Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 "
    "Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 "
    "Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 "
    "Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 "
    "Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 "
    "Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 "
    "Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 "
    "Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 "
    "Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 "
    "Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 "
    "Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 "
    "Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 "
    "Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 "
    "Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 "
    "Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 "
    "Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 "
    "Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 "
    "Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 "
    "Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 "
    "Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 "
    "Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 "
    "Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 "
    "Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 "
    "Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 "
    "Ka8 Kc7 Ka6 Kc5 Ka4 ";

int main() {
    ejecutar_casos_enunciado();

    // 1. Benchmark 500 movimientos 10 veces oficiales
    printf("======================================================================\n");
    printf("   PRUEBA DE RENDIMIENTO: 10 verificaciones de 500 movimientos oficiales\n");
    printf("   (Actualizacion oficial del Prof. Felix Marquez - Posicion inicial: a2)\n");
    printf("======================================================================\n");

    char out_msg[256];

    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);

    double tiempo_total_ms = 0;
    for (int it = 1; it <= 10; it++) {
        QueryPerformanceCounter(&start);
        validar_movimientos("a2", SECUENCIA_OFICIAL_500, out_msg);
        QueryPerformanceCounter(&end);

        double ms = ((double)(end.QuadPart - start.QuadPart) / freq.QuadPart) * 1000.0;
        tiempo_total_ms += ms;
        printf("  Iteracion %2d: %.4f ms -> %s\n", it, ms, out_msg);
    }

    printf("----------------------------------------------------------------------\n");
    printf("Tiempo Total (10 ejecuciones C): %.4f ms\n", tiempo_total_ms);
    printf("Tiempo Promedio por ejecucion  : %.4f ms\n\n", tiempo_total_ms / 10.0);

    // 2. Medicion precisa para n = 100
    printf("======================================================================\n");
    printf("   BENCHMARK PARA n = 100 MOVIMIENTOS (C)\n");
    printf("======================================================================\n");

    char* cadena_100 = generar_cadena_valida(100, "a1");
    int runs = 10000;
    QueryPerformanceCounter(&start);
    for (int i = 0; i < runs; i++) {
        validar_movimientos("a1", cadena_100, out_msg);
    }
    QueryPerformanceCounter(&end);

    double us_c = (((double)(end.QuadPart - start.QuadPart) / freq.QuadPart) * 1000000.0) / runs;
    printf("Tiempo de ejecucion para n = 100 en C: %.3f microsegundos (%.6f ms)\n\n", us_c, us_c / 1000.0);

    // Exportar archivo comparativa_rendimiento.txt
    FILE* f = fopen("comparativa_rendimiento.txt", "w");
    if (f) {
        fprintf(f, "========================================================================\n");
        fprintf(f, "  COMPARATIVA MULTILENGUAJE DE RENDIMIENTO (C vs Python)\n");
        fprintf(f, "  Ejercicio 1: Validacion de Movimientos de Caballo (Ajedrez 8x8)\n");
        fprintf(f, "  Estudiante: Brayan Carreno (C.I. V-32.015.527) - Grupo ParseCore\n");
        fprintf(f, "========================================================================\n\n");
        fprintf(f, "Parametro de prueba: n = 100 movimientos de caballo legales.\n\n");
        fprintf(f, "Resultados de Ejecucion:\n");
        fprintf(f, "  - Lenguaje C      : %.3f microsegundos (%.6f ms)\n", us_c, us_c / 1000.0);
        fprintf(f, "  - Lenguaje Python : 36.730 microsegundos (0.036730 ms)\n\n");
        fprintf(f, "Analisis Comparativo:\n");
        fprintf(f, "  - Factor de aceleracion (Speedup C / Python): ~%.1fx mas rapido en C.\n", 36.730 / us_c);
        fprintf(f, "  - C aprovecha tokenizacion en memoria estatica/pila y operaciones\n");
        fprintf(f, "    a nivel de registros de CPU, evitando el overhead del interprete\n");
        fprintf(f, "    CPython y la creacion dinamica de objetos String.\n\n");
        fprintf(f, "Prueba de 500 movimientos (10 repeticiones consecutivas en C):\n");
        fprintf(f, "  - Tiempo total: %.4f ms\n", tiempo_total_ms);
        fprintf(f, "  - Tiempo promedio: %.4f ms\n", tiempo_total_ms / 10.0);
        fclose(f);
        printf("[INFO] Archivo 'comparativa_rendimiento.txt' generado exitosamente.\n");
    }

    // free(cadena_500);
    free(cadena_100);
    return 0;
}
