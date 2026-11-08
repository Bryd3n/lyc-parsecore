# Prueba Diagnóstica — Lenguajes y Compiladores (2026-II)

**Estudiante:** NOMBRE APELLIDO
**Sección:** ____
**Repositorio:** UNEG / PRUEBA_DIAGNOSTICA / NOMBRE APELLIDO
**Video de defensa:** ver `ENLACE_DRIVE.txt`

## Contenido
- `ejercicio1/` → Validación de movimientos de caballo en C (+ benchmark 500 mov × 10).
- `ejercicio2/` → (x+1)^n vía Triángulo de Pascal, en C (memoria dinámica) y Python + comparativa de tiempos.
- `ejercicio3/` → Traductor de palabras reservadas C → español (C, escáner con máquina de estados).

## Compilación y ejecución
```bash
chmod +x setup_arch.sh && ./setup_arch.sh   # solo la primera vez

cd ejercicio1 && make && make bench
cd ../ejercicio2 && make && make bench
cd ../ejercicio3 && make && make demo
