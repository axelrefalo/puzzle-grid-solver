#include <vector>

// Dynamic-size port of ../../../src/SudokuSolver.cpp
// Grid is N x N where N = boxSize * boxSize, flattened row-major.
namespace sudoku {

static int boxSize;
static int N;

static bool notOnRow(int value, int row, std::vector<int>& grid) {
    for (int c = 0; c < N; c++) {
        if (grid[row * N + c] == value) return false;
    }
    return true;
}

static bool notOnColumn(int value, int col, std::vector<int>& grid) {
    for (int r = 0; r < N; r++) {
        if (grid[r * N + col] == value) return false;
    }
    return true;
}

static bool notOnSquare(int value, int row, int col, std::vector<int>& grid) {
    int _i = (row / boxSize) * boxSize;
    int _j = (col / boxSize) * boxSize;
    for (int i = _i; i < _i + boxSize; i++) {
        for (int j = _j; j < _j + boxSize; j++) {
            if (grid[i * N + j] == value) return false;
        }
    }
    return true;
}

static bool solving(std::vector<int>& grid, int position) {
    if (position == N * N) return true;

    int row = position / N;
    int col = position % N;

    if (grid[row * N + col] != 0) {
        return solving(grid, position + 1);
    }

    for (int digit = 1; digit <= N; digit++) {
        if (notOnColumn(digit, col, grid) && notOnRow(digit, row, grid) && notOnSquare(digit, row, col, grid)) {
            grid[row * N + col] = digit;
            if (solving(grid, position + 1)) return true;
        }
    }
    grid[row * N + col] = 0;
    return false;
}

// grid: flat N*N array (0 = empty), solved in place. Returns 1 if solved, 0 otherwise.
int solve(int* gridPtr, int boxSizeIn) {
    boxSize = boxSizeIn;
    N = boxSize * boxSize;

    std::vector<int> grid(gridPtr, gridPtr + N * N);

    bool solved = solving(grid, 0);
    if (solved) {
        for (int i = 0; i < N * N; i++) gridPtr[i] = grid[i];
    }
    return solved ? 1 : 0;
}

} // namespace sudoku
