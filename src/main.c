#include <stdio.h>
#include "include/game.h"

int main() {
    int board[ROWS][COLS];
    int turn = 1;

    newGame(board);

    while (!isGameOver(board))
    {
        printBoard(board);
        if(getInput(board, turn))
            turn = (turn == 1 ? -1 : 1);
    }

    return 0;
}