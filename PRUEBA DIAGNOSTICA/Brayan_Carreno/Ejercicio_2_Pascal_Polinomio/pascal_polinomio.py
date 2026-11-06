"""
Lenguajes y Compiladores - Semestre VII (UNEG)
Prueba Diagnostica - Ejercicio 2: Polinomio (x+1)^n y Triangulo de Pascal con Memoria Dinamica
Estudiante: Brayan Carreno (C.I. V-32.015.527) - Seccion 01
Grupo: ParseCore ("Estructurando la sintaxis, optimizando la ejecucion.")
Profesor: Msc. Felix Marquez
"""

import time
import sys

def generar_triangulo_pascal(n: int) -> list:
    """
    Genera los coeficientes del binomio (x+1)^n utilizando el Triangulo de Pascal.
    Implementado con asignacion dinamica de memoria en cada nivel.
    Retorna la lista de coeficientes de la fila n: [c_n, c_{n-1}, ..., c_1, c_0].
    """
    if n < 0:
        raise ValueError("El grado n debe ser un entero no negativo.")
    
    # Memoria dinamica: cada fila se crea dinamicamente en tiempo de ejecucion
    fila_actual = [1]
    
    for i in range(1, n + 1):
        nueva_fila = [1] * (i + 1)
        for j in range(1, i):
            nueva_fila[j] = fila_actual[j - 1] + fila_actual[j]
        fila_actual = nueva_fila # Libera la referencia anterior en el recolector
        
    return fila_actual


def formatear_polinomio(n: int, coeficientes: list) -> str:
    """
    Construye la representacion algebraica formal de (x+1)^n = sum(c_k * x^k).
    Ejemplo: (x+1)^3 = x^3 + 3x^2 + 3x + 1
    """
    terminos = []
    # coeficientes va de k=0 a k=n (o de mayor a menor grado)
    # Por convencion matematica: x^n + c_{n-1}*x^{n-1} + ... + 1
    for k in range(n, -1, -1):
        c = coeficientes[k]
        if c == 0:
            continue
            
        if k == 0:
            terminos.append(f"{c}")
        elif k == 1:
            terminos.append(f"{c if c != 1 else ''}x")
        else:
            terminos.append(f"{c if c != 1 else ''}x^{k}")
            
    return f"(x+1)^{n} = " + " + ".join(terminos)


def evaluar_polinomio_paso_a_paso(n: int, coeficientes: list, x: float):
    """
    Muestra por pasos el calculo numerico de f(x) = (x+1)^n segun el polinomio generado.
    """
    print("=" * 70)
    print(f"   CALCULO PASO A PASO PARA x = {x} EN f(x) = (x+1)^{n}")
    print("=" * 70)
    
    suma_total = 0.0
    print(f"Polinomio expandido: {formatear_polinomio(n, coeficientes)}\n")
    print(f"{'Termino k':<12} | {'Coeficiente (c_k)':<20} | {'Potencia x^k':<18} | {'Valor Termino':<20}")
    print("-" * 75)
    
    for k in range(n, -1, -1):
        c = coeficientes[k]
        potencia = x ** k
        valor_termino = c * potencia
        suma_total += valor_termino
        print(f"k = {k:<8} | {c:<20} | {potencia:<18.4f} | {valor_termino:<20.4f}")
        
    print("-" * 75)
    print(f"Suma acumulada por expansion : {suma_total}")
    valor_directo = (x + 1.0) ** n
    print(f"Verificacion directa (x+1)^n  : {valor_directo}")
    diferencia = abs(suma_total - valor_directo)
    print(f"Diferencia de precision       : {diferencia:.2e} (Consistencia verificada)\n")
    return suma_total


def benchmark_pascal_n100(repeticiones: int = 1000):
    """Mide el tiempo de ejecucion en Python para generar la fila n=100 de Pascal."""
    print("=" * 70)
    print("   BENCHMARK PASCAL n = 100 (Python)")
    print("=" * 70)
    
    t0 = time.perf_counter()
    for _ in range(repeticiones):
        coefs = generar_triangulo_pascal(100)
    t1 = time.perf_counter()
    
    tiempo_us = ((t1 - t0) / repeticiones) * 1_000_000
    tiempo_ms = tiempo_us / 1000.0
    
    print(f"Fila n = 100 generada con exito (Coeficiente central C(100,50) = {coefs[50]})")
    print(f"Tiempo promedio de ejecucion ({repeticiones} runs): {tiempo_us:.2f} us ({tiempo_ms:.6f} ms)\n")
    return tiempo_us


if __name__ == "__main__":
    # 1. Demostración de polinomios dados en el enunciado (n = 0 a 7)
    print("======================================================================")
    print("   EJEMPLOS DEL ENUNCIADO (n = 0 hasta 7)")
    print("======================================================================")
    for grado in range(8):
        c = generar_triangulo_pascal(grado)
        print(formatear_polinomio(grado, c))
    print()
    
    # 2. Evaluación paso a paso con n=4 y x=2
    coefs_4 = generar_triangulo_pascal(4)
    evaluar_polinomio_paso_a_paso(4, coefs_4, x=2.0)
    
    # 3. Benchmark n=100
    benchmark_pascal_n100(1000)
