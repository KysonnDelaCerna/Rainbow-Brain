#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "game.h"

int applyMove(int board[][COLS], int srcX, int srcY, int dstX, int dstY, int hasEaten)
{
    if (srcX < 0 || srcX > COLS - 1 || srcY < 0 || srcY > ROWS - 1 ||
        dstX < 0 || dstX > COLS - 1 || dstY < 0 || dstY > ROWS - 1)
        return -1;

    int moveX, moveY;
    moveX = srcX - dstX;
    moveY = srcY - dstY;

    /* normal piece */
    if (abs(board[srcY][srcX]) == 1)
    {
        /* moving */
        if (moveY == board[srcY][srcX] && abs(moveX) == 1 && !hasEaten)
        {
            if (board[dstY][dstX] == 0)
            {
                if (dstY == ROWS - 1 || dstY == 0)
                    board[dstY][dstX] = 5 * board[srcY][srcX];
                else
                    board[dstY][dstX] = board[srcY][srcX];
                board[srcY][srcX] = 0;
            }
            else
                return -3;
        }
        /* eating */
        else if (moveY == 2 * board[srcY][srcX] && abs(moveX) == 2)
        {
            if (board[dstY][dstX] == 0 &&
                (board[(srcY + dstY) / 2][(srcX + dstX) / 2] < 0) != (board[srcY][srcX] < 0))
            {
                if (dstY == ROWS - 1 || dstY == 0)
                    board[dstY][dstX] = 5 * board[srcY][srcX];
                else
                    board[dstY][dstX] = board[srcY][srcX];
                board[(srcY + dstY) / 2][(srcX + dstX) / 2] = 0;
                board[srcY][srcX] = 0;
                return 1;
            }
            else
                return -3;
        }
        else
            return -3;
    }
    /* king piece */
    else if (abs(board[srcY][srcX]) == 5)
    {
        if (abs(moveX) == abs(moveY) && moveX != 0)
        {
            int i;
            for (i = 1; i < abs(moveX) - 1; i++)
                if (board[srcY + (moveY < 0 ? -i : i)][srcX + (moveX < 0 ? -i : i)] != 0)
                    return -3;
            
            /* moving */
            board[srcY][srcX] = 0;
            board[dstY][dstX] = board[srcY][srcX];

            /* eating */
            if ((board[srcY + (moveY < 0 ? moveY + 1 : moveY - 1)][srcX + (moveX < 0 ? moveX + 1 : moveX - 1)]) < 0 != (board[srcY][srcX] < 0))
            {
                board[srcY + (moveY < 0 ? moveY + 1 : moveY - 1)][srcX + (moveX < 0 ? moveX + 1 : moveX - 1)] = 0;
                return 1;
            }
            else if (hasEaten)
                return -3;
            else
                return 0;
        }
        else
            return -3;
    }
    else
        return -2;

    return 0;
}

int parseAndApplyMove(int board[][COLS], char* move, int hasEaten)
{
    int srcX, srcY, dstX, dstY;
    srcX = move[1] - '1';
    srcY = move[0] - 'A';
    dstX = move[3] - '1';
    dstY = move[2] - 'A';

    return applyMove(board, srcX, srcY, dstX, dstY, hasEaten);
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
    else if (whites)
        return 1;
    else if (blacks)
        return 2;
    
    return 0;
}

int evaluateBoard(int** board)
{
    int positiveScore = 0, negativeScore = 0, i, j;

    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++)
        {
            if (board[i][j] > 0)
                positiveScore += board[i][j];
            else if (board[i][j] < 0)
                negativeScore += board[i][j];
        }

    if (positiveScore == 0)
        return -INF;
    else if (negativeScore == 0)
        return INF;
    return positiveScore + negativeScore;
}

int getInput(int** board)
{
    int pointer = 0, i, j, turnEnded = 0, hasEaten = 0;
    int tempBoard[ROWS][COLS];
    char move[55], tempMove[6];

    fgets(move, 52, stdin);

    if (strlen(move) < 4)
    {
        printf("Input too short\n");
        waitKey();
        return 0;
    }

    deepCopy(board, tempBoard);

    while (strlen(move + pointer) >= 4 && !turnEnded)
    {
        strncpy(tempMove, move + pointer, 4);
        switch (parseAndApplyMove(tempBoard, tempMove, hasEaten))
        {
            case 0:
            {
                turnEnded = 1;
                break;
            }
            case 1:
            {
                hasEaten = 1;
                break;
            }
            case -1:
            {
                printf("Invalid character\n");
                waitKey();
                return 0;
            }
            case -2:
            {
                printf("Invalid piece\n");
                waitKey();
                return 0;
            }
            case -3:
            {
                printf("Invalid move\n");
                waitKey();
                return 0;
            }
        }

        pointer += 2;
    }

    deepCopy(tempBoard, board);
    return 1;
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
                board[i][j] = -1;
            else if (i > 4 && (i + j) % 2 == 0)
                board[i][j] = 1;
            else
                board[i][j] = 0;
        }

    return board;
}

void deepCopy(int** src, int dst[][COLS])
{
    int i, j;

    for (i = 0; i < ROWS; i++)
        for(j = 0; j < COLS; j++)
            dst[i][j] = src[i][j];
}

void deepCopy(int src[][COLS], int** dst)
{
    int i, j;

    for (i = 0; i < ROWS; i++)
        for(j = 0; j < COLS; j++)
            dst[i][j] = src[i][j];
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

void waitKey()
{
    printf("Press any key to continue...\n");
    getchar();
}
