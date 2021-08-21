#ifndef __GAME_H
#define __GAME_H

#define ROWS 8
#define COLS 8

int verifyMove(int**, char*);
int isGameOver(int**);
int evaluateBoard(int**);
int passTurn(int);
int** newGame();
void applyMove(int**, char*);
void printBoard(int**);
void destroyBoard(int**);
void getInput(int**);
#endif