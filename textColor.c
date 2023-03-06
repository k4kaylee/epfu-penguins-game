#include <windows.h>
#include <dos.h>
#include "player.h"
#include "board.h"
#include "gamePhase.h"


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



char** getPossibleMoves(char** board, int size) {
    struct Player* current = getCurrentPlayer();

    char** possibleMoves = 0;
    possibleMoves = malloc(sizeof(*board) * size);
    for (int i = 0; i < size; i++)
        possibleMoves[i] = malloc(sizeof(**board) * size);

    for (int i = 0; i < size; i++) {

        for (int j = 0; j < size; j++)
            possibleMoves[i][j] = '0';
    }



    //How can i get information from structure in another function?
    int x = current->penguinX - 1;
    int y = letterToInt(current->penguinY) - 1;

    for (int i = x + 1; i < size; i++) {
        if (board[i][y] == 'X' || board[i][y] == 'P')
            break;
        possibleMoves[i][y] = board[i][y];
    }

    for (int i = x - 1; i >= 0; i--) {
        if (board[i][y] == 'X' || board[i][y] == 'P')
            break;
        possibleMoves[i][y] = board[i][y];
    }

    for (int j = y + 1; j < size; j++) {
        if (board[x][j] == 'X' || board[x][j] == 'P')
            break;
        possibleMoves[x][j] = board[x][j];
    }

    for (int j = y - 1; j >= 0; j--) {
        if (board[x][j] == 'X' || board[x][j] == 'P')
            break;
        possibleMoves[x][j] = board[x][j];
    }
    possibleMoves[x][y] = 'P';
    return possibleMoves;



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