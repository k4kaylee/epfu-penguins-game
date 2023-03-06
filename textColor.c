#include <windows.h>
#include <dos.h>


void setColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    //We use csbi for the wAttributes word.
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        //Mask out all but the background attribute, and add in the forgournd color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
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