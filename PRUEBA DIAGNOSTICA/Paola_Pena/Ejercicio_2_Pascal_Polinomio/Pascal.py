import time

# Función para generar los coeficientes
def generar_coeficientes(n):
    coef = [1] * (n + 1)
    for i in range(1, n + 1):
        for j in range(i - 1, 0, -1):
            coef[j] = coef[j] + coef[j - 1]
    return coef

def main():
    # Prueba de rendimiento para n=100
    print("--- PRUEBA DE RENDIMIENTO EN PYTHON (n=100) ---")
    
    inicio = time.perf_counter()
    
    coef_100 = generar_coeficientes(100)
    
    fin = time.perf_counter()
    tiempo = fin - inicio
    
    print(f"Generacion de coeficientes para n=100 completada en {tiempo:.6f} segundos.")

if __name__ == "__main__":
    main()