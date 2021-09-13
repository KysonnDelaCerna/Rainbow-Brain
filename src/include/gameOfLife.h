#ifndef __GAME_OF_LIFE_H
#define __GAME_OF_LIFE_H

#define WIDTH 10
#define HEIGHT 10

#define RED_ALIVE 6
#define RED_DYING 5
#define GREEN_ALIVE 4
#define GREEN_DYING 3
#define BLUE_ALIVE 2
#define BLUE_DYING 1
#define DEAD 0

int mod(int, int);
char nextState(char[9]);
void initiateBoard(char[HEIGHT][WIDTH]);
void displayBoard(char[HEIGHT][WIDTH]);
void seedRandom();

#endif