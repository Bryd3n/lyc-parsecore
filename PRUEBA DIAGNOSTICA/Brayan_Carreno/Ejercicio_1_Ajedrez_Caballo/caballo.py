"""
Lenguajes y Compiladores - Semestre VII (UNEG)
Prueba Diagnostica - Ejercicio 1: Validacion y Rendimiento de Movimientos de Caballo
Estudiante: Brayan Carreno (C.I. V-32.015.527) - Seccion 01
Grupo: ParseCore ("Estructurando la sintaxis, optimizando la ejecucion.")
Profesor: Msc. Felix Marquez
"""

import time
import os

def validar_movimientos(ak: str, movimientos_str: str) -> str:
    """
    Evalua una secuencia de movimientos de un caballo desde la casilla Ak.
    Reglas de ajedrez: desplazamiento en forma de 'L' (|dx|*|dy| == 2 y |dx|+|dy| == 3).
    Notacion: prefijo 'K' + columna ('a'-'h') + fila ('1'-'8').
    """
    # 1. Validar casilla inicial
    ak = ak.strip()
    if len(ak) != 2:
        return "INCORRECTO casilla inicial invalida."
    
    col_char = ak[0].lower()
    row_char = ak[1]
    
    if not ('a' <= col_char <= 'h' and '1' <= row_char <= '8'):
        return "INCORRECTO casilla inicial fuera del tablero."
    
    col = ord(col_char) - ord('a')
    row = int(row_char) - 1
    
    # 2. Separar movimientos
    if isinstance(movimientos_str, str):
        movimientos = movimientos_str.split()
    else:
        movimientos = movimientos_str
        
    for i, m in enumerate(movimientos, 1):
        m = m.strip()
        if not m:
            continue
            
        # Validar longitud mínima
        if len(m) != 3:
            return f"INCORRECTO falla en el movimiento {i}."
            
        # Validar prefijo 'K'
        letra_pieza = m[0]
        if letra_pieza != 'K':
            return f"movimiento INCORRECTO falla letra {letra_pieza} no pertenece a un caballo."
            
        t_col_char = m[1].lower()
        t_row_char = m[2]
        
        # Validar si casilla de destino existe en el tablero de 8x8
        if not ('a' <= t_col_char <= 'h' and '1' <= t_row_char <= '8'):
            return f"INCORRECTO falla en el movimiento {i}."
            
        target_col = ord(t_col_char) - ord('a')
        target_row = int(t_row_char) - 1
        
        dx = abs(target_col - col)
        dy = abs(target_row - row)
        
        # Geometría del salto del caballo (L-shape): dx^2 + dy^2 = 5
        if not ((dx == 1 and dy == 2) or (dx == 2 and dy == 1)):
            return f"INCORRECTO falla en el movimiento {i}."
            
        # Actualizar posición actual
        col = target_col
        row = target_row
        
    return "movimiento CORRECTO."


# Secuencia oficial de 500 movimientos extraída de la actualización oficial del profesor
SECUENCIA_OFICIAL_500 = (
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
    "Ka8 Kc7 Ka6 Kc5 Ka4 "
)

def generar_secuencia_valida(n: int, ak: str = "a1") -> list:
    """Genera n movimientos válidos continuos de caballo a partir de Ak."""
    import random
    col = ord(ak[0].lower()) - ord('a')
    row = int(ak[1]) - 1
    deltas = [(1, 2), (1, -2), (-1, 2), (-1, -2), (2, 1), (2, -1), (-2, 1), (-2, -1)]
    moves = []
    
    random.seed(42) # Semilla fija para reproducibilidad exacta
    for _ in range(n):
        valid_next = []
        for dx, dy in deltas:
            nc, nr = col + dx, row + dy
            if 0 <= nc <= 7 and 0 <= nr <= 7:
                valid_next.append((nc, nr))
        if not valid_next:
            break
        col, row = random.choice(valid_next)
        moves.append(f"K{chr(ord('a') + col)}{row + 1}")
    return moves


