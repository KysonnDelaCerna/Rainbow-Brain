#ifndef __GAME_H
#define __GAME_H

#define ROWS 8
#define COLS 8

int applyMove(int[][COLS], char*);
int isGameOver(int**);
int evaluateBoard(int**);
int getInput(int**);
int** newGame();
void printBoard(int**);
void destroyBoard(int**);
void waitKey();
#endif