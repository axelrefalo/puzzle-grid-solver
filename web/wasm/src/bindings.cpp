#include "sudoku.cpp"
#include "suguru.cpp"
#include "killer_sudoku.cpp"
#include "kakuro.cpp"

extern "C" {

int solve_sudoku(int* grid, int boxSize) {
    return sudoku::solve(grid, boxSize);
}

int solve_suguru(int* values, int* regions, int rows, int cols) {
    return suguru::solve(values, regions, rows, cols);
}

int solve_killer_sudoku(int* sums, int* cages, int* givens, int* solutionOut, int boxSize) {
    return killer_sudoku::solve(sums, cages, givens, solutionOut, boxSize);
}

int solve_kakuro(int* horizSums, int* vertSums, int* prefilled, int* solutionOut, int rows, int cols) {
    return kakuro::solve(horizSums, vertSums, prefilled, solutionOut, rows, cols);
}

} // extern "C"
