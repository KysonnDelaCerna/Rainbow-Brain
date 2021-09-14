#ifndef __GAME_OF_LIFE_H
#define __GAME_OF_LIFE_H

#define WIDTH 4096
#define HEIGHT 4096

#define N_STATES 7

#define RED_ALIVE 6
#define RED_DYING 5
#define GREEN_ALIVE 4
#define GREEN_DYING 3
#define BLUE_ALIVE 2
#define BLUE_DYING 1
#define DEAD 0

void initiateRandomBoard(char[HEIGHT][WIDTH]);
void initiateRandomBoardP(char *);
void displayBoard(char[HEIGHT][WIDTH]);
void seedRandom();

#endif