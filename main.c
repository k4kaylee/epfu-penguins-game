#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "gamemode.h"
#include "system.h"



int main() {
	FILE* log = createlog();
	clearLogDir();
	int gamemode = getGamemode();
	gamemode ?
		runInteractive(log)
		:
		runAutonomous(log);
	printf("\n\nPress any key to finish");
	getChar();
	fclose(log);
	return 0;
}