/* caballo.c — Prueba Diagnóstica LYC 2026-II — Ejercicio 1
 * Valida una secuencia de movimientos de caballo sobre un tablero 8x8.
 */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct { int col; int row; } Pos;

typedef struct {
    int         ok;
    int         fallo;
    char        letraMala;
    const char *motivo;
} Resultado;

/* ---------- Validación geométrica ---------- */
static int es_mov_caballo(Pos a, Pos b)
{
    int dc = abs(a.col - b.col);
    int dr = abs(a.row - b.row);
    return (dc == 1 && dr == 2) || (dc == 2 && dr == 1);
}

/* ---------- Parseo de "a1" ---------- */
static int parse_pos(const char *s, Pos *p)
{
    if (!s || strlen(s) != 2) return -1;
    char c = (char)tolower((unsigned char)s[0]);
    if (c < 'a' || c > 'h') return -1;
    if (s[1] < '1' || s[1] > '8') return -1;
    p->col = c - 'a';
    p->row = s[1] - '1';
    return 0;
}

/* ---------- Parseo de "Kc2" ---------- */
static int parse_mov(const char *t, Pos *p, char *bad)
{
    size_t n = strlen(t);
    if (n < 3) { *bad = t[0] ? t[0] : '?'; return 4; }
    if (t[0] != 'K') { *bad = t[0]; return 1; }

    char c = (char)tolower((unsigned char)t[1]);
    if (c < 'a' || c > 'h') { *bad = t[1]; return 2; }
    if (t[2] < '1' || t[2] > '8') { *bad = t[2]; return 3; }
    if (t[3] != '\0') { *bad = t[3]; return 4; }

    p->col = c - 'a';
    p->row = t[2] - '1';
    return 0;
}

/* ---------- Validación completa de la cadena ---------- */
static Resultado validar_cadena(Pos actual, const char *cadena, int nEsperado)
{
    Resultado r = { 1, 0, 0, NULL };

    size_t len  = strlen(cadena);
    char  *copia = (char *)malloc(len + 1);
    if (!copia) { r.ok = 0; r.motivo = "sin memoria"; return r; }
    memcpy(copia, cadena, len + 1);

    int idx = 0;
    for (char *tok = strtok(copia, " \t\r\n"); tok; tok = strtok(NULL, " \t\r\n")) {
        idx++;
        Pos  destino;
        char bad = 0;
        int  pr  = parse_mov(tok, &destino, &bad);

        if (pr != 0) {
            r.ok = 0; r.fallo = idx; r.letraMala = bad;
            r.motivo = (pr == 1) ? "letra inicial no pertenece a un caballo"
                     : (pr == 2) ? "columna fuera del tablero (a..h)"
                     : (pr == 3) ? "fila fuera del tablero (1..8)"
                                 : "formato de movimiento invalido";
            break;
        }
        if (!es_mov_caballo(actual, destino)) {
            r.ok = 0; r.fallo = idx;
            r.motivo = "movimiento no es de caballo";
            break;
        }
        actual = destino;
    }

    if (r.ok && nEsperado > 0 && idx != nEsperado) {
        r.ok = 0; r.fallo = idx + 1;
        r.motivo = "cantidad de movimientos no coincide con n";
    }

    free(copia);
    return r;
}

static void imprimir_resultado(const Resultado *r)
{
    if (r->ok) { puts("movimiento CORRECTO."); return; }

    if (r->letraMala)
        printf("movimiento INCORRECTO falla en el movimiento %d: letra '%c' no pertenece a un caballo.\n",
               r->fallo, r->letraMala);
    else
        printf("movimiento INCORRECTO falla en el movimiento %d. (%s)\n",
               r->fallo, r->motivo ? r->motivo : "");
}

/* ---------- Entrada interactiva ---------- */
static char *leer_linea(void)
{
    char  *linea = NULL;
    size_t cap   = 0;
    ssize_t n    = getline(&linea, &cap, stdin);
    if (n < 0) { free(linea); return NULL; }
    while (n > 0 && (linea[n-1] == '\n' || linea[n-1] == '\r')) linea[--n] = '\0';
    return linea;
}

static const char MOVS_500[] =
"Kb4 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 "
"Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 "
"Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 "
"Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 "
"Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 "
"Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 "
"Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 "
"Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 "
"Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 "
"Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 "
"Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 "
"Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 "
"Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 "
"Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 "
"Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 "
"Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 "
"Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 "
"Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 "
"Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 "
"Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 "
"Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 "
"Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 "
"Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 "
"Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4";

/* ---------- Benchmark ---------- */
static int contar_movimientos(const char *s)
{
    int c = 0, en = 0;
    for (; *s; s++) {
        if (isspace((unsigned char)*s)) en = 0;
        else if (!en) { en = 1; c++; }
    }
    return c;
}

static void bench(void)
{
    const int REP = 10;
    Pos ini = { 0, 1 };
    int total = contar_movimientos(MOVS_500);

    Resultado pre = validar_cadena(ini, MOVS_500, 0);

    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    for (int r = 0; r < REP; r++) (void)validar_cadena(ini, MOVS_500, 0);
    clock_gettime(CLOCK_MONOTONIC, &t1);

    double total_s = (double)(t1.tv_sec - t0.tv_sec)
                   + (double)(t1.tv_nsec - t0.tv_nsec) / 1e9;

    printf("=== BENCHMARK ===\n");
    printf("Cadena analizada      : %d movimientos\n", total);
    printf("Resultado previo      : %s", pre.ok ? "CORRECTO" : "INCORRECTO");
    if (!pre.ok) printf(" (falla en el mov. %d)", pre.fallo);
    printf("\n");
    printf("Repeticiones          : %d\n", REP);
    printf("Tiempo total          : %.9f s\n", total_s);
    printf("Tiempo por corrida    : %.9f s\n", total_s / REP);
    printf("Tiempo por movimiento : %.9f s\n", total_s / (REP * (double)total));
}

int main(int argc, char **argv)
{
    if (argc > 1 && strcmp(argv[1], "--bench") == 0) { bench(); return 0; }

    printf("Posicion inicial (Ak, ej. a1): ");
    char *ak = leer_linea();
    if (!ak) return 1;

    Pos ini;
    if (parse_pos(ak, &ini) != 0) { fprintf(stderr, "Posicion inicial invalida.\n"); free(ak); return 1; }
    free(ak);

    printf("n (numero de movimientos): ");
    char *ns = leer_linea();
    if (!ns) return 1;
    int n = atoi(ns);
    free(ns);

    printf("Cadena C (ej. Kc2 Kd4 Kb3 Kc5): ");
    char *c = leer_linea();
    if (!c) return 1;

    Resultado r = validar_cadena(ini, c, n);
    imprimir_resultado(&r);

    free(c);
    return 0;
}
