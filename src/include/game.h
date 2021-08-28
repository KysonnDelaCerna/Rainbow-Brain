#ifndef __GAME_H
#define __GAME_H

#define ROWS 8
#define COLS 8
#define INF 1000000000

int applyMove(int[][COLS], int, int, int, int);
int parseAndApplyMove(int[][COLS], char*);
int isGameOver(int**);
int evaluateBoard(int**);
int getInput(int**);
int** newGame();
void printBoard(int**);
void destroyBoard(int**);
void waitKey();
#endif