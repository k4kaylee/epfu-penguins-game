#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "gamemode.h"



int main() {
	int gamemode = getGamemode();
	gamemode ?
		runInteractive()
		:
		runAutonomous();

	return 0;
}