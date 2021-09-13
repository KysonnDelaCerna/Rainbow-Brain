#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "gameOfLife.h"

int mod(int a, int b)
{
    return (a + b) % b;
}

char nextState(char slice[9])
{
    if (slice[4] == RED_DYING || slice[4] == GREEN_DYING || slice[4] == BLUE_DYING)
        return DEAD;
    if (slice[4] == RED_ALIVE)
        return RED_DYING;
    if (slice[4] == GREEN_ALIVE)
        return GREEN_DYING;
    if (slice[4] == BLUE_ALIVE)
        return BLUE_DYING;
    
    int i, red, green, blue;
    red = green = blue = 0;

    for (i = 0; i < 9; i++)
    {
        if (i == 4)
            continue;
        else if (slice[i] == RED_ALIVE)
            red++;
        else if (slice[i] == GREEN_ALIVE)
            green++;
        else if (slice[i] == BLUE_ALIVE)
            blue++;
    }

    if (red + green + blue == 4)
    {
        if (red >= 2)
            return RED_ALIVE;
        if (green >= 2)
            return GREEN_ALIVE;
        if (blue >= 2)
            return BLUE_ALIVE;
    }

    return DEAD;
}

void initiateBoard(char board[HEIGHT][WIDTH])
{
    int i, j;

    for (i = 0; i < HEIGHT; i++)
    {
        for (j = 0; j < WIDTH; j++)
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

void displayBoard(char board[HEIGHT][WIDTH])
{
    int i, j;

    for (i = 0; i < HEIGHT; i++)
    {
        for (j = 0; j < WIDTH; j++)
        {
            switch(board[i][j])
            {
                case RED_ALIVE: printf("R"); break;
                case GREEN_ALIVE: printf("G"); break;
                case BLUE_ALIVE: printf("B"); break;
                case RED_DYING: printf("r"); break;
                case GREEN_DYING: printf("g"); break;
                case BLUE_DYING: printf("b"); break;
                case DEAD: printf(" "); break;
            }
        }
        printf("\n");
    }
}

void seedRandom()
{
    srand(time(NULL));
}