def ejecutar_pruebas_enunciado():
    print("=" * 70)
    print("   PRUEBAS OFICIALES DEL ENUNCIADO (Casos de Prueba)")
    print("=" * 70)
    
    casos = [
        ("a1", 4, "Kc2 Kd4 Kb3 Kc5", "movimiento CORRECTO."),
        ("a1", 4, "Kc2 Kd4 Kb4 Kc5", "INCORRECTO falla en el movimiento 3."),
        ("a2", 5, "Kc3 Ke4 Kf6 Ke8 Kg7", "movimiento CORRECTO."),
        ("a2", 5, "Kc8 Ke4 Kf6 Ke8 Kg7", "INCORRECTO falla en el movimiento 1."),
        ("a8", 2, "Kb6 Kd7", "movimiento CORRECTO."),
        ("a8", 2, "Kb6 Kb7", "INCORRECTO falla en el movimiento 2."),
        ("a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Kb4", "movimiento CORRECTO."),
        ("a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Qb4", "movimiento INCORRECTO falla letra Q no pertenece a un caballo."),
        ("a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kh6 Kb4", "movimiento INCORRECTO falla en el movimiento 9")
    ]
    
    for i, (ak, n, cadena, esperado) in enumerate(casos, 1):
        res = validar_movimientos(ak, cadena)
        cumple = "EXITOSO" if esperado.replace(".", "").lower() in res.replace(".", "").lower() else "DISCREPANCIA"
        print(f"[{cumple}] Caso {i}: Ak={ak}, n={n}")
        print(f"   Entrada: {cadena}")
        print(f"   Salida : {res}")
        print(f"   Esperad: {esperado}\n")


def benchmark_500_movimientos():
    print("=" * 70)
    print("   PRUEBA DE RENDIMIENTO: 10 verificaciones de 500 movimientos oficiales")
    print("   (Actualización oficial del Prof. Félix Márquez - Posición inicial: a2)")
    print("=" * 70)
    
    tiempos = []
    print("Ejecutando 10 iteraciones sobre la secuencia oficial de 500 movimientos...")
    for iteracion in range(1, 11):
        t0 = time.perf_counter()
        res = validar_movimientos("a2", SECUENCIA_OFICIAL_500)
        t1 = time.perf_counter()
        duracion_ms = (t1 - t0) * 1000
        tiempos.append(duracion_ms)
        print(f"  Iteracion {iteracion:2d}: {duracion_ms:.4f} ms -> {res}")
        
    tiempo_total_ms = sum(tiempos)
    tiempo_promedio_ms = tiempo_total_ms / len(tiempos)
    print("-" * 70)
    print(f"Tiempo Total (10 ejecuciones Python): {tiempo_total_ms:.4f} ms")
    print(f"Tiempo Promedio por ejecucion: {tiempo_promedio_ms:.4f} ms\n")
    return tiempo_total_ms, tiempo_promedio_ms


def benchmark_n100():
    print("=" * 70)
    print("   BENCHMARK PARA n = 100 MOVIMIENTOS (Python)")
    print("=" * 70)
    
    movs_100 = generar_secuencia_valida(100, "a1")
    cadena_100 = " ".join(movs_100)
    
    repeticiones = 1000
    t0 = time.perf_counter()
    for _ in range(repeticiones):
        validar_movimientos("a1", cadena_100)
    t1 = time.perf_counter()
    
    tiempo_unitario_us = ((t1 - t0) / repeticiones) * 1_000_000
    tiempo_unitario_ms = tiempo_unitario_us / 1000
    
    print(f"Tiempo de ejecucion para n = 100 (promedio sobre {repeticiones} runs):")
    print(f"  -> {tiempo_unitario_us:.2f} microsegundos ({tiempo_unitario_ms:.6f} ms)\n")
    return tiempo_unitario_us


if __name__ == "__main__":
    ejecutar_pruebas_enunciado()
    benchmark_500_movimientos()
    t_py = benchmark_n100()
