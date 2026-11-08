/* traductor.c — Ejercicio 3: traduce palabras reservadas C -> español. */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct { const char *en, *es; } Par;

static const Par DICC[] = {
    {"auto","auto"},        {"break","romper"},       {"case","caso"},
    {"char","caracter"},    {"const","constante"},    {"continue","continuar"},
    {"default","por_defecto"}, {"do","hacer"},        {"double","doble"},
    {"else","sino"},        {"enum","enumeracion"},   {"extern","externo"},
    {"float","flotante"},   {"for","para"},           {"goto","ir_a"},
    {"if","si"},            {"inline","en_linea"},    {"int","entero"},
    {"long","largo"},       {"register","registro"},  {"restrict","restringido"},
    {"return","retornar"},  {"short","corto"},        {"signed","con_signo"},
    {"sizeof","tamano_de"}, {"static","estatico"},    {"struct","estructura"},
    {"switch","segun"},     {"typedef","tipo_def"},   {"union","union"},
    {"unsigned","sin_signo"}, {"void","vacio"},       {"volatile","volatil"},
    {"while","mientras"},
    {"_Alignas","_Alinear"},{"_Alignof","_Alineacion_de"},
    {"_Atomic","_Atomico"}, {"_Bool","_Booleano"},    {"_Complex","_Complejo"},
    {"_Generic","_Generico"},{"_Imaginary","_Imaginario"},
    {"_Noreturn","_SinRetorno"},
    {"_Static_assert","_Verificacion_estatica"},
    {"_Thread_local","_Hilo_local"}
};
#define NDICC (sizeof(DICC)/sizeof(DICC[0]))

/* ---------- Búsqueda ---------- */
static int buscar(const char *s, size_t len)
{
    for (size_t i = 0; i < NDICC; i++)
        if (strlen(DICC[i].en) == len && strncmp(DICC[i].en, s, len) == 0)
            return (int)i;
    return -1;
}

/* ---------- Carga de archivo en memoria dinámica ---------- */
static char *leer_archivo(const char *ruta, size_t *tam)
{
    FILE *f = fopen(ruta, "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buf = (char *)malloc((size_t)sz + 1);
    if (!buf) { fclose(f); return NULL; }

    size_t rd = fread(buf, 1, (size_t)sz, f);
    fclose(f);
    buf[rd] = '\0';
    *tam = rd;
    return buf;
}

/* ---------- Escáner con máquina de estados ---------- */
enum Estado { NORMAL, LINEA, BLOQUE, CADENA, CARACTER };

static void traducir(const char *src, size_t n, FILE *out, unsigned *cuenta)
{
    enum Estado est = NORMAL;

    for (size_t i = 0; i < n; ) {
        char c = src[i];

        switch (est) {
        case NORMAL:
            if (c == '/' && i + 1 < n && src[i+1] == '/') { fputs("//", out); i += 2; est = LINEA; }
            else if (c == '/' && i + 1 < n && src[i+1] == '*') { fputs("/*", out); i += 2; est = BLOQUE; }
            else if (c == '"')  { fputc(c, out); i++; est = CADENA; }
            else if (c == '\'') { fputc(c, out); i++; est = CARACTER; }
            else if (isalpha((unsigned char)c) || c == '_') {
                size_t j = i;
                while (j < n && (isalnum((unsigned char)src[j]) || src[j] == '_')) j++;
                int k = buscar(src + i, j - i);
                if (k >= 0) { fputs(DICC[k].es, out); cuenta[k]++; }
                else        fwrite(src + i, 1, j - i, out);
                i = j;
            }
            else { fputc(c, out); i++; }
            break;

        case LINEA:
            fputc(c, out); i++;
            if (c == '\n') est = NORMAL;
            break;

        case BLOQUE:
            if (c == '*' && i + 1 < n && src[i+1] == '/') { fputs("*/", out); i += 2; est = NORMAL; }
            else { fputc(c, out); i++; }
            break;

        case CADENA:
            fputc(c, out); i++;
            if (c == '\\' && i < n) { fputc(src[i], out); i++; }
            else if (c == '"') est = NORMAL;
            break;

        case CARACTER:
            fputc(c, out); i++;
            if (c == '\\' && i < n) { fputc(src[i], out); i++; }
            else if (c == '\'') est = NORMAL;
            break;
        }
    }
}

int main(int argc, char **argv)
{
    char  *src;
    size_t n;

    if (argc > 1) {
        src = leer_archivo(argv[1], &n);
        if (!src) { fprintf(stderr, "No se pudo abrir '%s'\n", argv[1]); return 1; }
    } else {
        size_t cap = 8192, len = 0;
        src = (char *)malloc(cap);
        if (!src) return 1;
        size_t rd;
        while ((rd = fread(src + len, 1, cap - len, stdin)) > 0) {
            len += rd;
            if (len == cap) { cap *= 2; src = (char *)realloc(src, cap); if (!src) return 1; }
        }
        src[len] = '\0';
        n = len;
    }

    unsigned cuenta[NDICC] = {0};
    traducir(src, n, stdout, cuenta);

    fprintf(stderr, "\n=== Palabras reservadas encontradas y traducidas ===\n");
    int total = 0;
    for (size_t i = 0; i < NDICC; i++) {
        if (cuenta[i]) {
            fprintf(stderr, "  %-16s -> %-22s (%u ocurrencia%s)\n",
                    DICC[i].en, DICC[i].es, cuenta[i], cuenta[i] == 1 ? "" : "s");
            total += (int)cuenta[i];
        }
    }
    if (!total) fprintf(stderr, "  (ninguna)\n");
    else        fprintf(stderr, "  TOTAL: %d\n", total);

    free(src);
    return 0;
}
