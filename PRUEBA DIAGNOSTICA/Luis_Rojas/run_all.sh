#!/usr/bin/env bash
# run_all.sh — Corre los 3 ejercicios en orden, con pausas para narrar.
# Uso:    ./run_all.sh           (sin pausas, corrido)
#         ./run_all.sh --pause   (pide Enter entre secciones)
set -uo pipefail
ROOT="$(cd "$(dirname "$0")" && pwd)"

PAUSE=0
[[ "${1:-}" == "--pause" ]] && PAUSE=1
pause() { [[ $PAUSE -eq 1 ]] && read -rp $'\n\033[33m  ► Enter para continuar…\033[0m ' _; }

banner() {
    printf '\n\033[1;44;97m  %-70s  \033[0m\n' "$1"
    printf '\033[1;44m%-74s\033[0m\n\n' "$(printf '─%.0s' {1..74})"
}

# ── EJERCICIO 1 ──────────────────────────────────────────────
banner "EJERCICIO 1 · Movimientos del Caballo (C)"
cd "$ROOT/ejercicio1" && make -s && ./test.sh
pause

# ── EJERCICIO 2 ──────────────────────────────────────────────
banner "EJERCICIO 2 · (x+1)^n vía Triángulo de Pascal — C vs Python"
cd "$ROOT/ejercicio2" && make -s
echo "── Ejemplo del enunciado: (x+1)^6 ──"
./pascal 6 2
echo
echo "── Ejemplo del enunciado: (x+1)^7 ──"
./pascal 7 2
echo
echo "── Comparativa de rendimiento n=100 ──"
./comparar.sh
pause

# ── EJERCICIO 3 ──────────────────────────────────────────────
banner "EJERCICIO 3 · Traductor de palabras reservadas C → Español"
cd "$ROOT/ejercicio3" && make -s
echo "═══ ARCHIVO ORIGINAL (ejemplo.c) ═══"
cat ejemplo.c
echo
echo "═══ ARCHIVO TRADUCIDO (traducido.c) ═══"
./traductor ejemplo.c >traducido.c
cat traducido.c
echo
echo "═══ INFORME DE OCURRENCIAS ═══"
./traductor ejemplo.c >/dev/null

banner "FIN"
