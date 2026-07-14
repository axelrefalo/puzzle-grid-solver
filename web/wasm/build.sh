#!/usr/bin/env bash
# Rebuilds puzzle_solvers.js / puzzle_solvers.wasm from web/wasm/src.
# Requires Emscripten (emcc) on PATH: https://emscripten.org/docs/getting_started/downloads.html
set -euo pipefail
cd "$(dirname "$0")"

emcc src/bindings.cpp \
  -O2 \
  -o puzzle_solvers.js \
  -s MODULARIZE=1 \
  -s EXPORT_NAME=PuzzleSolvers \
  -s ENVIRONMENT=web,node \
  -s ALLOW_MEMORY_GROWTH=1 \
  -s EXPORTED_RUNTIME_METHODS='["ccall","cwrap","HEAP32"]' \
  -s EXPORTED_FUNCTIONS='["_malloc","_free","_solve_sudoku","_solve_suguru","_solve_killer_sudoku","_solve_kakuro"]'

echo "Built puzzle_solvers.js and puzzle_solvers.wasm"
