#include <stdio.h>
#include <string.h>
#include "include/gameOfLife.h"

void nextGeneration(char oldBoard[HEIGHT][WIDTH])
{
    int i, j;
    char newBoard[HEIGHT][WIDTH], slice[9];

    for (i = 0; i < HEIGHT; i++)
    {
        for (j = 0; j < WIDTH; j++)
        {
            slice[0] = oldBoard[mod(i - 1, HEIGHT)][mod(j - 1, WIDTH)];
            slice[1] = oldBoard[mod(i - 1, HEIGHT)][j];
            slice[2] = oldBoard[mod(i - 1, HEIGHT)][mod(j + 1, WIDTH)];
            slice[3] = oldBoard[i]                 [mod(j - 1, WIDTH)];
            slice[4] = oldBoard[i]                 [j];
            slice[5] = oldBoard[i]                 [mod(j + 1, WIDTH)];
            slice[6] = oldBoard[mod(i + 1, HEIGHT)][mod(j - 1, WIDTH)];
            slice[7] = oldBoard[mod(i + 1, HEIGHT)][j];
            slice[8] = oldBoard[mod(i + 1, HEIGHT)][mod(j + 1, WIDTH)];

            newBoard[i][j] = nextState(slice);
        }
    }

    memcpy(oldBoard, newBoard, sizeof(char) * WIDTH * HEIGHT);
}

int main() 
{
    char board[HEIGHT][WIDTH];
    
    seedRandom();
    initiateBoard(board);

    return 0;
}