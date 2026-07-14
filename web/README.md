# Puzzle Grid Solver — web interface

A static web page for building and solving Sudoku, Suguru, Killer Sudoku, and Kakuro grids in the browser. Grid size is adjustable for every puzzle type. Solving runs the original backtracking algorithms from `../src/*.cpp` compiled to WebAssembly — nothing is sent to a server.

## Running it

Browsers block `fetch()` of the `.wasm` file from a `file://` page, so serve the folder over HTTP:

```sh
cd web
python3 -m http.server 8000
```

Then open http://localhost:8000.

## Using it

Each puzzle type has its own tab with an **Example** button (loads one of the sample puzzles from `src/`), a **Clear** button, and a **Solve** button.

- **Sudoku**: set the box size (3 → 9×9), type in known digits, Solve.
- **Suguru**: use **Paint** to color in each region by click-dragging, **Numbers** to enter any known digits, then Solve. Any cell left unpainted becomes its own single-cell region.
- **Killer Sudoku**: use **Paint** to color in each cage, enter that cage's sum in the small badge on its top-left cell, switch to **Givens** for any known digits, then Solve.
- **Kakuro**: click a cell to cycle Blocked → Clue → Fillable. On a clue cell (diagonally split), the top-right triangle is the row (across) sum and the bottom-left triangle is the column (down) sum for the run(s) it introduces.

## Rebuilding the WebAssembly module

`wasm/puzzle_solvers.js` / `puzzle_solvers.wasm` are committed so the page works without installing anything. If you change the C++ sources under `wasm/src/`, rebuild with [Emscripten](https://emscripten.org/docs/getting_started/downloads.html) installed (e.g. `brew install emscripten`):

```sh
cd web/wasm
./build.sh
```

## Layout

```
web/
  index.html, style.css      the page
  js/                        one file per puzzle type + shared helpers/bridge
  wasm/src/                  dynamic-size C++ ports of the src/*.cpp solvers
  wasm/build.sh               rebuild script
  wasm/puzzle_solvers.{js,wasm}   compiled output (committed)
```
