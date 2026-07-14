#include <vector>

// Dynamic-size port of ../../../src/KakuroSolver.cpp
// rows x cols grid, flattened row-major. horizSums/vertSums hold the remaining
// run sum, pre-expanded across every fillable cell of that run (same redundant
// format as the original hardcoded examples); 0 means "not part of a run in
// that direction" (blocked or clue-only cell).
namespace kakuro {

static int ROWS;
static int COLS;

static bool endLine(std::vector<int>& horiz, int line, int col) {
    if (col + 1 >= COLS) return true;
    return horiz[line * COLS + col + 1] == 0;
}

static bool endColumn(std::vector<int>& vert, int line, int col) {
    if (line + 1 >= ROWS) return true;
    return vert[(line + 1) * COLS + col] == 0;
}

static bool numberPossible(std::vector<int>& horiz, std::vector<int>& vert, int line, int col, int digit) {
    bool endOfLine = endLine(horiz, line, col);
    bool endOfColumn = endColumn(vert, line, col);

    if (endOfLine && endOfColumn) {
        return digit == horiz[line * COLS + col] && digit == vert[line * COLS + col];
    } else if (endOfLine) {
        return digit == horiz[line * COLS + col] && digit < vert[line * COLS + col];
    } else if (endOfColumn) {
        return digit == vert[line * COLS + col] && digit < horiz[line * COLS + col];
    } else {
        return digit < horiz[line * COLS + col] && digit < vert[line * COLS + col];
    }
}

static void substract(std::vector<int>& horiz, std::vector<int>& vert, int line, int col, int value) {
    int index1 = col + 1;
    int digit = index1 < COLS ? horiz[line * COLS + index1] : 0;
    while (digit > 0 && index1 < COLS) {
        horiz[line * COLS + index1] -= value;
        index1++;
        if (index1 < COLS) digit = horiz[line * COLS + index1];
    }

    index1 = line + 1;
    digit = index1 < ROWS ? vert[index1 * COLS + col] : 0;
    while (digit > 0 && index1 < ROWS) {
        vert[index1 * COLS + col] -= value;
        index1++;
        if (index1 < ROWS) digit = vert[index1 * COLS + col];
    }
}

static void add(std::vector<int>& horiz, std::vector<int>& vert, int line, int col, int value) {
    int index1 = col + 1;
    int digit = index1 < COLS ? horiz[line * COLS + index1] : 0;
    while (digit > 0 && index1 < COLS) {
        horiz[line * COLS + index1] += value;
        index1++;
        if (index1 < COLS) digit = horiz[line * COLS + index1];
    }

    index1 = line + 1;
    digit = index1 < ROWS ? vert[index1 * COLS + col] : 0;
    while (digit > 0 && index1 < ROWS) {
        vert[index1 * COLS + col] += value;
        index1++;
        if (index1 < ROWS) digit = vert[index1 * COLS + col];
    }
}

static bool notInLineAndColumn(std::vector<int>& horiz, std::vector<int>& vert, std::vector<int>& solution, int line, int col, int digit) {
    int index1 = col - 1;
    int previousValue = index1 >= 0 ? horiz[line * COLS + index1] : 0;
    while (previousValue > 0 && index1 >= 0) {
        if (solution[line * COLS + index1] == digit) return false;
        index1--;
        if (index1 >= 0) previousValue = horiz[line * COLS + index1];
    }

    index1 = line - 1;
    previousValue = index1 >= 0 ? vert[index1 * COLS + col] : 0;
    while (previousValue > 0 && index1 >= 0) {
        if (solution[index1 * COLS + col] == digit) return false;
        index1--;
        if (index1 >= 0) previousValue = vert[index1 * COLS + col];
    }
    return true;
}

static bool solver(std::vector<int>& horiz, std::vector<int>& vert, std::vector<int>& prefilled, std::vector<int>& solution, int box) {
    if (box == ROWS * COLS) return true;

    int line = box / COLS;
    int col = box % COLS;

    if (horiz[line * COLS + col] == 0) {
        return solver(horiz, vert, prefilled, solution, box + 1);
    }

    if (prefilled[line * COLS + col] == 0) {
        for (int digit = 1; digit <= 9; digit++) {
            if (numberPossible(horiz, vert, line, col, digit) && notInLineAndColumn(horiz, vert, solution, line, col, digit)) {
                solution[line * COLS + col] = digit;
                substract(horiz, vert, line, col, digit);

                if (solver(horiz, vert, prefilled, solution, box + 1)) return true;

                add(horiz, vert, line, col, digit);
            }
        }
    } else {
        int digit = prefilled[line * COLS + col];
        if (numberPossible(horiz, vert, line, col, digit) && notInLineAndColumn(horiz, vert, solution, line, col, digit)) {
            solution[line * COLS + col] = digit;
            substract(horiz, vert, line, col, digit);

            if (solver(horiz, vert, prefilled, solution, box + 1)) return true;

            add(horiz, vert, line, col, digit);
        }
    }

    solution[line * COLS + col] = 0;
    return false;
}

// horizSums/vertSums: flat rows*cols arrays, run sum repeated across every fillable cell of that run.
// prefilled: flat rows*cols array of given digits (0 = free).
// solutionOut: flat rows*cols array, filled with the solution in place.
// Returns 1 if solved, 0 otherwise.
int solve(int* horizSumsPtr, int* vertSumsPtr, int* prefilledPtr, int* solutionOutPtr, int rows, int cols) {
    ROWS = rows;
    COLS = cols;

    std::vector<int> horiz(horizSumsPtr, horizSumsPtr + rows * cols);
    std::vector<int> vert(vertSumsPtr, vertSumsPtr + rows * cols);
    std::vector<int> prefilled(prefilledPtr, prefilledPtr + rows * cols);
    std::vector<int> solution(rows * cols, 0);

    bool solved = solver(horiz, vert, prefilled, solution, 0);
    if (solved) {
        for (int i = 0; i < rows * cols; i++) solutionOutPtr[i] = solution[i];
    }
    return solved ? 1 : 0;
}

} // namespace kakuro
