char** getBoard(int size, char** board); //creates a two-dimensional dynamic array with a size received by getSize() and fills it with 'X'
int getSize(void);//gets size parameter for board
int letterToInt(char coordinate);//custom function used to translate coordinates on x-axis from symbols to numbers
void displayBoard(int size, char** board);//prints the board at its current state and uses setColor() function when its necessary
