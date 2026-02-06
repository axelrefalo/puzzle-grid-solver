

#include <iostream>
#include <iomanip>
#include <stdbool.h>

using namespace std;

#define Print 0 // <1> for printing the result and <0> for nothing

//  <KakuroGrid> 
// index
// <0> horizontal values of the grid
// <1> vertical values of the grid
// <2> the value that are already in the grid
// <3> the solved Kakuro
int KakuroGrid1[4][9][9] = {

    {{0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,14,14,0,10,10,0},
    {0,0,31,31,31,31,31,31,0},
    {0,0,8,8,0,9,9,0,0},
    {0,0,8,8,0,0,8,8,0},
    {0,0,24,24,24,24,24,24,0},
    {0,0,0,0,15,15,0,0,0},
    {0,0,0,0,0,0,0,0,0}},

    {{0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,27,7,0,18,10,0},
    {0,0,22,27,7,15,18,10,0},
    {0,0,22,27,0,15,18,0,0},
    {0,0,22,27,0,0,18,8,0},
    {0,0,22,27,8,12,18,8,0},
    {0,0,0,0,8,12,0,0,0},
    {0,0,0,0,0,0,0,0,0}},

    {{0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,3,0,0,0,0,0},
    {0,0,3,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,8,0,0,0,1,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0}},

    {{0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0}},
};

int KakuroGrid8[4][9][9] = {

   {{0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,12,12,0,12,12,0,0},
    {0,0,30,30,30,30,30,30,0},
    {0,0,0,6,6,0,10,10,0},
    {0,0,13,13,0,7,7,0,0},
    {0,0,31,31,31,31,31,31,0},
    {0,0,0,7,7,0,7,7,0},
    {0,0,0,0,0,0,0,0,0}},

   {{0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,13,31,0,13,36,0,0},
    {0,0,13,31,7,13,36,3,0},
    {0,0,0,31,7,0,36,3,0},
    {0,0,7,31,0,7,36,0,0},
    {0,0,7,31,5,7,36,13,0},
    {0,0,0,31,5,0,36,13,0},
    {0,0,0,0,0,0,0,0,0}},

   {{0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,0,0},
    {0,0,0,0,2,0,0,0,0},
    {0,0,4,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0}},

   {{0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0}},

};

int KakuroGrid24[4][9][9] = {

   {{0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0,15,15, 0,17,17, 0, 0},
    {0, 0,33,33,33,33,33,33, 0},
    {0, 0, 0,15,15, 0,10,10, 0},
    {0, 0, 0,10,10, 0,10,10, 0},
    {0, 0,30,30,30,30,30,30, 0},
    {0, 0,13,13, 0, 6, 6, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0}},

   {{0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0,15,30, 0,13,33, 0, 0},
    {0, 0,15,30,24,13,33,20, 0},
    {0, 0, 0,30,24, 0,33,20, 0},
    {0, 0, 0,30,24, 0,33,20, 0},
    {0, 0,10,30,24,14,33,20, 0},
    {0, 0,10,30, 0,14,33, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0}},

   {{0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,2,0,0,0,0,0},
    {0,0,0,0,7,0,0,0,0},
    {0,0,0,0,0,0,0,1,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,4,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0}},

   {{0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0}},

};

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

   {{0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,4,0,0},
    {0,0,0,3,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,9,0,3,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0}},

   {{0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0}},

};



// main function of the backtracking algo
bool Solver(int KakuroGrid[4][9][9], int Box);

// substract a value to all the boxes that are on the right and under the boxe's value
void Substract(int KakuroGrid[4][9][9], int line, int column, int value);

// add a value to all the boxes that are on the right and under the boxe's value
void Add(int KakuroGrid[4][9][9], int line, int column, int value);

// function that check if a value is possible on the box(line, column) in term of addition
// return <1> if the digit is possible and <0> if it's not the case
// the endline and endcolumn boxes require a particular process
bool NumberPossible(int KakuroGrid[4][9][9], int line, int column, int digit);

// return <1> if the box(line, column) is at the end of the line and <0> if it's not the case
bool EndLine(int KakuroGrid[4][9][9], int line, int column);

// return <1> if the box(line, column) is at the end of the column and <0> if it's not the case
bool EndColumn(int KakuroGrid[4][9][9], int line, int column);

