/**
 * Lenguajes y Compiladores - Semestre VII (UNEG)
 * Prueba Diagnostica - Ejercicio 3: Analizador Lexico Basico (Traductor de C a Espanol)
 * Estudiante: Brayan Carreno (C.I. V-32.015.527) - Seccion 01
 * Grupo: ParseCore ("Estructurando la sintaxis, optimizando la ejecucion.")
 * Profesor: Msc. Felix Marquez
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Tabla de Palabras Reservadas en C y sus equivalentes en Espanol
typedef struct {
    const char* c_keyword;
    const char* es_keyword;
    int conteo;
} Traduccion;

static Traduccion TABLA_RESERVADAS[] = {
    {"if", "si", 0},
    {"else", "sino", 0},
    {"while", "mientras", 0},
    {"for", "para", 0},
    {"do", "hacer", 0},
    {"int", "entero", 0},
    {"float", "flotante", 0},
    {"char", "caracter", 0},
    {"double", "doble", 0},
    {"void", "vacio", 0},
    {"return", "retornar", 0},
    {"struct", "estructura", 0},
    {"typedef", "definir_tipo", 0},
    {"switch", "segun", 0},
    {"case", "caso", 0},
    {"break", "romper", 0},
    {"continue", "continuar", 0},
    {"default", "defecto", 0},
    {"sizeof", "tamano_de", 0},
    {"const", "constante", 0},
    {"static", "estatico", 0},
    {"unsigned", "sin_signo", 0},
    {"signed", "con_signo", 0},
    {"long", "largo", 0},
    {"short", "corto", 0},
    {NULL, NULL, 0}
};

/**
 * Busca si un identificador corresponde a una palabra reservada en C.
 * Retorna el indice en la tabla o -1 si es un identificador comun.
 */
