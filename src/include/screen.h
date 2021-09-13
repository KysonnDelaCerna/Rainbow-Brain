#ifndef __SCREEN_H
#define __SCREEN_H
#include <windows.h>

#define CELLS_X 16
#define CELLS_Y 16
#define CELL_SIZE 32
#define SCREEN_WIDTH (CELLS_X * CELL_SIZE)
#define SCREEN_HEIGHT (CELLS_Y * CELL_SIZE)

#define RED         RGB(255,0  ,0  )
#define DARK_RED    RGB(128,0  ,0  )
#define GREEN       RGB(0  ,255,0  )
#define DARK_GREEN  RGB(0  ,128,0  )
#define BLUE        RGB(0  ,0  ,255)
#define DARK_BLUE   RGB(0  ,0  ,128)
#define BLACK       RGB(0  ,0  ,0  )

#endif