#include <iostream>
#include <iomanip>
#include <stdbool.h>

using namespace std;

#define Print 0 // <1> for printing the result and <0> for nothing

//  <SudokuKillerGrid> 
// index
// <0> values of the grid
// <1> structure to indentify the blocs of the grid
// <2> the solved sudoku killer
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
    { 0, 0, 0, 0, 0, 0, 0, 0, 0}},
};

int SudokuKillerGridHard8[3][9][9] = {

   {{ 7, 7,20,27,27, 5,28,28,12},
    { 7,20,20,27,27, 5,28,28,12},
    {18,18,18,12, 7,21,28,21,12},
    {17,10, 8,12, 7,21, 7,21,21},
    {17,10, 8,12,17,21, 7,21,14},
    {12,12, 8,12,17,16,14,14,14},
    {12,26,26,26,15,16,14,14,22},
    {12,12,26,15,15,16,16,22,22},
    { 8, 8, 8,14,14,14,15,15,22}},

   {{ 1, 1, 2, 3, 3, 4, 5, 5, 6},
    { 1, 2, 2, 3, 3, 4, 5, 5, 6},
    { 7, 7, 7, 8, 9,10, 5,11, 6},
    {12,13,14, 8, 9,10,15,11,11},
    {12,13,14, 8,16,10,15,11,17},
    {18,18,14, 8,16,19,20,20,17},
    {18,21,21,21,22,19,20,20,23},
    {24,24,21,22,22,19,19,23,23},
    {25,25,25,26,26,26,27,27,23}},

   {{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0}},
};

// main function of the backtracking algo
bool Solver(int SudokuKillerGrid[3][9][9], int Box);

// substract a value to all the boxes that are on the bloc as the box(column, value)
void Substract(int SudokuKillerGrid[3][9][9], int line, int column, int value, int BlocNumber, bool BlocShape[9][9]);

// add a value to all the boxes that are on the bloc as the box(column, value)
void Add(int SudokuKillerGrid[3][9][9], int line, int column, int value, int BlocNumber, bool BlocShape[9][9]);

// function that check if a value is possible on the box(line, column) in term of addition
//  return <1> if the digit is possible and <0> if it's not the case
// the endline and endcolumn boxes require a particular process
bool NumberPossible(int SudokuKillerGrid[3][9][9], int line, int column, int digit);

// return <1> if the box(line, column) is at the end of the bloc and <0> if it's not the case
bool EndBloc(int SudokuKillerGrid[3][9][9], int line, int column);

// retrun <1> if the box(line, column) is in the grid <0> if it's not the case
bool InGrid(int line, int column);

// function that check if there is not already the <digit> in the <line>
// return <1> if it's the case and <0> if it's not
bool NotOnRow(int SudokuKiller[3][9][9], int row, int column, int value);

// function that check if there is not already the <digit> in the <column>
// return <1> if it's the case and <0> if it's not
bool NotOnColumn(int SudokuKiller[3][9][9], int row, int column, int value);

// function that check if there is not already the <digit> in the square of the sudoku
// return <1> if it's the case and <0> if it's not
bool NotOnSquare(int SudokuKiller[3][9][9], int row, int column, int value);

// function that print the grid
// option is the part of the grid want to be seen
void PrintGrid(int SudokuKiller[3][9][9], int Option);

int main()
{
    cout << "\n----------------------------\n";
    cout << "Solving the Sudoku Killer";
    cout << "\n----------------------------\n";
    PrintGrid(SudokuKillerGridEasy1, 0);
    cout << "\n";
    PrintGrid(SudokuKillerGridEasy1, 1);
    cout << "----------------------------";

    // The Solver begin with the zero index 
    if (Solver(SudokuKillerGridEasy1, 0)) {
        cout << "\n----------------------------\n";
        cout << "Sudoku Killer Solved";
        cout << "\n----------------------------\n";
        PrintGrid(SudokuKillerGridEasy1, 2);
        cout << "----------------------------\n";
    }
    else {
        cout << "\n----------------------------\n";
        cout << "Sudoku Killer not solvable";
        cout << "\n----------------------------\n";
    }
}

bool Solver(int SudokuKillerGrid[3][9][9], int Box) {

    // check if the grid is completed
    if (Box == 81) {
        return true;
    }

    // convert the box number to (line, column) coordinate
    int line = Box / 9;
    int column = Box % 9;

    if (Print) {
        cout << "\nbox " << Box << " line " << line << " column " << column;
        cout << "\n\n";

        PrintGrid(SudokuKillerGrid, 2); // the grid 
        PrintGrid(SudokuKillerGrid, 0); // the values
    }

    for (int digit = 1; digit <= 9; digit++) {

        if (NumberPossible(SudokuKillerGrid, line, column, digit) && NotOnRow(SudokuKillerGrid, line, column, digit) && NotOnColumn(SudokuKillerGrid, line, column, digit) && NotOnSquare(SudokuKillerGrid, line, column, digit)) {

            SudokuKillerGrid[2][line][column] = digit;

            // <BlocShape> Table that represent the structure of a certain bloc
            bool BlocShape[9][9] = { 0 };
            // substract a value on a bloc 
            Substract(SudokuKillerGrid, line, column, digit, SudokuKillerGrid[1][line][column], BlocShape);

            if (Solver(SudokuKillerGrid, Box + 1) == true) {
                return true;
            }
            // add a value on a bloc 
            Add(SudokuKillerGrid, line, column, digit, SudokuKillerGrid[1][line][column], BlocShape);

        }
    }
    // if there is no digit possible in box
    SudokuKillerGrid[2][line][column] = 0;
    return false;
}

