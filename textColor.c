#include "stdio.h"
#include "stdlib.h"
#include "textColor.h"
#define LIGHT_GRAY 7
#define LIGHT_GREEN 10
#define LIGHT_RED 12



enum PlayerColor* colors = 0;

void initColorsList() {
    colors = calloc(5, sizeof(int));
    for (int i = BLUE; i <= YELLOW; i++) {
        if (colors)
            colors[i] = i;
    }
};

void setColor(int ForgC)  //set text color in terminal
{
    switch (ForgC) {
        case BLUE: printf("\x1B[34m"); break;
        case CYAN: printf("\x1B[36m"); break;
        case RED: printf("\x1B[31m"); break;
        case MAGENTA: printf("\x1B[35m"); break;
        case YELLOW: printf("\x1B[33m"); break;
        case LIGHT_GRAY: printf("\x1B[0m"); break;
        case LIGHT_GREEN: printf("\x1B[32;1m"); break;
        case LIGHT_RED: printf("\x1B[31;1m"); break;
    }
}

void printColors() {
    for (int i = BLUE; i < YELLOW; i++);
}

enum PlayerColor getPlayerColor() {
    printColors();
    printf("\nNow, please, choose the color for your penguins: ");

    int color;
    scanf("%d", &color);
    for (int i = 0; i < 5; i++) {
        if (color == colors[i]) {
            colors[i] = NO_COLOR;
            return color;
        }
    }

    return NO_COLOR;
}