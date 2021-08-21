#include <stdlib.h>
#include <stdio.h>
#include "game.h"

int verifyMove(int** board, char* move)
{
    return 1;
}

int isGameOver(int** board)
{
    int i, j, whites = 0, blacks = 0;

    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++)
        {
            if (board[i][j] > 0)
                whites++;
            else if (board[i][j] < 0)
                blacks++;
        }
    
    if (whites && blacks)
        return 0;
    return 1;
}

int evaluateBoard(int** board)
{
    int score = 0, i, j;

    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++)
            score += board[i][j];

    return score;
}

int passTurn(int turn)
{
    return !turn;
}

int** newGame()
{
    int** board = (int**) malloc(sizeof(int*) * ROWS);
    int i, j;

    for (i = 0; i < ROWS; i++)
        board[i] = (int*) malloc(sizeof(int) * COLS);

    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++)
        {
            if (i < 3 && (i + j) % 2 == 0)
                board[i][j] = 1;
            else if (i > 4 && (i + j) % 2 == 0)
                board[i][j] = -1;
            else
                board[i][j] = 0;
        }

    return board;
}

void applyMove(int** board, char* move)
{

}

void printBoard(int** board)
{
    char buffer[ROWS * 3 + 1][COLS * 5 + 4] = {
        "      1    2    3    4    5    6    7    8",
        "  ",
        "  ",
        "A ",
        "  ",
        "  ",
        "B ",
        "  ",
        "  ",
        "C ",
        "  ",
        "  ",
        "D ",
        "  ",
        "  ",
        "E ",
        "  ",
        "  ",
        "F ",
        "  ",
        "  ",
        "G ",
        "  ",
        "  ",
        "H ",
    };
    int i, j;

    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++)
        {
            if ((i + j) % 2 == 1)
            {
                sprintf(buffer[i * 3 + 1] + (j * 5 + 2), "     ");
                sprintf(buffer[i * 3 + 2] + (j * 5 + 2), "     ");
                sprintf(buffer[i * 3 + 3] + (j * 5 + 2), "     ");
            }
            else
            {
                if (board[i][j] == 1)
                {
                    sprintf(buffer[i * 3 + 1] + (j * 5 + 2), "#bbb#");
                    sprintf(buffer[i * 3 + 2] + (j * 5 + 2), "bbbbb");
                    sprintf(buffer[i * 3 + 3] + (j * 5 + 2), "#bbb#");
                }
                else if (board[i][j] == 5)
                {
                    sprintf(buffer[i * 3 + 1] + (j * 5 + 2), "#BBB#");
                    sprintf(buffer[i * 3 + 2] + (j * 5 + 2), "BBBBB");
                    sprintf(buffer[i * 3 + 3] + (j * 5 + 2), "#BBB#");
                }
                else if (board[i][j] == -1)
                {
                    sprintf(buffer[i * 3 + 1] + (j * 5 + 2), "#rrr#");
                    sprintf(buffer[i * 3 + 2] + (j * 5 + 2), "rrrrr");
                    sprintf(buffer[i * 3 + 3] + (j * 5 + 2), "#rrr#");
                }
                else if (board[i][j] == -5)
                {
                    sprintf(buffer[i * 3 + 1] + (j * 5 + 2), "#RRR#");
                    sprintf(buffer[i * 3 + 2] + (j * 5 + 2), "RRRRR");
                    sprintf(buffer[i * 3 + 3] + (j * 5 + 2), "#RRR#");
                }
                else
                {
                    sprintf(buffer[i * 3 + 1] + (j * 5 + 2), "#####");
                    sprintf(buffer[i * 3 + 2] + (j * 5 + 2), "#####");
                    sprintf(buffer[i * 3 + 3] + (j * 5 + 2), "#####");
                }
            }
        }
    
    system("cls");
    for (i = 0; i < ROWS * 3 + 1; i++)
        printf("%s\n", buffer[i]);
}

void destroyBoard(int** board)
{
    int i;

    for (i = 0; i < ROWS; i++)
        free(board[i]);
    
    free(board);
}

void getInput(int** board)
{
    char move[52];

    do
        fgets(move, 52, stdin);
    while (!verifyMove(board, move));
    
    applyMove(board, move);
}