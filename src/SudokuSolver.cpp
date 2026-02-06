
#include <iostream>
#include <stdbool.h>
using namespace std;

#define SIZE 3

int Grid1[SIZE*SIZE][SIZE*SIZE] = {
                       {2,0,0,7,0,0,0,0,0},
                       {6,5,0,0,9,0,0,0,8},
                       {0,0,0,0,0,3,9,0,0},
                       {0,0,7,0,0,0,0,0,0},
                       {0,0,0,4,0,0,0,1,0},
                       {9,8,0,0,3,0,0,0,6},
                       {0,0,2,0,5,0,0,0,0},
                       {5,7,0,0,0,1,0,6,0},
                       {0,0,3,0,0,0,0,0,7} };

int Grid2[SIZE*SIZE][SIZE*SIZE] = {
                       {8,0,0,0,0,2,0,0,0},
                       {0,0,4,0,0,0,0,9,0},
                       {9,0,0,0,5,6,8,0,0},
                       {5,0,0,2,0,0,0,0,0},
                       {0,0,3,0,7,5,0,0,6},
                       {0,0,0,4,0,0,7,0,0},
                       {0,1,0,0,0,0,0,0,3},
                       {0,0,0,7,0,0,0,0,0},
                       {4,0,0,0,8,9,6,0,0} };

int Grid3[SIZE*SIZE][SIZE*SIZE] = {
                       {0,1,6,0,8,0,5,3,0},
                       {0,0,4,0,0,0,0,0,0},
                       {0,0,0,9,0,0,0,8,0},
                       {4,0,0,0,1,0,0,0,0},
                       {9,0,0,0,0,0,3,0,0},
                       {0,3,1,7,0,0,0,0,6},
                       {0,0,0,0,0,2,0,0,7},
                       {3,0,0,0,0,0,0,0,0},
                       {0,5,8,0,9,0,6,0,0} };

/*
int Grid4[SIZE*SIZE][SIZE*SIZE] = {
                       {0,0,0,0,0,6,0,0,0,0,16,0,0,0,0,0},
                       {11,7,0,0,15,14,0,10,2,0,5,13,0,0,16,8},
                       {0,0,10,12,0,0,0,0,0,0,0,0,6,5,0,0},
                       {0,15,5,0,3,0,7,11,6,14,0,8,0,1,2,0},
                       {8,4,0,0,0,11,2,14,13,12,3,0,0,0,15,7},
                       {0,0,11,0,0,9,15,7,16,2,8,0,0,10,0,0},
                       {9,12,6,0,0,8,10,16,4,7,14,0,0,11,3,2},
                       {5,0,2,7,0,0,0,1,15,0,0,0,16,14,0,9},
                       {13,0,15,5,0,0,0,9,8,0,0,0,14,2,0,3},
                       {7,3,8,0,0,13,11,12,14,5,6,0,0,15,1,4},
                       {0,0,14,0,0,15,5,3,11,9,1,0,0,13,0,0},
                       {1,6,0,0,0,2,14,8,10,3,13,0,0,0,9,5},
                       {0,8,9,0,11,0,1,4,5,16,0,6,0,12,13,0},
                       {0,0,13,3,0,0,0,0,0,0,0,0,4,9,0,0},
                       {6,5,0,0,9,16,0,15,3,0,11,4,0,0,14,1},
                       {0,0,0,0,0,5,0,0,0,0,15,0,0,0,0,0}};
*/
int Grid5[SIZE * SIZE][SIZE * SIZE] = {
                       {0,3,0,6,0,0,1,9,0},
                       {0,0,2,0,0,0,7,0,0},
                       {0,9,7,0,0,2,0,6,0},
                       {0,0,0,0,0,5,0,0,0},
                       {6,0,0,2,9,0,0,0,0},
                       {0,0,0,0,0,0,4,0,7},
                       {4,0,1,0,0,0,0,0,0},
                       {0,0,0,0,8,9,0,0,3},
                       {0,8,9,5,0,0,0,1,0} };

