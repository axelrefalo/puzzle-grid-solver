#include <vector>

// Dynamic-size port of ../../../src/KillerSudokuSolver.cpp
// N x N grid where N = boxSize * boxSize, flattened row-major.
namespace killer_sudoku {

static int boxSize;
static int N;

static bool inGrid(int line, int col) {
    return line >= 0 && line < N && col >= 0 && col < N;
}

// end of a cage: no other cell of the same cage below (same or earlier column) or to the right (same line)
static bool endBloc(std::vector<int>& cages, int line, int col) {
    int blocNumber = cages[line * N + col];

    for (int _col = 0; _col <= col; _col++) {
        int _line = line + 1;
        if (inGrid(_line, _col) && blocNumber == cages[_line * N + _col]) return false;
    }
    for (int _col = col + 1; _col < N; _col++) {
        int _line = line;
        if (inGrid(_line, _col) && blocNumber == cages[_line * N + _col]) return false;
    }
    return true;
}

static bool numberPossible(std::vector<int>& sums, std::vector<int>& cages, int line, int col, int digit) {
    if (endBloc(cages, line, col)) {
        return digit == sums[line * N + col];
    }
    return digit < sums[line * N + col];
}

static bool notOnRow(std::vector<int>& solution, int row, int digit) {
    for (int i = 0; i < N; i++) if (solution[row * N + i] == digit) return false;
    return true;
}

static bool notOnColumn(std::vector<int>& solution, int col, int digit) {
    for (int i = 0; i < N; i++) if (solution[i * N + col] == digit) return false;
    return true;
}

static bool notOnSquare(std::vector<int>& solution, int row, int col, int digit) {
    int _i = (row / boxSize) * boxSize;
    int _j = (col / boxSize) * boxSize;
    for (int i = _i; i < _i + boxSize; i++) {
        for (int j = _j; j < _j + boxSize; j++) {
            if (solution[i * N + j] == digit) return false;
        }
    }
    return true;
}

static void substract(std::vector<int>& sums, std::vector<int>& cages, int line, int col, int value, int blocNumber, std::vector<char>& shape) {
    if (inGrid(line, col) && cages[line * N + col] == blocNumber && !shape[line * N + col]) {
        sums[line * N + col] -= value;
        shape[line * N + col] = 1;
        substract(sums, cages, line, col + 1, value, blocNumber, shape);
        substract(sums, cages, line, col - 1, value, blocNumber, shape);
        substract(sums, cages, line + 1, col, value, blocNumber, shape);
        substract(sums, cages, line - 1, col, value, blocNumber, shape);
    }
}

static void add(std::vector<int>& sums, std::vector<int>& cages, int line, int col, int value, int blocNumber, std::vector<char>& shape) {
    if (inGrid(line, col) && cages[line * N + col] == blocNumber && shape[line * N + col]) {
        sums[line * N + col] += value;
        shape[line * N + col] = 0;
        add(sums, cages, line, col + 1, value, blocNumber, shape);
        add(sums, cages, line, col - 1, value, blocNumber, shape);
        add(sums, cages, line + 1, col, value, blocNumber, shape);
        add(sums, cages, line - 1, col, value, blocNumber, shape);
    }
}

static bool solver(std::vector<int>& sums, std::vector<int>& cages, std::vector<int>& solution, std::vector<int>& givens, int box) {
    if (box == N * N) return true;

    int line = box / N;
    int col = box % N;

    int forcedDigit = givens[line * N + col];
    int loFrom = forcedDigit != 0 ? forcedDigit : 1;
    int loTo = forcedDigit != 0 ? forcedDigit : N;

    for (int digit = loFrom; digit <= loTo; digit++) {
        if (numberPossible(sums, cages, line, col, digit) && notOnRow(solution, line, digit) &&
            notOnColumn(solution, col, digit) && notOnSquare(solution, line, col, digit)) {

            solution[line * N + col] = digit;

            std::vector<char> shape(N * N, 0);
            substract(sums, cages, line, col, digit, cages[line * N + col], shape);

            if (solver(sums, cages, solution, givens, box + 1)) return true;

            add(sums, cages, line, col, digit, cages[line * N + col], shape);
        }
    }
    solution[line * N + col] = 0;
    return false;
}

// sums: flat N*N array, the cage's target sum repeated across every cell of that cage.
// cages: flat N*N array of cage ids (unrelated cells must use different ids).
// givens: flat N*N array, non-zero to force a cell's value (0 = free). May be all zero.
// solutionOut: flat N*N array, filled with the solution in place.
// Returns 1 if solved, 0 otherwise.
int solve(int* sumsPtr, int* cagesPtr, int* givensPtr, int* solutionOutPtr, int boxSizeIn) {
    boxSize = boxSizeIn;
    N = boxSize * boxSize;

    std::vector<int> sums(sumsPtr, sumsPtr + N * N);
    std::vector<int> cages(cagesPtr, cagesPtr + N * N);
    std::vector<int> givens(givensPtr, givensPtr + N * N);
    std::vector<int> solution(N * N, 0);

    bool solved = solver(sums, cages, solution, givens, 0);
    if (solved) {
        for (int i = 0; i < N * N; i++) solutionOutPtr[i] = solution[i];
    }
    return solved ? 1 : 0;
}

} // namespace killer_sudoku
