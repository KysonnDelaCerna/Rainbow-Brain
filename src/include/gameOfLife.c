#include <time.h>
#include <stdlib.h>
#include "gameOfLife.h"

void initiateBoard(short int board[WIDTH][HEIGHT])
{
    int i, j;

    for (i = 0; i < WIDTH; i++)
    {
        for (j = 0; j < HEIGHT; j++)
        {
            switch(rand() % 6)
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

void seedRandom()
{
    srand(time(NULL));
}