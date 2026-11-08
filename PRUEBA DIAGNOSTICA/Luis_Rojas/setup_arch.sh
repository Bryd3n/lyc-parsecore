#!/usr/bin/env bash
# setup_arch.sh — Ejecutar UNA sola vez en Arch/Manjaro
set -euo pipefail

if ! command -v pacman >/dev/null 2>&1; then
  echo "Este script es para Arch Linux / Manjaro." >&2
  exit 1
fi

sudo pacman -Sy --needed --noconfirm \
     base-devel gcc clang python python-pip git time

echo "--- Versiones instaladas ---"
gcc      --version | head -n1
python3  --version
