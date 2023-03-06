#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <conio.h>

#include "placement.h"
#include "movement.h"
#include "board.h"
#include "player.h"
#include "textColor.h"
#include "gamePhase.h"
#include "fileManager.h"
#include "system.h"



int getGamemode() {
	int isInteractive = 0;
	printf("Welcome to 'Hey! That's my fish!'\n\nFirst of all, we should choose the gamemode.\nPlease, put '0' for autonomous mode or '1' for interative: ");
	scanf("%d", &isInteractive);
	while (isInteractive != 0 && isInteractive != 1) {
		clear();
		printf("%d\n", isInteractive);
		setColor(12);
		printf("ERROR: incorrect gamemode input.\nPlease, choose gamemode again (0 - autunomous, 1 - interactive): ");
		setColor(7);
		scanf("%d", &isInteractive);
	}
	return isInteractive;
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

	char** board = 0;
	int size = getSize();
	board = getBoard(size, board);
	struct Player* current;

	placeFish(size, board, amountOfPlayers * amountOfPenguins);


	fprintf(log, "\n\nPLACEMENT:");
	logBoard(size, board, log);
	for (int j = 0; j < amountOfPenguins; j++) {
		for (int i = 0; i < amountOfPlayers; i++) {
			placePenguin(size, board, getPlayer(players, i));
			current = getPlayer(players, i);
			fprintf(log, "\n%s places their penguin at %d %c", current->name, current->penguinX, current->penguinY);
			displayBoard(size, board);
		}
		if (j == amountOfPenguins - 1) {
			setGamePhase(1);
		}
	}


	fprintf(log, "\n\nMOVEMENT:");
	for (int i = 0; i < amountOfPlayers; i++) {
		if (getGamePhase() == 1)
			setCurrentPlayer(getPlayer(players, i));
		displayBoard(size, board);
		makeAMove(board, size);
		current = getPlayer(players, i);
		fprintf(log, "\n%s moves their penguin to %d %c\n", current->name, current->penguinX, current->penguinY + 1);
		if (i == amountOfPlayers - 1)
			setGamePhase(2);
	}
	displayBoard(size, board);
	logBoard(size, board, log);
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
		snprintf(buf, sizeof(buf), "%s\\programs\\%s", _getcwd(buf, BUFSIZ), dirList[current->fileID - 1] );
		clear();
		system(buf);
		fprintf(log, "%s is running %s\n", current->name, dirList[current->fileID - 1]);
	}
};

