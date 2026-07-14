#include <vector>

// Dynamic-size port of ../../../src/SuguruSolver.cpp
// values/regions are rows x cols, flattened row-major.
namespace suguru {

static int ROWS;
static int COLS;

static bool inGrid(int line, int col) {
    return line >= 0 && line < ROWS && col >= 0 && col < COLS;
}

// counts the size of the region (blob) containing (line, col), marking visited cells in shape
static int numberBox(std::vector<int>& regions, int line, int col, int blocNumber, std::vector<char>& shape) {
    int count = 0;
    if (inGrid(line, col) && regions[line * COLS + col] == blocNumber && !shape[line * COLS + col]) {
        count = 1;
        shape[line * COLS + col] = 1;
        count += numberBox(regions, line, col + 1, blocNumber, shape);
        count += numberBox(regions, line, col - 1, blocNumber, shape);
        count += numberBox(regions, line + 1, col, blocNumber, shape);
        count += numberBox(regions, line - 1, col, blocNumber, shape);
    }
    return count;
}

static bool notOnBloc(std::vector<int>& values, std::vector<int>& regions, int line, int col, int blocNumber, std::vector<char>& shape, int digit) {
    if (inGrid(line, col) && regions[line * COLS + col] == blocNumber && !shape[line * COLS + col]) {
        if (values[line * COLS + col] == digit) return false;
        shape[line * COLS + col] = 1;
        if (!notOnBloc(values, regions, line, col + 1, blocNumber, shape, digit)) return false;
        if (!notOnBloc(values, regions, line, col - 1, blocNumber, shape, digit)) return false;
        if (!notOnBloc(values, regions, line + 1, col, blocNumber, shape, digit)) return false;
        if (!notOnBloc(values, regions, line - 1, col, blocNumber, shape, digit)) return false;
    }
    return true;
}

static bool notAround(std::vector<int>& values, int line, int col, int digit) {
    for (int i = line - 1; i <= line + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            if (inGrid(i, j) && values[i * COLS + j] == digit) return false;
        }
    }
    return true;
}

static bool solver(std::vector<int>& values, std::vector<int>& regions, int box) {
    if (box == ROWS * COLS) return true;

    int line = box / COLS;
    int col = box % COLS;

    if (values[line * COLS + col] != 0) {
        return solver(values, regions, box + 1);
    }

    std::vector<char> shape1(ROWS * COLS, 0);
    int numBoxBloc = numberBox(regions, line, col, regions[line * COLS + col], shape1);

    for (int digit = 1; digit <= numBoxBloc; digit++) {
        int blocNumber = regions[line * COLS + col];
        std::vector<char> shape2(ROWS * COLS, 0);

        if (notAround(values, line, col, digit) && notOnBloc(values, regions, line, col, blocNumber, shape2, digit)) {
            values[line * COLS + col] = digit;
            if (solver(values, regions, box + 1)) return true;
        }
    }
    values[line * COLS + col] = 0;
    return false;
}

// values: flat rows*cols array (0 = empty), solved in place.
// regions: flat rows*cols array of region ids (unrelated cells must use different ids).
// Returns 1 if solved, 0 otherwise.
int solve(int* valuesPtr, int* regionsPtr, int rows, int cols) {
    ROWS = rows;
    COLS = cols;

    std::vector<int> values(valuesPtr, valuesPtr + rows * cols);
    std::vector<int> regions(regionsPtr, regionsPtr + rows * cols);

    bool solved = solver(values, regions, 0);
    if (solved) {
        for (int i = 0; i < rows * cols; i++) valuesPtr[i] = values[i];
    }
    return solved ? 1 : 0;
}

} // namespace suguru
