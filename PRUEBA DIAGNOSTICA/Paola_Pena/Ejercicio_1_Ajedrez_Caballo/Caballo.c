#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

// Función que valida una secuencia de movimientos
// Recibe la posición inicial, el número de movimientos, la cadena y si debe imprimir el resultado
void verificar_movimientos(const char* inicial, int n, const char* movimientos, int imprimir_resultado) {
    char current_col = inicial[0];
    char current_row = inicial[1];
    
    // Se duplica la cadena para no modificar la original al usar strtok
    char* mov_copy = strdup(movimientos);
    if (!mov_copy) return;

    char* token = strtok(mov_copy, " \r\n");
    int move_count = 1;
    
    while (token != NULL && move_count <= n) {
        // Validar que el movimiento inicie con la letra esperada (K para caballo)
        if (token[0] != 'K') {
            if (imprimir_resultado) {
                printf("movimiento INCORRECTO falla letra %c no pertenece a un caballo.\n", token[0]);
            }
            free(mov_copy);
            return;
        }
        
        char next_col = token[1];
        char next_row = token[2];
        
        // Calcular diferencias en x (columnas) y en y (filas)
        int dx = abs(next_col - current_col);
        int dy = abs(next_row - current_row);
        
        // Un caballo se mueve en "L": 2 casillas en un eje y 1 en el otro
        if (!((dx == 1 && dy == 2) || (dx == 2 && dy == 1))) {
            if (imprimir_resultado) {
                printf("INCORRECTO falla en el movimiento %d.\n", move_count);
            }
            free(mov_copy);
            return;
        }
        
        // Actualizar posición y avanzar al siguiente movimiento
        current_col = next_col;
        current_row = next_row;
        token = strtok(NULL, " \r\n");
        move_count++;
    }
    
    if (imprimir_resultado) {
        printf("movimiento CORRECTO.\n");
    }
    free(mov_copy);
}

int main() {
    printf("--- PRUEBAS DE EJEMPLO ---\n");
    verificar_movimientos("a1", 4, "Kc2 Kd4 Kb3 Kc5", 1);
    verificar_movimientos("a1", 4, "Kc2 Kd4 Kb4 Kc5", 1);
    verificar_movimientos("a2", 5, "Kc3 Ke4 Kf6 Ke8 Kg7", 1);
    verificar_movimientos("a2", 5, "Kc8 Ke4 Kf6 Ke8 Kg7", 1);
    verificar_movimientos("a8", 2, "Kb6 Kd7", 1);
    verificar_movimientos("a8", 2, "Kb6 Kb7", 1);
    verificar_movimientos("a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Kb4", 1);
    verificar_movimientos("a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Qb4", 1);
    verificar_movimientos("a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kh6 Kb4", 1);

    printf("\n--- PRUEBA DE RENDIMIENTO (500 movimientos x 10 veces) ---\n");
    
    // Los 500 movimientos proporcionados en el planteamiento
    const char* movimientos_500 = 
        "Kb4 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 "
        "Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 "
        "Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 "
        "Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 "
        "Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 "
        "Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 "
        "Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 "
        "Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 "
        "Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 "
        "Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 "
        "Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 "
        "Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 "
        "Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 "
        "Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4";

    // Iniciar temporizador
    clock_t inicio = clock();

    // Ejecutar 10 veces la validación de 500 movimientos
    for (int i = 0; i < 10; i++) {
        verificar_movimientos("a2", 500, movimientos_500, 0); // 0 para no saturar la consola imprimiendo 10 veces
    }

    // Detener temporizador
    clock_t fin = clock();
    double tiempo_gastado = (double)(fin - inicio) / CLOCKS_PER_SEC;

    printf("Validacion completada.\n");
    printf("Tiempo total de ejecucion para 10 iteraciones de 500 movimientos: %f segundos\n", tiempo_gastado);

    return 0;
}