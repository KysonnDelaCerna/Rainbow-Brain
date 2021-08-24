#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "game.h"

int applyMove(int board[][COLS], char* move)
{
    if (move[0] < 'A' || move[0] > 'H' || move[1] < '1' || move[1] > '8' ||
        move[2] < 'A' || move[2] > 'H' || move[3] < '1' || move[3] > '8')
        return -1;

    int srcX, srcY, dstX, dstY, moveX, moveY;
    srcX = move[1] - '1';
    srcY = move[0] - 'A';
    dstX = move[3] - '1';
    dstY = move[2] - 'A';
    moveX = srcX - dstX;
    moveY = srcY - dstY;

    if (board[srcY][srcX] == 1)
    {
        /* moving */
        if (moveY == 1 && abs(moveX) == 1)
        {
            if (board[dstY][dstX] == 0)
            {
                if (dstY == ROWS - 1)
                    board[dstY][dstX] = 5;
                else
                    board[dstY][dstX] = 1;
                board[srcY][srcX] = 0;
            }
            else
                return -3;
        }
        /* eating */
        else if (moveY == 2 && abs(moveX) == 2)
        {
            if (board[dstY][dstX] == 0 &&
                board[(srcY + dstY) / 2][(srcX + dstX) / 2] < 0)
            {
                if (dstY == ROWS - 1)
                    board[dstY][dstX] = 5;
                else
                    board[dstY][dstX] = 1;
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
    else if (board[srcY][srcX] == 5)
    {
        if (abs(moveX) == abs(moveY) && moveX != 0)
        {
            int i;
            for (i = 1; i < abs(moveX) - 1; i++)
                if (board[srcY + (moveY < 0 ? -i : i)][srcX + (moveX < 0 ? -i : i)] != 0)
                    return -3;
            
            /* moving */
            board[srcY][srcX] = 0;
            board[dstY][dstX] = 5;

            /* eating */
            if (board[srcY + (moveY < 0 ? moveY + 1 : moveY - 1)][srcX + (moveX < 0 ? moveX + 1 : moveX - 1)] < 0)
            {
                board[srcY + (moveY < 0 ? moveY + 1 : moveY - 1)][srcX + (moveX < 0 ? moveX + 1 : moveX - 1)] = 0;
                return 1;
            }
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

int getInput(int** board)
{
    int pointer = 0, i, j, turnEnded = 0;
    int tempBoard[ROWS][COLS];
    char move[55], tempMove[6];

    fgets(move, 52, stdin);

    if (strlen(move) < 4)
    {
        printf("Input too short\n");
        waitKey();
        return 0;
    }

    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++)
            tempBoard[i][j] = board[i][j];

    while (strlen(move + pointer) >= 4 && !turnEnded)
    {
        strncpy(tempMove, move + pointer, 4);
        switch (applyMove(tempBoard, tempMove))
        {
            case 0:
            {
                turnEnded = 1;
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

    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++)
            board[i][j] = tempBoard[i][j];
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
                board[i][j] = 5;
            else
                board[i][j] = 0;
        }

    return board;
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