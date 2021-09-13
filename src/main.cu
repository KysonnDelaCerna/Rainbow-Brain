#include <iostream>

__device__ int mod(int a, int b)
{
    return (a + b) % b;
}

__device__ char nextState(char slice[9])
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

__global__ void nextGeneration(char oldBoard[HEIGHT][WIDTH], char newBoard[HEIGHT][WIDTH])
{
    int i, j;
    char newBoard[HEIGHT][WIDTH], slice[9];

    for (i = 0; i < HEIGHT; i++)
    {
        for (j = 0; j < WIDTH; j++)
        {
            slice[0] = oldBoard[mod(i - 1, HEIGHT)][mod(j - 1, WIDTH)];
            slice[1] = oldBoard[mod(i - 1, HEIGHT)][j];
            slice[2] = oldBoard[mod(i - 1, HEIGHT)][mod(j + 1, WIDTH)];
            slice[3] = oldBoard[i]                 [mod(j - 1, WIDTH)];
            slice[4] = oldBoard[i]                 [j];
            slice[5] = oldBoard[i]                 [mod(j + 1, WIDTH)];
            slice[6] = oldBoard[mod(i + 1, HEIGHT)][mod(j - 1, WIDTH)];
            slice[7] = oldBoard[mod(i + 1, HEIGHT)][j];
            slice[8] = oldBoard[mod(i + 1, HEIGHT)][mod(j + 1, WIDTH)];

            newBoard[i][j] = nextState(slice);
        }
    }

    memcpy(oldBoard, newBoard, sizeof(char) * WIDTH * HEIGHT);
}

int main (void) {
    cout << "Hello World" << endl;
    return 0;
}