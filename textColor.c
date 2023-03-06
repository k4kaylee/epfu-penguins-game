#include "stdio.h"


void setColor(int ForgC)
{
    switch (ForgC) {
        case 0: printf("\x1B[30m"); break;
        case 1: printf("\x1B[34m"); break;
        case 2: printf("\x1B[32m"); break;
        case 3: printf("\x1B[36m"); break;
        case 4: printf("\x1B[31m"); break;
        case 5: printf("\x1B[35m"); break;
        case 6: printf("\x1B[30;1m"); break;
        case 7: printf("\x1B[0m"); break;
        case 8: printf("\x1B[0m"); break;
        case 9: printf("\x1B[34;1m"); break;
        case 10: printf("\x1B[32;1m"); break;
        case 11: printf("\x1B[36;1m"); break;
        case 12: printf("\x1B[31;1m"); break;
        case 13: printf("\x1B[35;1m"); break;
        case 14: printf("\x1B[33m"); break;
        case 15: printf("\x1B[37m"); break;
    }
}



/*
 Name          | Value
               |
 Black         | 0
 Blue          | 1
 Green         | 2
 Cyan          | 3
 Red           | 4
 Magenta       | 5
 Brown         | 6
 Light Gray    | 7
 Dark Gray     | 8
 Light Blue    | 9
 Light Green   | 10
 Light Cyan    | 11
 Light Red     | 12
 Light Magenta | 13
 Yellow        | 14
 White         | 15
*/