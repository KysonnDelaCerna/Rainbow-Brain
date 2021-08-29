#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/game.h"

#define DEPTH 15

int minimax(int[ROWS][COLS], int, int);
int minimaxHelper(int[ROWS][COLS], int, int, int, int, int, int);

int minimax(int board[ROWS][COLS], int depth, int max)
{
    if (depth <= 0)
        return evaluateBoard(board);
    
    int tempScore, bestScore, i, j;
    int tempBoard[ROWS][COLS], bestBoard[ROWS][COLS];

    if (max)
    {
        bestScore = -INF;
        for (i = 0; i < ROWS; i++)
        {
            for (j = 0; j < COLS; j++)
            {
                if (board[i][j] > 0)
                {
                    memcpy(tempBoard, board, sizeof(int) * ROWS * COLS);
                    tempScore = minimaxHelper(tempBoard, bestScore, j, i, 0, max, depth - 1);
                    if (tempScore > bestScore)
                    {
                        bestScore = tempScore;
                        memcpy(bestBoard, tempBoard, sizeof(int) * ROWS * COLS);
                    }
                }
            }
        }
    }
    else
    {
        bestScore = INF;
        for (i = 0; i < ROWS; i++)
        {
            for (j = 0; j < COLS; j++)
            {
                if (board[i][j] < 0)
                {
                    memcpy(tempBoard, board, sizeof(int) * ROWS * COLS);
                    tempScore = minimaxHelper(tempBoard, bestScore, j, i, 0, max, depth - 1);
                    if (tempScore < bestScore)
                    {
                        bestScore = tempScore;
                        memcpy(bestBoard, tempBoard, sizeof(int) * ROWS * COLS);
                    }
                }
            }
        }
    }
    
    if (depth == DEPTH)
        memcpy(board, bestBoard, sizeof(int) * ROWS * COLS);
    return bestScore;
}

int minimaxHelper(int board[ROWS][COLS], int bestScore, int srcX, int srcY, int hasEaten, int max, int depth)
{
    int i, tempScore, turn = (max == 1 ? 1 : -1);
    int tempBoard[ROWS][COLS], bestBoard[ROWS][COLS];

    if (abs(board[srcY][srcX]) == 1)
    {
        for (i = 1; i < 3; i++)
        {
            /* copy to temp */
            memcpy(tempBoard, board, sizeof(int) * ROWS * COLS);
            /* check if move works */
            switch(applyMove(tempBoard, srcX, srcY, srcX + i, srcY - i * turn, hasEaten, turn))
            {
                /* got to eat */
                case 1:
                {
                    /* check to see if can eat again */
                    minimaxHelper(tempBoard, bestScore, srcX + i, srcY - i * turn, 1, max, depth);
                }
                case 0:
                {
                    /* pass turn */
                    minimax(tempBoard, depth - 1, !max);
                    /* check evaluation, if it's better save this state */
                    tempScore = evaluateBoard(tempBoard);
                    if ((max && tempScore > bestScore) || (!max && tempScore < bestScore))
                    {
                        bestScore = tempScore;
                        memcpy(bestBoard, tempBoard, sizeof(int) * ROWS * COLS);
                    }
                    break;
                }
            }

            /* copy to temp */
            memcpy(tempBoard, board, sizeof(int) * ROWS * COLS);
            /* check if move works */
            switch(applyMove(tempBoard, srcX, srcY, srcX - i, srcY - i * turn, hasEaten, turn))
            {
                /* got to eat */
                case 1:
                {
                    /* check to see if can eat again */
                    minimaxHelper(tempBoard, bestScore, srcX - i, srcY - i * turn, 1, max, depth);
                }
                case 0:
                {
                    /* pass turn */
                    minimax(tempBoard, depth - 1, !max);
                    /* check evaluation, if it's better save this state */
                    tempScore = evaluateBoard(tempBoard);
                    if ((max && tempScore > bestScore) || (!max && tempScore < bestScore))
                    {
                        bestScore = tempScore;
                        memcpy(bestBoard, tempBoard, sizeof(int) * ROWS * COLS);
                    }
                    break;
                }
            }
        }
    }
    else if (abs(board[srcY][srcX]) == 5)
    {
        for (i = -7; i < 8; i++)
        {
            if (i == 0)
                continue;
            
            /* copy to temp */
            memcpy(tempBoard, board, sizeof(int) * ROWS * COLS);
            /* check if move works */
            switch(applyMove(tempBoard, srcX, srcY, srcX + i, srcY - i * turn, hasEaten, turn))
            {
                /* got to eat */
                case 1:
                {
                    /* check to see if can eat again */
                    minimaxHelper(tempBoard, bestScore, srcX + i, srcY - i * turn, 1, max, depth);
                }
                case 0:
                {
                    /* pass turn */
                    minimax(tempBoard, depth - 1, !max);
                    /* check evaluation, if it's better save this state */
                    tempScore = evaluateBoard(tempBoard);
                    if ((max && tempScore > bestScore) || (!max && tempScore < bestScore))
                    {
                        bestScore = tempScore;
                        memcpy(bestBoard, tempBoard, sizeof(int) * ROWS * COLS);
                    }
                    break;
                }
            }

            /* copy to temp */
            memcpy(tempBoard, board, sizeof(int) * ROWS * COLS);
            /* check if move works */
            switch(applyMove(tempBoard, srcX, srcY, srcX - i, srcY - i * turn, hasEaten, turn))
            {
                /* got to eat */
                case 1:
                {
                    /* check to see if can eat again */
                    minimaxHelper(tempBoard, bestScore, srcX - i, srcY - i * turn, 1, max, depth);
                }
                case 0:
                {
                    /* pass turn */
                    minimax(tempBoard, depth - 1, !max);
                    /* check evaluation, if it's better save this state */
                    tempScore = evaluateBoard(tempBoard);
                    if ((max && tempScore > bestScore) || (!max && tempScore < bestScore))
                    {
                        bestScore = tempScore;
                        memcpy(bestBoard, tempBoard, sizeof(int) * ROWS * COLS);
                    }
                    break;
                }
            }
        }
    }
    
    /* return only the best outcome */
    memcpy(board, bestBoard, sizeof(int) * ROWS * COLS);
    return bestScore;
}

int main() {
    int board[ROWS][COLS];
    int turn = 1;

    newGame(board);

    while (!isGameOver(board))
    {
        printBoard(board);
        if (turn == 1)
        {
            if(getInput(board, turn))
                turn = -1;
        }
        else
        {
            printf("Please wait while AI decides...\n");
            minimax(board, DEPTH, 0);
            turn = 1;
        }
    }
    
    return 0;
}