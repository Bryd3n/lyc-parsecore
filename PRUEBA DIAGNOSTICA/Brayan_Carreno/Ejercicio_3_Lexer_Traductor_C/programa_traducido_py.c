#include <stdio.h>

// Programa de prueba para el Analizador Lexico (Traductor C a Espanol)
// Comentario: Esta funcion no debe traducir if o while dentro del comentario
entero calcular_factorial(entero n) {
    si (n <= 1) {
        retornar 1;
    } sino {
        retornar n * calcular_factorial(n - 1);
    }
}

vacio demostrar_bucles() {
    entero contador = 0;
    mientras (contador < 5) {
        printf("Valor actual del contador: %d\n", contador);
        contador++;
    }

    para (entero i = 0; i < 3; i++) {
        // La palabra for no debe ser traducida dentro de strings
        caracter* mensaje = "Prueba de cadena con palabras reservadas: if, else, for, while, return";
        flotante valor_flotante = 3.14159;
    }
}

entero main() {
    entero numero = 5;
    entero resultado = calcular_factorial(numero);
    demostrar_bucles();
    retornar 0;
}
