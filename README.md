# Puzzle-Grid-Solver

Set of algorithm (written in c++) that can solve Sudoku, Suguru, Killer Sudoku and Kakuro puzzles, using the backtracking method

## Sudoku 
Solve a sudoku grids using the backtracking method
file : `src/SudokuSolver.cpp`

For solving please replace the following table and run the code
```cpp
    int Grid[SIZE][SIZE] = {

    { 9, 0, 0, 1, 0, 0, 0, 0, 5},
    { 0, 0, 5, 0, 9, 0, 2, 0, 1},
    { 8, 0, 0, 0, 4, 0, 0, 0, 0},
    { 0, 0, 0, 0, 8, 0, 0, 0, 0},
    { 0, 0, 0, 7, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 2, 6, 0, 0, 9},
    { 2, 0, 0, 3, 0, 0, 0, 0, 6},
    { 0, 0, 0, 2, 0, 0, 9, 0, 0},
    { 0, 0, 1, 9, 0, 4, 5, 7, 0}};
                 
```

## Suguru
Solve a suguru grids using the backtracking method
file : `src/SuguruSolver.cpp`

For solving please replace the following table and run the code
* `0` first table is the value already placed in the grid
* `1` second table is the blocs indentification, use the different numbers to represent different blocs
  
```cpp
   int SuguruGridEasy1[2][9][9] = {

   {{ 0, 3, 7, 2, 0, 5, 4, 0, 0},
    { 1, 0, 0, 6, 0, 2, 3, 2, 0},
    { 4, 3, 2, 0, 4, 0, 4, 0, 3},
    { 0, 0, 0, 0, 2, 0, 0, 6, 0},
    { 7, 1, 7, 6, 0, 3, 5, 0, 7},
    { 0, 0, 0, 1, 4, 0, 6, 0, 2},
    { 1, 0, 0, 0, 7, 3, 0, 7, 1},
    { 2, 6, 7, 0, 1, 0, 0, 6, 0},
    { 4, 0, 0, 3, 0, 0, 1, 0, 5}},

   {{ 1, 2, 2, 2, 2, 3, 3, 3, 3},
    { 1, 2, 2, 2, 4, 4, 4, 3, 5},
    { 6, 6, 6, 6, 7, 5, 5, 5, 5},
    { 6, 8, 8, 8, 7, 7, 5, 5, 9},
    { 6, 6, 8, 7, 7, 7, 9, 9, 9},
    {10,10, 8, 8,11, 7, 9, 9, 9},
    {10,12,12, 8,11,13,13,13,13},
    {10,12,12,12,11,11,11,13,13},
    {10,12,12,11,11,14,14,14,13}},};
```

## KillerSudoku
Solve a killer sudoku grids using the backtracking method
file : `src/KillerSudokuSolver.cpp`

For solving please replace the following table and run the code
* `0` first table is the sum of the digit that need to be satisfy
* `1` second table is the blocs indentification, use the different numbers to represent different blocs
* `2` third table is the solution of the killer sudoku
  
```cpp
int SudokuKillerGridEasy1[3][9][9] = {

   {{13, 7, 7,12,12,17,20,20,20},
    {13, 9,11, 9, 9,17,11,10,10},
    {13, 9,11,16,17,17,11,10, 6},
    {13, 6, 6,16,12, 9,11,10, 6},
    {12,12,12,12,12, 9,11,12, 6},
    {13,13,12, 6, 6, 4, 4,12,15},
    {11,10,10, 7,17,17,19,19,15},
    {11,11,14, 7, 7,13,10,19,19},
    {11,11,14,14, 7,13,10,10,10}},

   {{ 1, 2, 2, 3, 3, 4, 5, 5, 5},
    { 1, 6, 7, 8, 8, 4, 9,10,10},
    {11, 6, 7,12, 4, 4, 9,13,14},
    {11,15,15,12,16,17,18,13,14},
    {19,19,20,20,16,17,18,21,14},
    {22,22,20,23,23,24,24,21,25},
    {26,27,27,28,29,29,30,30,25},
    {26,26,31,28,32,33,34,30,30},
    {35,35,31,31,32,33,34,36,36}},

   {{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0}},};
```

## Kakuro
Solve a killer sudoku grids using the backtracking method
file : `src/KakuroSolver.cpp`

For solving please replace the following table and run the code
* `0` first table is the horizontal sum of the digit that need to be satisfy
* `1` second table is the vertical sum of the digit that need to be satisfy
* `2` third table is the value already placed in the grid
* `3` forth table is the solution of the kakuro grid

```cpp
int KakuroGrid14[4][9][9] = {

   {{0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 4, 4, 0, 6, 6, 6, 0},
    {0, 0,24,24,24,24,24,24, 0},
    {0, 0, 0, 4, 4, 0,17,17, 0},
    {0, 0, 0, 0,17,17,17,17, 0},
    {0, 0,23,23,23,23,23, 0, 0},
    {0, 0,12,12, 0, 4, 4, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0}},

   {{0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 4,12, 0, 7,24,15, 0},
    {0, 0, 4,12,14, 7,24,15, 0},
    {0, 0, 0,12,14, 0,24,15, 0},
    {0, 0, 0, 0,14, 6,24,15, 0},
    {0, 0,12,17,14, 6,24, 0, 0},
    {0, 0,12,17, 0, 6,24, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0}},

   {{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 4, 0, 0},
    { 0, 0, 0, 3, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 9, 0, 3, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0}},

   {{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},};

```
