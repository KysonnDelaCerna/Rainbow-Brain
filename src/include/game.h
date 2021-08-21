#ifndef __GAME_H
#define __GAME_H

#define ROWS 8
#define COLS 8

int isGameOver(int**);
int** newGame();
void printBoard(int**);
void passTurn();
void getInput();
void destroyBoard(int**);
#endif