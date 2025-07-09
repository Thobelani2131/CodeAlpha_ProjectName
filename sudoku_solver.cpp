#include <iostream>

const int GRID_SIZE = 9;

// ✅ Function to check if placing 'num' in grid[row][col] is valid
bool isValid(int grid[GRID_SIZE][GRID_SIZE], int row, int col, int num) {
    // Check row and column for duplicates
    for (int i = 0; i < GRID_SIZE; i++) {
        if (grid[row][i] == num || grid[i][col] == num)
            return false;
    }

    // ✅ Check 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[startRow + i][startCol + j] == num)
                return false;
        }
    }

    return true;
}

// ✅ Recursive backtracking function to solve the Sudoku puzzle
bool solveSudoku(int grid[GRID_SIZE][GRID_SIZE]) {
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            // Find an empty cell
            if (grid[row][col] == 0) {
                // Try numbers 1 to 9
                for (int num = 1; num <= 9; num++) {
                    if (isValid(grid, row, col, num)) {
                        grid[row][col] = num; // Tentatively place number

                        // Recurse to next cell
                        if (solveSudoku(grid))
                            return true;

                        grid[row][col] = 0; // Backtrack
                    }
                }
                return false; // No valid number found, need to backtrack
            }
        }
    }
    return true; // Solved
}

// ✅ Function to print the Sudoku grid
void printSudoku(int grid[GRID_SIZE][GRID_SIZE]) {
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            std::cout << grid[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

// ✅ Main Function
int main() {
    // Representing Sudoku grid as 2D array (0 = empty cells)
    int sudokuGrid[GRID_SIZE][GRID_SIZE] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    std::cout << "Initial Sudoku Grid:\n";
    printSudoku(sudokuGrid);

    if (solveSudoku(sudokuGrid)) {
        std::cout << "\nSolved Sudoku Grid:\n";
        printSudoku(sudokuGrid);
    } else {
        std::cout << "\nNo solution exists.\n";
    }

    return 0;
}
