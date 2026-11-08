#!/usr/bin/env bash
# Compara tiempos C vs Python para n=100, 100 ejecuciones.
set -euo pipefail
cd "$(dirname "$0")"
make -s >/dev/null

echo "─────────────────────────────────────"
./pascal --bench
echo "─────────────────────────────────────"
python3 pascal.py --bench
echo "─────────────────────────────────────"
