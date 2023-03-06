#include "stdio.h"
#define BLACK 0
#define BLUE  1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHT_GRAY 7
#define DARK_GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define LIGHT_RED 12
#define LIGHT_MAGENTA 13
#define YELLOW 14
#define WHITE 15

void setColor(int ForgC)  //set text color in terminal
{
    switch (ForgC) {
        case BLACK: printf("\x1B[30m"); break;
        case BLUE: printf("\x1B[34m"); break;
        case GREEN: printf("\x1B[32m"); break;
        case CYAN: printf("\x1B[36m"); break;
        case RED: printf("\x1B[31m"); break;
        case MAGENTA: printf("\x1B[35m"); break;
        case BROWN: printf("\x1B[30;1m"); break;
        case LIGHT_GRAY: printf("\x1B[0m"); break;
        case DARK_GRAY: printf("\x1B[0m"); break;
        case LIGHT_BLUE: printf("\x1B[34;1m"); break;
        case LIGHT_GREEN: printf("\x1B[32;1m"); break;
        case LIGHT_CYAN : printf("\x1B[36;1m"); break;
        case LIGHT_RED: printf("\x1B[31;1m"); break;
        case LIGHT_MAGENTA: printf("\x1B[35;1m"); break;
        case YELLOW: printf("\x1B[33m"); break;
        case WHITE: printf("\x1B[37m"); break;
    }
}