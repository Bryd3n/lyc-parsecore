#!/usr/bin/env python3
"""pascal.py — Ejercicio 2: (x+1)^n con Triángulo de Pascal (memoria dinámica: listas)."""
import sys
import time


def fila_pascal(n: int) -> list:
    fila = [1]
    for i in range(1, n + 1):
        fila.append(1)
        for j in range(i - 1, 0, -1):
            fila[j] += fila[j - 1]
    return fila


def polinomio(coef: list) -> str:
    n = len(coef) - 1
    partes = []
    for k, c in enumerate(coef):
        e = n - k
        if e == 0:
            partes.append(str(c))
        elif e == 1:
            partes.append("x" if c == 1 else f"{c}x")
        else:
            partes.append(f"x^{e}" if c == 1 else f"{c}x^{e}")
    return " + ".join(partes)


def evaluar_con_pasos(coef: list, x: int) -> str:
    n = len(coef) - 1
    term, val = [], []
    total = 0
    for k, c in enumerate(coef):
        e = n - k
        v = c * (x ** e)
        total += v
        term.append(f"{c}*{x}^{e}")
        val.append(str(v))
    return (f"f({x}) = (x+1)^{n}\n"
            f"     = " + " + ".join(term) + "\n"
            f"     = " + " + ".join(val) + "\n"
            f"     = {total}")


def bench(iters: int = 100, n: int = 100) -> None:
    t0 = time.perf_counter()
    for _ in range(iters):
        f = fila_pascal(n)
    t1 = time.perf_counter()
    print(f"Python — n={n}, {iters} ejecuciones")
    print(f"  Tiempo total : {t1 - t0:.6f} s")
    print(f"  Por ejecucion: {(t1 - t0) / iters:.6f} s")
    print(f"  Digito control (coef central) = {f[n // 2] % 1000:03d}")


def main() -> None:
    if len(sys.argv) > 1 and sys.argv[1] == "--bench":
        bench()
        return

    n = int(sys.argv[1]) if len(sys.argv) > 1 else 5
    x = int(sys.argv[2]) if len(sys.argv) > 2 else 2
    if n < 0:
        sys.exit("n debe ser >= 0")

    coef = fila_pascal(n)
    print(f"(x+1)^{n} = {polinomio(coef)}")
    print()
    print(evaluar_con_pasos(coef, x))


if __name__ == "__main__":
    main()
