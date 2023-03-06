#include <stdio.h>
#include <stdlib.h>

#include "placement.h"
#include "penguinID.h"
#include "movement.h"
#include "board.h"
#include "player.h"
#include "textColor.h"
#include "gamePhase.h"
#include "fileManager.h"
#include "system.h"

#define INTERACTIVE 0
#define AUTONOMOUS 1

int getGamemode() {
	int gamemode;
	printf("Welcome to 'Hey! That's my fish!'\n\nFirst of all, we should choose the gamemode.\nPlease, put '0' for autonomous mode or '1' for interative: ");
	scanf("%d", &gamemode);
	while (gamemode != INTERACTIVE && gamemode != AUTONOMOUS) {
		clear();
		setColor(LIGHT_RED);
		printf("ERROR: incorrect gamemode input.\nPlease, choose gamemode again (0 - autunomous, 1 - interactive): ");
		setColor(LIGHT_GRAY);
		scanf("%d", &gamemode);
	}
	return gamemode;
};

void runInteractive(FILE* log) {	
	fprintf(log, "\nGamemode: Interactive");
	int amountOfPlayers = getAmountOfPlayers();
	fprintf(log, "\nAmount of players: %d", amountOfPlayers);
	int amountOfPenguins = getAmountOfPenguins();
	fprintf(log, "\nPenguins for each player: %d", amountOfPenguins);
	struct Player* players = 0;
	players = malloc(sizeof(struct Player) * amountOfPlayers);

	players = getAllPlayers(amountOfPlayers, players);
	displayPlayerBoard(amountOfPlayers, players);

	for (int i = 0; i < amountOfPlayers; i++) {
		fprintf(log, "\n%d: %s", i + 1, players[i].name);
	}


	struct Board* board = malloc(sizeof(board));
	board->grid = 0;
	board->size = getSize();
	board->grid = getBoard(board->size);
	struct Player* current;

	placeFish(board, amountOfPlayers * amountOfPenguins);

	
	fprintf(log, "\n\nPLACEMENT:");
	logBoard(board, log);

	setGamePhase(PLACEMENT);
	for (int j = 0; j < amountOfPenguins; j++) {
		for (int i = 0; i < amountOfPlayers; i++) {
			setPenguinID(j);
			current = getPlayer(players, i);
			placePenguin(board, current);
			fprintf(log, "\n%s places their penguin at %d %c", current->name, current->penguinX[j], current->penguinY[j]);
			displayBoard(board);
		}
	}




	fprintf(log, "\n\nMOVEMENT:\n");
	for (int i = 0; i < amountOfPlayers; i++) {
		setGamePhase(CHOOSING_PENGUIN);
		displayBoard(board);
		current = getPlayer(players, i);
		setCurrentPlayer(current);
		choosePenguin(board, current);
		setGamePhase(MOVEMENT);
		displayBoard(board);
		makeAMove(board);
		int pengID = getPenguinID();
		fprintf(log, "%s moves their penguin to %d %c\n", current->name, current->penguinX[pengID], current->penguinY[pengID]);
		if (i == amountOfPlayers - 1)
			setGamePhase(2);
	}


	displayBoard(board);
	logBoard(board, log);
	displayPoints(players, amountOfPlayers);
	logPoints(players, amountOfPlayers, log);
	printf("\n\nThank you for the game! ^_^");
};

void runAutonomous(FILE* log) {
	fprintf(log, "\nGamemode: Autonomous");
	clear();
	int amountOfPlayers = getAmountOfPlayers();
	fprintf(log, "\nAmount of players: %d\n", amountOfPlayers);
	struct Player* players = 0;
	players = malloc(sizeof(struct Player) * amountOfPlayers);

	players = getAllPlayers(amountOfPlayers, players);


	for (int i = 0; i < amountOfPlayers; i++) {
		fprintf(log, "\n%d: %s", i + 1, players[i].name);
	}

	getFiles();
	printFiles();
	fprintf(log, "\n\nProgram files were scanned succesfully.\n\n");
	
	for (int i = 0; i < amountOfPlayers; i++) {
		setCurrentPlayer(getPlayer(players, i));
		getPlayerFile(amountOfFiles);
	}
	char buf[BUFSIZ];
	struct Player* current;
	for (int i = 0; i < amountOfPlayers; i++) {
		setCurrentPlayer(getPlayer(players, i));
		current = getPlayer(players, i);
		//_getcwd(buf, BUFSIZ); needs to be tested for linux
		snprintf(buf, sizeof(buf), "%s\\programs\\%s", getCWD(buf, BUFSIZ), dirList[current->fileID - 1] );
		clear();
		system(buf);
		fprintf(log, "%s is running %s\n", current->name, dirList[current->fileID - 1]);
	}
};

