#include <iostream>
#include <iomanip>
#include <stdbool.h>

using namespace std;

#define Print 0 // <1> for printing the result and <0> for nothing

//  <SudokuKillerGrid> 
// index
// <0> values of the grid
// <1> structure to indentify the blocs of the grid
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
    {10,12,12,11,11,14,14,14,13}},
};

int Solution[100][9][9] = { 0 };
// the Solution[99][0][0] is the number of solutions

// compare two grid if the grid are equal return <1> if not return <0>
bool SolutionStore(int Solution[100][9][9], int SuguruGrid[2][9][9]);

// copy a solution into the solution tab
void CopySolution(int Solution[100][9][9], int SuguruGrid[2][9][9]);

// main function of the backtracking algo
bool Solver(int Solution[100][9][9], int SuguruGrid[2][9][9], int Box);

// retrun <1> if the box(line, column) is in the grid <0> if it's not the case
bool InGrid(int line, int column);

// return the number of box of a bloc
int NumberBox(int SuguruGrid[2][9][9], int line, int column, int BlocNumber, bool BlocShape[9][9]);

// function that check if there is not already the <digit> in the bloc of the Suguru
// return <1> if it's the case and <0> if it's not
bool NotOnBloc(int SuguruGrid[2][9][9], int line, int column, int BlocNumber, bool BlocShape[9][9], int digit);


// function that check if there is not already the <digit> arround the box
// return <1> if it's the case and <0> if it's not
bool NotAround(int SuguruGrid[2][9][9], int line, int column, int digit);


// function that print the grid
// option is the part of the grid want to be seen
void PrintGrid(int SuguruGrid[2][9][9], int Option);

int main()
{
    cout << "\n----------------------------\n";
    cout << "Solving the Suguru";
    cout << "\n----------------------------\n\n";

    PrintGrid(SuguruGridEasy1, 0);
     cout << "\n";
    PrintGrid(SuguruGridEasy1, 1);

    // The Solver begin with the zero index
    Solver(Solution, SuguruGridEasy1, 0);
    
    int NumberSolution = Solution[99][0][0];

    if (NumberSolution > 0) {

        cout << "\n----------------------------\n";
        cout << "Solved Suguru";
        cout << "\n----------------------------\n\n";

        for (int i = 0; i < NumberSolution; i++) {
            cout << "Solution " << (i + 1) << ":\n\n";
            PrintGrid(Solution, i);
        }
        cout << "----------------------------\n";
    }
    else {
        cout << "\n----------------------------\n";
        cout << "Suguru not solvable";
        cout << "\n----------------------------\n";
    }
}

bool Solver(int Solution[100][9][9], int SuguruGrid[2][9][9], int Box) {

    // check if the grid is completed
    if (Box == 81) {
        if (SolutionStore(Solution, SuguruGrid)) {
            return false;
        }
        else {
            CopySolution(Solution, SuguruGrid);
            return false;
        }
    }

    // convert the box number to (line, column) coordinate
    int line = Box / 9;
    int column = Box % 9;

    if (SuguruGrid[0][line][column] != 0) {
        return Solver(Solution, SuguruGrid, Box + 1);
    }

    if (Print) {
        cout << "\nbox " << Box << " line " << line << " column " << column;
        cout << "\n\n";

        PrintGrid(SuguruGrid, 0); // the grid 
    }

    bool BlocShape1[9][9] = { 0 };
    int NumBoxBloc = NumberBox(SuguruGrid, line, column, SuguruGrid[1][line][column], BlocShape1);

    for (int digit = 1; digit <= NumBoxBloc; digit++) {

        int BlocNumber = SuguruGrid[1][line][column];
        bool BlocShape2[9][9] = { 0 };

        if (NotAround(SuguruGrid, line, column, digit) && NotOnBloc(SuguruGrid, line, column, BlocNumber, BlocShape2, digit)) {

            SuguruGrid[0][line][column] = digit;

            if (Solver(Solution, SuguruGrid, Box + 1) == true) {
                return true;
            }

        }
    }
    // if there is no digit possible in box
    SuguruGrid[0][line][column] = 0;
    return false;
}

// return the number of box of a bloc
int NumberBox(int SuguruGrid[2][9][9], int line, int column, int BlocNumber, bool BlocShape[9][9]) {

    int Count = 0;

    if (InGrid(line, column) && SuguruGrid[1][line][column] == BlocNumber && !(BlocShape[line][column])) {

        Count = 1;
        BlocShape[line][column] = 1;

        Count += NumberBox(SuguruGrid, line, column + 1, BlocNumber, BlocShape);
        Count += NumberBox(SuguruGrid, line, column - 1, BlocNumber, BlocShape);
        Count += NumberBox(SuguruGrid, line + 1, column, BlocNumber, BlocShape);
        Count += NumberBox(SuguruGrid, line - 1, column, BlocNumber, BlocShape);


    }

    return Count;
}

// function that check if there is not already the <digit> in the bloc of the Suguru
// return <1> if it's the case and <0> if it's not
bool NotOnBloc(int SuguruGrid[2][9][9], int line, int column, int BlocNumber, bool BlocShape[9][9], int digit) {

    if (InGrid(line, column) && SuguruGrid[1][line][column] == BlocNumber && !(BlocShape[line][column])) {

        if (SuguruGrid[0][line][column] == digit) {
            return false;
        }

        BlocShape[line][column] = 1;

        if (!(NotOnBloc(SuguruGrid, line, column + 1, BlocNumber, BlocShape, digit))) {
            return false;
        }
        if (!(NotOnBloc(SuguruGrid, line, column - 1, BlocNumber, BlocShape, digit))) {
            return false;
        }
        if (!(NotOnBloc(SuguruGrid, line + 1, column, BlocNumber, BlocShape, digit))) {
            return false;
        }
        if (!(NotOnBloc(SuguruGrid, line - 1, column, BlocNumber, BlocShape, digit))) {
            return false;
        }
    }
    return true;
}

// function that check if there is not already the <digit> arround the box
// return <1> if it's the case and <0> if it's not
bool NotAround(int SuguruGrid[2][9][9], int line, int column, int digit) {

    for (int i = line - 1; i <= line + 1; i++) {
        for (int j = column - 1; j <= column + 1; j++) {
            if (InGrid(i, j)) {
                if (SuguruGrid[0][i][j] == digit) {
                    return false;
                }

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

// function that print the grid
// option is the part of the grid want to be seen
void PrintGrid(int SuguruGrid[2][9][9], int Option) {
    for (int l = 0; l < 9; l++) {
        for (int c = 0; c < 9; c++) {
            cout << setw(3) << SuguruGrid[Option][l][c];
        }
        cout << "\n";
    }
}

// compare two grid if the grid are equal return <1> if not return <0>
bool SolutionStore(int Solution[100][9][9], int SuguruGrid[2][9][9]) {

    int NumSolution = Solution[99][0][0];

    for (int sol = 0; sol < NumSolution; sol++) {
        int Count = 0;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (Solution[sol][i][j] == SuguruGrid[0][i][j]) {
                    Count++;
                }
            }
        }
        if (Count == 81) {
            return true;
        }
    }
    return false;
}

// copy a solution into the solution tab
void CopySolution(int Solution[100][9][9], int SuguruGrid[2][9][9]) {

    int NumSolution = Solution[99][0][0];

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            Solution[NumSolution][i][j] = SuguruGrid[0][i][j];
        }
    }
    Solution[99][0][0]++;
}