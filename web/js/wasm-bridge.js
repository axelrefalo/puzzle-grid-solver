let modulePromise = null;

function loadModule() {
    if (!modulePromise) {
        modulePromise = PuzzleSolvers();
    }
    return modulePromise;
}

function withIntArrays(Module, arrays, fn) {
    const ptrs = arrays.map((arr) => {
        const ptr = Module._malloc(arr.length * 4);
        Module.HEAP32.set(arr, ptr / 4);
        return ptr;
    });
    try {
        return fn(...ptrs);
    } finally {
        ptrs.forEach((ptr) => Module._free(ptr));
    }
}

function readIntArray(Module, ptr, length) {
    return Array.from(Module.HEAP32.subarray(ptr / 4, ptr / 4 + length));
}

async function solveSudoku(grid, boxSize) {
    const Module = await loadModule();
    const n = boxSize * boxSize;
    const solve = Module.cwrap('solve_sudoku', 'number', ['number', 'number']);

    return withIntArrays(Module, [grid], (gridPtr) => {
        const solved = solve(gridPtr, boxSize);
        return {
            solved: !!solved,
            grid: solved ? readIntArray(Module, gridPtr, n * n) : null,
        };
    });
}

async function solveSuguru(values, regions, rows, cols) {
    const Module = await loadModule();
    const solve = Module.cwrap('solve_suguru', 'number', ['number', 'number', 'number', 'number']);

    return withIntArrays(Module, [values, regions], (valuesPtr, regionsPtr) => {
        const solved = solve(valuesPtr, regionsPtr, rows, cols);
        return {
            solved: !!solved,
            values: solved ? readIntArray(Module, valuesPtr, rows * cols) : null,
        };
    });
}

async function solveKillerSudoku(sums, cages, givens, boxSize) {
    const Module = await loadModule();
    const n = boxSize * boxSize;
    const solve = Module.cwrap('solve_killer_sudoku', 'number', ['number', 'number', 'number', 'number', 'number']);

    return withIntArrays(Module, [sums, cages, givens, new Array(n * n).fill(0)], (sumsPtr, cagesPtr, givensPtr, outPtr) => {
        const solved = solve(sumsPtr, cagesPtr, givensPtr, outPtr, boxSize);
        return {
            solved: !!solved,
            solution: solved ? readIntArray(Module, outPtr, n * n) : null,
        };
    });
}

async function solveKakuro(horizSums, vertSums, prefilled, rows, cols) {
    const Module = await loadModule();
    const solve = Module.cwrap('solve_kakuro', 'number', ['number', 'number', 'number', 'number', 'number', 'number']);

    return withIntArrays(
        Module,
        [horizSums, vertSums, prefilled, new Array(rows * cols).fill(0)],
        (horizPtr, vertPtr, prefilledPtr, outPtr) => {
            const solved = solve(horizPtr, vertPtr, prefilledPtr, outPtr, rows, cols);
            return {
                solved: !!solved,
                solution: solved ? readIntArray(Module, outPtr, rows * cols) : null,
            };
        }
    );
}

window.PuzzleSolversBridge = {
    solveSudoku,
    solveSuguru,
    solveKillerSudoku,
    solveKakuro,
};
