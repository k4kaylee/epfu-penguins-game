#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "board.h"
#include "gamemode.h"
#include "system.h"



int main() {
	int gamemode = getGamemode();
	gamemode ?
		runInteractive()
		:
		runAutonomous();
	printf("\n\nPress any key to finish");
	getChar();
	return 0;
}