// substract a value to all the boxes that are on the bloc as the box(column, value)
void Substract(int SudokuKillerGrid[3][9][9], int line, int column, int value, int BlocNumber, bool BlocShape[9][9]) {

    if (InGrid(line, column) && SudokuKillerGrid[1][line][column] == BlocNumber && !(BlocShape[line][column])) {
        // if the box is part of the bloc and we not already pass on it
        // substract the value on all the boxes of the bloc
        SudokuKillerGrid[0][line][column] = SudokuKillerGrid[0][line][column] - value;

        // every box that are be pass are store in <BlocShape>
        BlocShape[line][column] = 1;

        Substract(SudokuKillerGrid, line, column + 1, value, BlocNumber, BlocShape); // right value
        Substract(SudokuKillerGrid, line, column - 1, value, BlocNumber, BlocShape); // left value 
        Substract(SudokuKillerGrid, line + 1, column, value, BlocNumber, BlocShape); // below value
        Substract(SudokuKillerGrid, line - 1, column, value, BlocNumber, BlocShape); // up value
    }
}

// add a value to all the boxes that are on the bloc as the box(column, value)
// add come after the substract so BlocNumber will be define
void Add(int SudokuKillerGrid[3][9][9], int line, int column, int value, int BlocNumber, bool BlocShape[9][9]) {

    if (InGrid(line, column) && SudokuKillerGrid[1][line][column] == BlocNumber && (BlocShape[line][column])) {
        // if the box is part of the bloc
        // add the value on all the boxes of the bloc
        SudokuKillerGrid[0][line][column] = SudokuKillerGrid[0][line][column] + value;

        // every box that are be pass on we put a 0
        BlocShape[line][column] = 0;

        Add(SudokuKillerGrid, line, column + 1, value, BlocNumber, BlocShape); // right value
        Add(SudokuKillerGrid, line, column - 1, value, BlocNumber, BlocShape); // left value 
        Add(SudokuKillerGrid, line + 1, column, value, BlocNumber, BlocShape); // below value
        Add(SudokuKillerGrid, line - 1, column, value, BlocNumber, BlocShape); // up value
    }
}


// function that check if a value is possible on the box(line, column) in term of addition
//  return <1> if the digit is possible and <0> if it's not the case
// the endline and endcolumn boxes require a particular process
bool NumberPossible(int SudokuKillerGrid[3][9][9], int line, int column, int digit) {

    if (EndBloc(SudokuKillerGrid, line, column)) { // if the box it's at the end of bloc
        if (digit == SudokuKillerGrid[0][line][column]) { // the value of the box has to be equal the digjt 
            return true;
        }
        else {
            return false;
        }
    }
    else {
        if (digit < SudokuKillerGrid[0][line][column]) {
            return true;
        }
        else {
            return false;
        }

    }
}

// return <1> if the box(line, column) is at the end of the bloc and <0> if it's not the case
// the function look for a variable on a line below the box and on line after the box if a box of the same bloc is found this is not the end of the bloc
bool EndBloc(int SudokuKillerGrid[3][9][9], int line, int column) {

    int BlocNumber = SudokuKillerGrid[1][line][column];

    // line below the box
    for (int _column = 0; _column <= column; _column++) {
        int _line = line + 1;
        if (InGrid(_line, _column)) {
            if (BlocNumber == SudokuKillerGrid[1][_line][_column]) {
                return false;
            }
        }
    }
    // line after the box
    for (int _column = column + 1; _column < 9; _column++) {
        int _line = line;
        if (InGrid(_line, _column)) {
            if (BlocNumber == SudokuKillerGrid[1][_line][_column]) {
                return false;
            }
        }
    }
    return true;
}

// retrun <1> if the box(line, column) is in the grid <0> if it's not the case
bool InGrid(int line, int column) {
    if (line >= 0 && line <= 8 && column >= 0 && column <= 8) {
        return true;
    }
    else {
        return false;
    }
}

// function that check if there is not already the <digit> in the <line>
// return <1> if it's the case and <0> if it's not
bool NotOnRow(int SudokuKiller[3][9][9], int row, int column, int value) {
    for (int i = 0; i < 9; i++) {
        if (SudokuKiller[2][row][i] == value) {
            return false;
        }
    }
    //cout << value << "\n Not on row \n";
    return true;
}

// function that check if there is not already the <digit> in the <column>
// return <1> if it's the case and <0> if it's not
bool NotOnColumn(int SudokuKiller[3][9][9], int row, int column, int value) {
    for (int i = 0; i < 9; i++) {
        if (SudokuKiller[2][i][column] == value) {
            return false;
        }
    }
    return true;
}

// function that check if there is not already the <digit> in the square of the sudoku
// return <1> if it's the case and <0> if it's not
bool NotOnSquare(int SudokuKiller[3][9][9], int row, int column, int value) {
    int _i = (row / 3) * 3; // position (_i,_j) of the first cell of the square's value 
    int _j = (column / 3) * 3;

    // go on each box of the square
    for (int i = _i; i < _i + 3; i++) {
        for (int j = _j; j < _j + 3; j++) {
            if (SudokuKiller[2][i][j] == value) {
                return false;
            }
        }
    }
    return true;
}

// function that print the grid
// option is the part of the grid want to be seen
void PrintGrid(int SudokuKiller[3][9][9], int Option) {
    for (int l = 0; l < 9; l++) {
        for (int c = 0; c < 9; c++) {
            cout << setw(3) << SudokuKiller[Option][l][c];
        }
        cout << "\n";
    }
}