int Grid6[SIZE * SIZE][SIZE * SIZE] = {
                       {0,0,0,6,0,0,1,0,3},
                       {0,5,7,0,0,8,0,0,0},
                       {0,0,0,2,0,0,0,0,9},
                       {0,7,0,0,8,0,0,0,0},
                       {0,0,4,0,2,0,0,0,0},
                       {0,0,0,0,3,0,0,0,6},
                       {1,0,0,0,4,3,0,5,0},
                       {3,0,0,9,0,0,0,0,0},
                       {0,0,0,0,6,0,0,2,0} };


bool NotOnRow(int value, int row, int column, int grid[SIZE*SIZE][SIZE*SIZE]) { //If the number is on the Row the fucntion return true
    for (int i = 0; i < SIZE*SIZE; i++) {
        if (grid[row][i] == value) {
            return false;
        }
    }
    //cout << value << "\n Not on row \n";
    return true;

}
bool NotOnColumn(int value, int row, int column, int grid[SIZE*SIZE][SIZE*SIZE]) {
    for (int i = 0; i < SIZE*SIZE; i++) {
        if (grid[i][column] == value) {
            return false;
        }
    }
    //cout << value << "\n Not on column \n";
    return true;

}

bool NotOnSquare(int value, int row, int column, int grid[SIZE*SIZE][SIZE*SIZE]) {

    int _i = (row / SIZE) * SIZE; // position (_i,_j) of the first cell of the square's value 
    int _j = (column / SIZE) * SIZE;

    for (int i = _i; i < _i + SIZE; i++) {
        for (int j = _j; j < _j + SIZE; j++) {
            if (grid[i][j] == value) {
                return false;
                
            }
        }
    }
    //cout << value << "\n Not on square \n";
    return true;
}


void PrintGrid(int grid[SIZE*SIZE][SIZE*SIZE]) {

    cout << endl;
    for (int l = 0; l < SIZE*SIZE; l++) {
        if (l % SIZE == 0) {
            cout << "------------------------------------";
        }
        cout << endl;
        for (int c = 0; c < SIZE*SIZE; c++) {
            if (c % SIZE == 0) {
                cout << " | ";
            }
            cout << " " << grid[l][c] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool Solving(int grid[SIZE*SIZE][SIZE*SIZE], int position) {

    if (position > 215) {
        PrintGrid(grid);
    }
    // Ligne 14 Colonne 11

    if (position == SIZE*SIZE*SIZE*SIZE) {
        // If we reach the last box the sudoku is solve
        // cout << "\n Sudoku Solved \n";
        return true;
    }

    // Converting the position in coordinates
    int row = position/(SIZE*SIZE);
    int column = position%(SIZE*SIZE);

    // cout << "\n row : " << row << " column : "<< column << "\n\n";

    if (grid[row][column] != 0) {
        // if there is already a digit in the box we pass to the next one
        // the "return" is used to go back on the track skipping le box with a digit 
        return Solving(grid, position + 1);
    }
    

    for (int digit = 1; digit <= (SIZE*SIZE); digit++) {
   

        if (NotOnColumn(digit, row, column, grid) && NotOnRow(digit, row, column, grid) && NotOnSquare(digit, row, column, grid)) {
            // cout << "\n" << digit << " placed on column : " << column << " and row : " << row << "\n";
            grid[row][column] = digit;


            if(Solving(grid, position + 1)) {
                return true;
            }

            
        }

    }
    grid[row][column] = 0;
    return false;

}

int main()
{
    cout << "\n------------------------------------\n";
    cout << "Solving the Sudoku";
    PrintGrid(Grid5);

    // The Solver begin with the zero index 
    if (Solving(Grid5, 0)) {
        cout << "\n------------------------------------\n";
        cout << "Sudoku solved";
        PrintGrid(Grid5);
    }
    else {
        cout << "\n------------------------------------\n";
        cout << "Sudoku not solvable";
        cout << "\n------------------------------------\n";
    }
}
