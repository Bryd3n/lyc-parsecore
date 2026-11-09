#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Diccionario de palabras reservadas
const char* reservadas[] = {"int", "float", "char", "void", "if", "else", "while", "for", "return"};
const char* traducciones[] = {"entero", "flotante", "caracter", "vacio", "si", "sino", "mientras", "para", "retornar"};
#define NUM_PALABRAS 9

// Función para cargar el archivo completo en memoria dinámica
char* cargar_archivo(const char* nombre_archivo) {
    FILE* archivo = fopen(nombre_archivo, "r");
    if (!archivo) {
        printf("Error: No se pudo abrir el archivo %s\n", nombre_archivo);
        return NULL;
    }
    
    // Determinar el tamaño exacto del archivo
    fseek(archivo, 0, SEEK_END);
    long tamano = ftell(archivo);
    fseek(archivo, 0, SEEK_SET);
    
    // Asignación de memoria dinámica obligatoria
    char* contenido = (char*)malloc(tamano + 1);
    if (contenido) {
        fread(contenido, 1, tamano, archivo);
        contenido[tamano] = '\0';
    }
    fclose(archivo);
    return contenido;
}

// Función para escanear y traducir tokens
void procesar_y_traducir(const char* contenido) {
    int i = 0;
    char buffer[100];
    int buf_idx = 0;

    printf("--- CODIGO TRADUCIDO AL ESPANOL ---\n");
    while (contenido[i] != '\0') {
        // Acumular caracteres si forman parte de una palabra
        if (isalpha(contenido[i]) || isdigit(contenido[i]) || contenido[i] == '_') {
            buffer[buf_idx++] = contenido[i];
        } else {
            // Al encontrar un separador, evaluar la palabra acumulada
            if (buf_idx > 0) {
                buffer[buf_idx] = '\0';
                int traducido = 0;
                for (int j = 0; j < NUM_PALABRAS; j++) {
                    if (strcmp(buffer, reservadas[j]) == 0) {
                        printf("%s", traducciones[j]);
                        traducido = 1;
                        break;
                    }
                }
                // Si no es palabra reservada, imprimir la original
                if (!traducido) printf("%s", buffer);
                buf_idx = 0;
            }
            // Imprimir el caracter separador (espacio, llave, paréntesis, etc.)
            printf("%c", contenido[i]);
        }
        i++;
    }
    printf("\n");
}

int main() {
    const char* archivo_entrada = "codigo_prueba.c";
    
    // 1. Cargar archivo en memoria dinámica
    char* codigo_fuente = cargar_archivo(archivo_entrada);
    
    if (codigo_fuente) {
        // 2. Procesar el texto
        procesar_y_traducir(codigo_fuente);
        
        // 3. Liberar la memoria dinámica
        free(codigo_fuente);
    }
    
    return 0;
}