// function that check if there is not already the <digit> in the <line> and the <column>
// return <1> if it's the case and <0> if it's not
bool NotInLineAndColumn(int KakuroGrid[4][9][9], int line, int column, int digit);

// function that print the grid
// option is the part of the grid want to be seen
void PrintGrid(int KakuroGrid[4][9][9], int Option);

int main()
{   
    cout << "\n----------------------------\n";
    cout << "Input Kakuro";
    cout << "\n----------------------------\n";
    PrintGrid(KakuroGrid14, 0);
    cout << "\n";
    PrintGrid(KakuroGrid14, 1);
    cout << "----------------------------";
    

    // The Solver begin with the zero index 
    if (Solver(KakuroGrid14, 0)) {
        cout << "\n----------------------------\n";
        cout << "Solved Kakuro";
        cout << "\n----------------------------\n";
        PrintGrid(KakuroGrid14, 3);
        cout << "----------------------------\n";
    }
    else {
        cout << "\n----------------------------\n";
        cout << "Kakuro not solvable";
        cout << "\n----------------------------\n";
    }
}

bool Solver(int KakuroGrid[4][9][9], int Box) {

    // check if the grid is completed
    if (Box == 81) {
        // faire une fontion pour voir si c'est une unique solution
        return true;
    }

    // convert the box number to (line, column) coordinate
    int line = Box / 9;
    int column = Box % 9;

    if (Print) {
        cout << " box " << Box << " line " << line << " column " << column << "\n";
        if (EndLine(KakuroGrid, line, column)) {
            cout << " EndLine ";
        }
        if (EndColumn(KakuroGrid, line, column)) {
            cout << " EndColumn ";
        }
        cout << "\n\n";
        PrintGrid(KakuroGrid, 3); // the grid
        //PrintGrid(KakuroGrid, 0); // the horizontal values
        //PrintGrid(KakuroGrid, 1); // the vertical values
    }

    // if it's a 0 on the Box go to the next box
    if (KakuroGrid[0][line][column] == 0) {
        return Solver(KakuroGrid, Box + 1);
    }

    // Faire une fonction qui remplit un tableau avec les valeurs possibles 
    // ex : value et nbValue, passes par adresse 
    // Puis les parcourir et appeler le bloc substract / solver / add

    // check if there is already a digit in the row
    if (KakuroGrid[2][line][column] == 0) {
        for (int digit = 1; digit <= 9; digit++) {
            if (NumberPossible(KakuroGrid, line, column, digit) && NotInLineAndColumn(KakuroGrid, line, column, digit)) {
                //cout << digit << " possible ";
                KakuroGrid[3][line][column] = digit;
                Substract(KakuroGrid, line, column, digit);

                if (Solver(KakuroGrid, Box + 1) == true) {
                    return true;
                }

                Add(KakuroGrid, line, column, digit);

            }
        }
    }else { // if there is already a digit
        int digit = KakuroGrid[2][line][column];

        if (NumberPossible(KakuroGrid, line, column, digit) && NotInLineAndColumn(KakuroGrid, line, column, digit)) {
            
            KakuroGrid[3][line][column] = digit;
            Substract(KakuroGrid, line, column, digit);
            if (Solver(KakuroGrid, Box + 1) == true) {
                return true;
            }
            Add(KakuroGrid, line, column, digit);
        }
        
    }

    // if there is no digit possible in box
    KakuroGrid[3][line][column] = 0;
    return false;
}

// substract a value to all the boxes that are on the right and under the boxe's value
void Substract(int KakuroGrid[4][9][9], int line, int column, int value) {

    // substract the value to the right line of the box(line, column)
    int index1 = column + 1; // first index
    int digit = KakuroGrid[0][line][index1]; // value on the box

    while(digit > 0 && index1 < 9){
        KakuroGrid[0][line][index1] = KakuroGrid[0][line][index1] - value;
        index1++;
        if (index1 < 9) {
            digit = KakuroGrid[0][line][index1];
        }
    }

    // substract the value on the column under the box(line, column)
    index1 = line + 1;
    digit = KakuroGrid[1][index1][column];

    while (digit > 0 && index1 < 9) {
        KakuroGrid[1][index1][column] = KakuroGrid[1][index1][column] - value;
        index1++;
        if (index1 < 9) {
            digit = KakuroGrid[1][index1][column];
        }
    }
}

