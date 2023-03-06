#pragma once
struct Board{
	int size;
	char** grid;
};

char** getBoard(int size); //creates a two-dimensional dynamic array with a size received by getSize() and fills it with 'X'
int getSize(void);//gets size parameter for board
void displayBoard(struct Board* board); //prints the board at its current state and uses setColor() function when its necessary
