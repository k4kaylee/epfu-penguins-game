#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "gamemode.h"
#include "system.h"
#include "penguinBot.h"



int main(int argc, char** argv) {
	FILE* log = createlog();
	clearLogDir();
	if (argc > 1) {
		return runPenguinBot(argc, argv);
	}
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