// add a value to all the boxes that are on the right and under the boxe's value
void Add(int KakuroGrid[4][9][9], int line, int column, int value) {

    // add the value to the right line of the box(line, column)
    int index1 = column + 1; // first index
    int digit = KakuroGrid[0][line][index1]; // value on the bpx

    while (digit > 0 && index1 < 9) {
        KakuroGrid[0][line][index1] = KakuroGrid[0][line][index1] + value;
        index1++;
        if (index1 < 9) {
            digit = KakuroGrid[0][line][index1];
        }
    }

    // add the value on the column under the box(line, column)
    index1 = line + 1;
    digit = KakuroGrid[1][index1][column];

    while (digit > 0 && index1 < 9) {
        KakuroGrid[1][index1][column] = KakuroGrid[1][index1][column] + value;
        index1++;
        if (index1 < 9) {
            digit = KakuroGrid[1][index1][column];
        }
    }
}

// function that check if a value is possible on the box(line, column) in term of addition
// return <1> if the digit is possible and <0> if it's not the case
// the endline and endcolumn boxes require a particular process
bool NumberPossible(int KakuroGrid[4][9][9], int line, int column, int digit) {
    
    bool EndOfLine = EndLine(KakuroGrid, line, column);
    bool EndOfColumn = EndColumn(KakuroGrid, line, column);
    
    if (EndOfLine && EndOfColumn) { // if the box is at the end of a line and a column the digit have to be equal to each value
        if (KakuroGrid[0][line][column] == digit && KakuroGrid[1][line][column] == digit) {
            return true;
        }else {
            return false;
        }
    }else if (EndOfLine) { // box at the end of a line
        if (KakuroGrid[0][line][column] == digit && digit < KakuroGrid[1][line][column]) { //
            return true;
        }else {
            return false;
        }
    }else if (EndOfColumn) { // box at the end of column 

        if (KakuroGrid[1][line][column] == digit && digit < KakuroGrid[0][line][column]) {
            return true;
        }else {
            return false;
        }
    }else { // if the value is not at any end
        if (digit < KakuroGrid[0][line][column] && digit < KakuroGrid[1][line][column]) {
            return true;
        }else {
            return false;
        }
    }
}

// return <1> if the box(line, column) is at the end of the line and <0> if it's not the case
bool EndLine(int KakuroGrid[4][9][9], int line, int column) {
    if (column + 1 > 8) { // if it's at a border of the Grid
        return true;
    }else if (KakuroGrid[0][line][column + 1] == 0) { // if the next box is 0
        return true;
    }else {
        return false;
    }
}

// return <1> if the box(line, column) is at the end of the column and <0> if it's not the case
bool EndColumn(int KakuroGrid[4][9][9], int line, int column) {
    if (line + 1 > 8) { // if it's at a border of the Grid
        return true;
    }else if (KakuroGrid[1][line + 1][column] == 0) { // if the next box is 0
        return true;
    }else {
        return false;
    }
}

// function that check if there is not already the <digit> in the <line> and the <column>
// return <1> if it's the case and <0> if it's not
bool NotInLineAndColumn(int KakuroGrid[4][9][9], int line, int column, int digit) {
    
    // check on the left of the box(line, column) 
    int index1 = column - 1;
    int PreviousValue = KakuroGrid[0][line][index1];

    while (PreviousValue > 0 && index1 >= 0) {
        if (KakuroGrid[3][line][index1] == digit) {
            return false;
        }
        index1 = index1 - 1;
        if (index1 >= 0) {
            PreviousValue = KakuroGrid[0][line][index1];
        }
    }

    // check on the top of the box(line, column) 
    index1 = line - 1;
    PreviousValue = KakuroGrid[1][index1][column];

    while (PreviousValue > 0 && index1 >= 0) {
        if (KakuroGrid[3][index1][column] == digit) {
            return false;
        }
        index1 = index1 - 1;
        if (index1 >= 0) {
            PreviousValue = KakuroGrid[1][index1][column];
        }
    }
    return true; 
}

// function that print the grid
// option is the part of the grid want to be seen
void PrintGrid(int KakuroGrid[4][9][9], int Option) {
    for (int l = 0; l < 9; l++) {
        for (int c = 0; c < 9; c++) {
            cout << setw(3) << KakuroGrid[Option][l][c];  // 3 = largeur de colonne
        }
        cout << "\n";
    }
}