int buscar_palabra_reservada(const char* ident) {
    for (int i = 0; TABLA_RESERVADAS[i].c_keyword != NULL; i++) {
        if (strcmp(TABLA_RESERVADAS[i].c_keyword, ident) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * Carga dinamicamente un archivo fuente completo en memoria Heap.
 */
char* cargar_archivo_en_memoria_dinamica(const char* ruta, size_t* out_tamano) {
    FILE* f = fopen(ruta, "rb");
    if (!f) {
        printf("[ERROR] No se pudo abrir el archivo de origen: %s\n", ruta);
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long tamano = ftell(f);
    fseek(f, 0, SEEK_SET);

    if (tamano < 0) {
        fclose(f);
        return NULL;
    }

    // Reservar memoria dinamica exacta (+1 para el terminador nulo)
    char* buffer = (char*)malloc(tamano + 1);
    if (!buffer) {
        printf("[ERROR] Fallo al asignar memoria dinamica de %ld bytes.\n", tamano);
        fclose(f);
        return NULL;
    }

    size_t leidos = fread(buffer, 1, tamano, f);
    buffer[leidos] = '\0';
    fclose(f);

    *out_tamano = leidos;
    return buffer;
}

/**
 * Analizador Lexico (Lexer) con Maquina de Estados Finitos:
 * Escanea el buffer en memoria dinamica reconociendo tokens.
 * Traduce exclusivamente palabras reservadas fuera de strings y comentarios.
 */
void analizar_y_traducir_lexico(const char* fuente, size_t tamano, FILE* f_salida) {
    size_t i = 0;
    int total_identificadores = 0;
    int total_traducidos = 0;

    while (i < tamano) {
        char c = fuente[i];

        // 1. Literal de Cadena: "..." (Preservar intacto sin traducir)
        if (c == '"') {
            fputc(c, f_salida);
            i++;
            while (i < tamano) {
                char sc = fuente[i];
                fputc(sc, f_salida);
                if (sc == '\\' && i + 1 < tamano) { // Caracter de escape
                    i++;
                    fputc(fuente[i], f_salida);
                } else if (sc == '"') {
                    i++;
                    break;
                }
                i++;
            }
            continue;
        }

        // 2. Literal de Caracter: '...' (Preservar intacto)
        if (c == '\'') {
            fputc(c, f_salida);
            i++;
            while (i < tamano) {
                char sc = fuente[i];
                fputc(sc, f_salida);
                if (sc == '\\' && i + 1 < tamano) {
                    i++;
                    fputc(fuente[i], f_salida);
                } else if (sc == '\'') {
                    i++;
                    break;
                }
                i++;
            }
            continue;
        }

        // 3. Comentarios de linea: // ... o multiline: /* ... */
        if (c == '/' && i + 1 < tamano) {
            char next = fuente[i + 1];
            if (next == '/') {
                // Comentario de una linea
                fputc(c, f_salida);
                fputc(next, f_salida);
                i += 2;
                while (i < tamano && fuente[i] != '\n') {
                    fputc(fuente[i], f_salida);
                    i++;
                }
                continue;
            } else if (next == '*') {
                // Comentario multiline
                fputc(c, f_salida);
                fputc(next, f_salida);
                i += 2;
                while (i < tamano) {
                    if (fuente[i] == '*' && i + 1 < tamano && fuente[i + 1] == '/') {
                        fputc('*', f_salida);
                        fputc('/', f_salida);
                        i += 2;
                        break;
                    }
                    fputc(fuente[i], f_salida);
                    i++;
                }
                continue;
            }
        }

        // 4. Identificadores y Palabras Reservadas: [a-zA-Z_][a-zA-Z0-9_]*
        if (isalpha((unsigned char)c) || c == '_') {
            size_t inicio = i;
            while (i < tamano && (isalnum((unsigned char)fuente[i]) || fuente[i] == '_')) {
                i++;
            }
            size_t len = i - inicio;
            char ident[128];
            if (len < sizeof(ident)) {
                strncpy(ident, &fuente[inicio], len);
                ident[len] = '\0';

                total_identificadores++;
                int idx = buscar_palabra_reservada(ident);

                if (idx >= 0) {
                    // Palabra reservada encontrada: escribir traduccion en espanol
                    fputs(TABLA_RESERVADAS[idx].es_keyword, f_salida);
                    TABLA_RESERVADAS[idx].conteo++;
                    total_traducidos++;
                } else {
                    // Identificador de usuario: preservar tal cual
                    fputs(ident, f_salida);
                }
            } else {
                // Identificador inusualmente largo
                fwrite(&fuente[inicio], 1, len, f_salida);
            }
            continue;
        }

        // 5. Otros caracteres (espacios, operadores, puntuacion, constantes numericas)
        fputc(c, f_salida);
        i++;
    }

    // Reporte estadistico del Analisis Lexico
    printf("======================================================================\n");
    printf("   ESTADISTICAS DEL ANALIZADOR LEXICO (Traduccion C -> Espanol)\n");
    printf("======================================================================\n");
    printf("Caracteres procesados en RAM : %zu bytes\n", tamano);
    printf("Total identificadores leidos : %d\n", total_identificadores);
    printf("Palabras reservadas traducidas: %d\n\n", total_traducidos);
    printf("%-18s | %-18s | %-10s\n", "Palabra en C", "Traduccion (ES)", "Frecuencia");
    printf("----------------------------------------------------\n");

    for (int t = 0; TABLA_RESERVADAS[t].c_keyword != NULL; t++) {
        if (TABLA_RESERVADAS[t].conteo > 0) {
            printf("%-18s | %-18s | %-10d\n",
                TABLA_RESERVADAS[t].c_keyword,
                TABLA_RESERVADAS[t].es_keyword,
                TABLA_RESERVADAS[t].conteo);
        }
    }
    printf("----------------------------------------------------\n");
}

int main(int argc, char* argv[]) {
    const char* ruta_origen = "programa_prueba.c";
    const char* ruta_destino = "programa_traducido.c";

    if (argc >= 2) ruta_origen = argv[1];
    if (argc >= 3) ruta_destino = argv[2];

    printf("======================================================================\n");
    printf("   EJERCICIO 3: RECONOCEDOR Y TRADUCTOR LEXICO C -> ESPANOL\n");
    printf("   Estudiante: Brayan Carreno (C.I. V-32.015.527) - Grupo ParseCore\n");
    printf("======================================================================\n");
    printf("Archivo de entrada : %s\n", ruta_origen);
    printf("Archivo de salida  : %s\n\n", ruta_destino);

    size_t tamano_fuente = 0;
    // Cargar codigo fuente de forma DINAMICA en memoria
    char* codigo_en_memoria = cargar_archivo_en_memoria_dinamica(ruta_origen, &tamano_fuente);
    if (!codigo_en_memoria) {
        return 1;
    }

    FILE* f_out = fopen(ruta_destino, "w");
    if (!f_out) {
        printf("[ERROR] No se pudo crear el archivo de salida: %s\n", ruta_destino);
        free(codigo_en_memoria);
        return 1;
    }

    analizar_y_traducir_lexico(codigo_en_memoria, tamano_fuente, f_out);
    fclose(f_out);

    // Liberar la memoria dinamica
    free(codigo_en_memoria);

    printf("\n[EXITO] Traduccion lexica completada y guardada en '%s'.\n", ruta_destino);
    return 0;
}
