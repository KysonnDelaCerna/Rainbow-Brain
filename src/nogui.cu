#include <iostream>
#include <curand.h>
#include <curand_kernel.h>
extern "C" {
#include "include/gameOfLife.h"
}

using namespace std;

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
    
    int red, green, blue;
    red = green = blue = 0;

    for (int i = 0; i < 9; i++)
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

__global__ void nextGeneration(char *oldBoard, char *newBoard)
{
    int x, y, left, right, up, down, stride = blockDim.x * gridDim.x;
    char slice[9];

    for (int i = blockIdx.x * blockDim.x + threadIdx.x; i < WIDTH * HEIGHT; i += stride)
    {
        x = i % WIDTH;
        y = i - x;
        left = mod(x - 1, WIDTH);
        right = mod(x + 1, WIDTH);
        up = mod(y - WIDTH, WIDTH * HEIGHT);
        down = mod(y + WIDTH, WIDTH * HEIGHT);

        slice[0] = oldBoard[left + up];
        slice[1] = oldBoard[x + up];
        slice[2] = oldBoard[right + up];
        slice[3] = oldBoard[left + y];
        slice[4] = oldBoard[i];
        slice[5] = oldBoard[right + y];
        slice[6] = oldBoard[left + down];
        slice[7] = oldBoard[x + down];
        slice[8] = oldBoard[right + down];

        newBoard[i] = nextState(slice);
    }
}

void printBoard(char *board) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            switch(board[i * WIDTH + j])
            {
                case RED_ALIVE: cout << "R"; break;
                case RED_DYING: cout << "r"; break;
                case GREEN_ALIVE: cout << "G"; break;
                case GREEN_DYING: cout << "g"; break;
                case BLUE_ALIVE: cout << "B"; break;
                case BLUE_DYING: cout << "b"; break;
                case DEAD: cout << " "; break;
                default: cout << "X"; break;
            }
        }
        cout << endl;
    }
    cout << endl;
}

__global__ void initRand(curandState *state, unsigned long seed) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    curand_init(seed, idx, 0, &state[idx]);
}

__global__ void cudaInitiateRandomBoard(curandState *globalState, char *board) {
    int stride = blockDim.x * gridDim.x, idx = blockIdx.x * blockDim.x + threadIdx.x;
    float random;
    curandState localState;

    for (int i = idx; i < WIDTH * HEIGHT; i += stride)
    {
        localState = globalState[idx % (blockDim.x * blockDim.x)];
        random = curand_uniform(&(localState));
        if (random <= 0.0833)
            board[i] = RED_ALIVE;
        else if (random <= 0.1666)
            board[i] = GREEN_ALIVE;
        else if (random <= 0.2500)
            board[i] = BLUE_ALIVE;
        else
            board[i] = DEAD;
        globalState[idx % (blockDim.x * blockDim.x)] = localState;
    }
}

int main (void) {
    char *oldBoard, *newBoard;
    curandState *devStates;
    int blockSize = 256;
    int numBlocks = (WIDTH * HEIGHT + blockSize - 1) / blockSize;

    cudaMalloc(&devStates, blockSize * blockSize * sizeof(curandState));
    cudaMallocManaged(&oldBoard, WIDTH * HEIGHT * sizeof(char));
    cudaMallocManaged(&newBoard, WIDTH * HEIGHT * sizeof(char));
    cudaDeviceSynchronize();

    initRand<<<blockSize, blockSize>>>(devStates, time(NULL));
    cudaInitiateRandomBoard<<<numBlocks, blockSize>>>(devStates, oldBoard);
    cudaDeviceSynchronize();

    printBoard(oldBoard);

    nextGeneration<<<numBlocks, blockSize>>>(oldBoard, newBoard);
    cudaDeviceSynchronize();

    printBoard(newBoard);

    cudaFree(oldBoard);
    cudaFree(newBoard);

    return 0;
}