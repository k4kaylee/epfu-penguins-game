#include <stdio.h>
#include <stdlib.h>

#include <conio.h>

#include "placement.h"
#include "board.h"
#include "player.h"
#include "textColor.h"
#include "gamePhase.h"



int getGamemode() {
	int isInteractive = 0;
	printf("Welcome to 'Hey! That's my fish!'\n\nFirst of all, we should choose the gamemode.\nPlease, put '0' for autonomous mode or '1' for interative: ");
	scanf("%d", &isInteractive);
	while (isInteractive != 0 && isInteractive != 1) {
		system("cls");
		printf("%d\n", isInteractive);
		setColor(12);
		printf("ERROR: incorrect gamemode input.\nPlease, choose gamemode again (0 - autunomous, 1 - interactive): ");
		setColor(7);
		scanf("%d", &isInteractive);
	}
	return isInteractive;
};

void runInteractive() {
	int amountOfPlayers = getAmountOfPlayers();
	struct Player* players = 0;
	players = malloc(sizeof(struct Player) * amountOfPlayers);

	players = getAllPlayers(amountOfPlayers, players);
	displayPlayerBoard(amountOfPlayers, players);

	char** board = 0;
	int size = getSize();
	board = getBoard(size, board);

	placeFish(size, board, amountOfPlayers);
	
	for (int i = 0; i < amountOfPlayers; i++) {
		placePenguin(size, board, getPlayer(players, i));
		displayBoard(size, board);
		if (i == amountOfPlayers - 1)
			setGamePhase(1);
	}

	for (int i = 0; i < amountOfPlayers; i++) {
		if (getGamePhase() == 1)
			setCurrentPlayer(getPlayer(players, i));
		displayBoard(size, board);
		_getch();
	}
};

void runAutonomous() {
	printf("\nAutonomous!");
};

