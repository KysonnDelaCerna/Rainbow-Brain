#ifndef __GAME_H
#define __GAME_H

#define ROWS 8
#define COLS 8
#define INF 1000000000

int applyMove(int[ROWS][COLS], int, int, int, int, int, int);
int parseAndApplyMove(int[ROWS][COLS], char*, int, int);
int getInput(int[ROWS][COLS], int);
int isGameOver(int[ROWS][COLS]);
int evaluateBoard(int[ROWS][COLS]);
void printBoard(int[ROWS][COLS]);
void newGame(int[ROWS][COLS]);
void waitKey();
#endif