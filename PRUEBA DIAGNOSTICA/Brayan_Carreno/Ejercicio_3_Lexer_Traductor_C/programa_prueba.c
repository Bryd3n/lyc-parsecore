#include <stdio.h>

// Programa de prueba para el Analizador Lexico (Traductor C a Espanol)
// Comentario: Esta funcion no debe traducir if o while dentro del comentario
int calcular_factorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * calcular_factorial(n - 1);
    }
}

void demostrar_bucles() {
    int contador = 0;
    while (contador < 5) {
        printf("Valor actual del contador: %d\n", contador);
        contador++;
    }

    for (int i = 0; i < 3; i++) {
        // La palabra for no debe ser traducida dentro de strings
        char* mensaje = "Prueba de cadena con palabras reservadas: if, else, for, while, return";
        float valor_flotante = 3.14159;
    }
}

int main() {
    int numero = 5;
    int resultado = calcular_factorial(numero);
    demostrar_bucles();
    return 0;
}
