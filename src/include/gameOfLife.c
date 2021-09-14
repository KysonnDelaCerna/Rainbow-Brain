#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "gameOfLife.h"

void initiateRandomBoard(char board[HEIGHT][WIDTH])
{
    int i, j;

    for (i = 0; i < HEIGHT; i++)
    {
        for (j = 0; j < WIDTH; j++)
        {
            switch(rand() % 12)
            {
                case 0:
                {
                    board[i][j] = RED_ALIVE;
                    break;
                }
                case 1:
                {
                    board[i][j] = GREEN_ALIVE;
                    break;
                }
                case 2:
                {
                    board[i][j] = BLUE_ALIVE;
                    break;
                }
                default:
                {
                    board[i][j] = DEAD;
                }
            }
        }
    }
}

void initiateRandomBoardP(char *board)
{
    int i;

    for (i = 0; i < WIDTH * HEIGHT; i++)
    {
        switch(rand() % 12)
        {
            case 0:
            {
                board[i] = RED_ALIVE;
                break;
            }
            case 1:
            {
                board[i] = GREEN_ALIVE;
                break;
            }
            case 2:
            {
                board[i] = BLUE_ALIVE;
                break;
            }
            default:
            {
                board[i] = DEAD;
            }
        }
    }
}

void seedRandom()
{
    srand(time(NULL));
}