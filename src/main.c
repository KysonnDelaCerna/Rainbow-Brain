#include <stdio.h>
#include "include/game.h"

int main() {
    int** board = newGame();
    int turn = 1;

    while (!isGameOver(board))
    {
        printBoard(board);
        if(getInput(board, turn))
            turn = (turn == 1 ? -1 : 1);
    }

    destroyBoard(board);
    return 0;
}