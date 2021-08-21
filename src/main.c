#include <stdio.h>
#include "include/game.h"

int main () {
    int** board = newGame();
    printBoard(board);
    destroyBoard(board);
    return 0;
}