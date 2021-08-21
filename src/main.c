#include <stdio.h>
#include "include/game.h"

int main () {
    int** board = newGame();

    while (!isGameOver(board))
    {
        printBoard(board);
        getInput(board);
    }

    destroyBoard(board);
    return 0;
}