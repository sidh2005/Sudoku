#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 25  

void printBoard(int **board, int size, int boxSize) {
    printf("\n");
    for (int i = 0; i < size; i++) {
        if (i % boxSize == 0 && i != 0) {
            for (int k = 0; k < size * 3 + boxSize - 1; k++) printf("-");
            printf("\n");
        }
        for (int j = 0; j < size; j++) {
            if (j % boxSize == 0 && j != 0) printf("| ");
            if (board[i][j] == 0)
                printf("-  "); 
            else
                printf("%d  ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void getUserInput(int **board, int size, int boxSize) {
    printf("\nEnter your Sudoku and use 0 for empty spaces:\n");
    printBoard(board, size, boxSize);  

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("Enter value for row %d, col %d: ", i + 1, j + 1);
            scanf("%d", &board[i][j]);
            if (board[i][j] < 0 || board[i][j] > size) {
                printf("Please enter numbers between 0 and %d.\n", size);
                j--; 
            } else {
                printBoard(board, size, boxSize);  
            }
        }
    }
}


int isValid(int **board, int size, int boxSize, int row, int col, int num) {
    for (int i = 0; i < size; i++) {
        if (board[row][i] == num || board[i][col] == num)
            return 0;
    }

    int boxRow = row - row % boxSize;
    int boxCol = col - col % boxSize;
    for (int i = 0; i < boxSize; i++) {
        for (int j = 0; j < boxSize; j++) {
            if (board[boxRow + i][boxCol + j] == num)
                return 0;
        }
    }
    return 1;
}

int solveSudoku(int **board, int size, int boxSize) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= size; num++) {
                    if (isValid(board, size, boxSize, row, col, num)) {
                        board[row][col] = num;
                        if (solveSudoku(board, size, boxSize)) return 1;
                        board[row][col] = 0;
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    int size, boxSize;
    printf("Enter Sudoku size: ");
    scanf("%d", &size);

    boxSize = sqrt(size);
    if (boxSize * boxSize != size || size > MAX_SIZE) {
        printf("The sizse must be a perfect square and ≤ %d×%d.\n", MAX_SIZE, MAX_SIZE);
        return 1;
    }

    int **board = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
        board[i] = (int *)malloc(size * sizeof(int));

    getUserInput(board, size, boxSize);  

    printf("\nUnsolved Sudoku:\n");
    printBoard(board, size, boxSize);

    if (solveSudoku(board, size, boxSize)) {
        printf("\nSolved Sudoku:\n");
        printBoard(board, size, boxSize);
    } else {
        printf("\nNo solution exists :(\n");
    }

    for (int i = 0; i < size; i++)
    free(board[i]);
    free(board);

    return 0;
}
