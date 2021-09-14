#ifndef UNICODE
#define UNICODE
#endif 

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <windowsx.h>
#include "include/gameOfLife.h"
#include "include/screen.h"

char oldBoard[HEIGHT][WIDTH], newBoard[HEIGHT][WIDTH];
int x = 0, y = 0;

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

void nextGeneration(char oldBoard[HEIGHT][WIDTH], char newBoard[HEIGHT][WIDTH])
{
    int i, j;
    char slice[9];

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
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            int i, j;
            RECT rc;
            HBRUSH RED_BRUSH, DARK_RED_BRUSH, GREEN_BRUSH, DARK_GREEN_BRUSH, BLUE_BRUSH, DARK_BLUE_BRUSH, DEAD_BRUSH;
            RED_BRUSH           = CreateSolidBrush(RED);
            DARK_RED_BRUSH      = CreateSolidBrush(DARK_RED);
            GREEN_BRUSH         = CreateSolidBrush(GREEN);
            DARK_GREEN_BRUSH    = CreateSolidBrush(DARK_GREEN);
            BLUE_BRUSH          = CreateSolidBrush(BLUE);
            DARK_BLUE_BRUSH     = CreateSolidBrush(DARK_BLUE);
            DEAD_BRUSH          = CreateSolidBrush(BLACK);

            for (i = 0; i < CELLS_Y; i++)
            {
                for (j = 0; j < CELLS_X; j++)
                {
                    rc.left   = j       * CELL_SIZE;
                    rc.right  = (j + 1) * CELL_SIZE;
                    rc.top    = i       * CELL_SIZE;
                    rc.bottom = (i + 1) * CELL_SIZE;

                    switch(oldBoard[mod(y + i, HEIGHT)][mod(x + j, WIDTH)])
                    {
                        case RED_ALIVE:     FillRect(hdc, &rc, RED_BRUSH); break;
                        case RED_DYING:     FillRect(hdc, &rc, DARK_RED_BRUSH); break;
                        case GREEN_ALIVE:   FillRect(hdc, &rc, GREEN_BRUSH); break;
                        case GREEN_DYING:   FillRect(hdc, &rc, DARK_GREEN_BRUSH); break;
                        case BLUE_ALIVE:    FillRect(hdc, &rc, BLUE_BRUSH); break;
                        case BLUE_DYING:    FillRect(hdc, &rc, DARK_BLUE_BRUSH); break;
                        case DEAD:          FillRect(hdc, &rc, DEAD_BRUSH); break;
                    }

                    rc.left   = j       * CELL_SIZE + CELL_SIZE / 4;
                    rc.right  = rc.left + CELL_SIZE / 2;
                    rc.top    = i       * CELL_SIZE + CELL_SIZE / 4;
                    rc.bottom = rc.top  + CELL_SIZE / 2;

                    switch(newBoard[mod(y + i, HEIGHT)][mod(x + j, WIDTH)])
                    {
                        case RED_ALIVE:     FillRect(hdc, &rc, RED_BRUSH); break;
                        case RED_DYING:     FillRect(hdc, &rc, DARK_RED_BRUSH); break;
                        case GREEN_ALIVE:   FillRect(hdc, &rc, GREEN_BRUSH); break;
                        case GREEN_DYING:   FillRect(hdc, &rc, DARK_GREEN_BRUSH); break;
                        case BLUE_ALIVE:    FillRect(hdc, &rc, BLUE_BRUSH); break;
                        case BLUE_DYING:    FillRect(hdc, &rc, DARK_BLUE_BRUSH); break;
                        case DEAD:          FillRect(hdc, &rc, DEAD_BRUSH); break;
                    }
                }
            }

            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_CHAR:
        {
            switch(wParam)
            {
                case 'n':
                {
                    memcpy(oldBoard, newBoard, sizeof(char) * WIDTH * HEIGHT);
                    nextGeneration(oldBoard, newBoard);
                    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
                    break;
                }
                case 'r':
                {
                    initiateRandomBoard(oldBoard);
                    nextGeneration(oldBoard, newBoard);
                    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
                    break;
                }
                case 'w':
                {
                    y = mod(y - 1, HEIGHT);
                    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
                    break;
                }
                case 's':
                {
                    y = mod(y + 1, HEIGHT);
                    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
                    break;
                }
                case 'a':
                {
                    x = mod(x - 1, HEIGHT);
                    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
                    break;
                }
                case 'd':
                {
                    x = mod(x + 1, HEIGHT);
                    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
                    break;
                }
            }
            return 0;
        }
        case WM_LBUTTONDOWN:
        {
            int xClick = GET_X_LPARAM(lParam) / CELL_SIZE;
            int yClick = GET_Y_LPARAM(lParam) / CELL_SIZE;

            oldBoard[mod(y + yClick, HEIGHT)][mod(x + xClick, WIDTH)] = (oldBoard[mod(y + yClick, HEIGHT)][mod(x + xClick, WIDTH)] + 1) % N_STATES;
            nextGeneration(oldBoard, newBoard);
            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    seedRandom();
    initiateRandomBoard(oldBoard);
    nextGeneration(oldBoard, newBoard);
    
    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"CEPARCO CUDA Project";

    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                                                          // Optional window styles.
        CLASS_NAME,                                                 // Window class
        L"Rainbow Brain",                                           // Window text
        (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX), // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, SCREEN_WIDTH + GetSystemMetrics(5) * 4, SCREEN_HEIGHT + GetSystemMetrics(6) * 4 + GetSystemMetrics(4),

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}