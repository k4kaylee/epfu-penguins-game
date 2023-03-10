#include <stdio.h>
#include <stdlib.h>

#include "placement.h"
#include "penguin.h"
#include "movement.h"
#include "board.h"
#include "player.h"
#include "textColor.h"
#include "gamePhase.h"
#include "fileManager.h"
#include "system.h"
#include "penguin.h"
#include "textColor.h"

#define INTERACTIVE 0
#define AUTONOMOUS 1

int getGamemode() {
	int gamemode;
	printf("Welcome to 'Hey! That's my fish!'\n\nFirst of all, we should choose the gamemode.\nPlease, put '0' for autonomous mode or '1' for interative: ");
	gamemode = fixscanf();
	while (gamemode != INTERACTIVE && gamemode != AUTONOMOUS) {
		clear();
		setColor(LIGHT_RED);
		printf("ERROR: incorrect gamemode input.\nPlease, choose gamemode again (0 - autunomous, 1 - interactive): ");
		setColor(LIGHT_GRAY);
		gamemode = fixscanf();
	}
	return gamemode;
};

void runInteractive(FILE* log) {
	initColorsList();
	fprintf(log, "\nGamemode: Interactive");
	setAmountOfPlayers();
	fprintf(log, "\nAmount of players: %d", amountOfPlayers);
    setAmountOfPenguins();
	fprintf(log, "\nPenguins for each player: %d", amountOfPenguins);
	players = malloc(sizeof(struct Player) * amountOfPlayers);
	for (int i = 0; i < amountOfPlayers; i++) {
		players[i].penguins = malloc(sizeof(struct Penguin) * amountOfPenguins);
	}

	players = getAllPlayers();
	displayPlayerBoard();

	for (int i = 0; i < amountOfPlayers; i++) {
		fprintf(log, "\n%d: %s", i + 1, players[i].name);
	}

	struct Board* board = malloc(sizeof(struct Board));
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
			placePenguin(board, getPlayer(i));
			fprintf(log, "\n%s places their penguin at %d %c", players[i].name, players[i].penguins[j].coordinateX, players[i].penguins[j].coordinateY);
			displayBoard(board);
		}
	}




	fprintf(log, "\n\nMOVEMENT:\n");
	int playerCounter = amountOfPlayers;
	while (playerCounter > 0) {
		for (int i = 0; i < amountOfPlayers; i++) {
			current = getPlayer(i);
			setCurrentPlayer(current);

			if (current->movementStatus || current->penguins == NULL) {
				continue;
			}

			for (int k = 0; k < amountOfPlayers; k++) {
				for (int j = 0; j < players[k].numberOfPenguins; j++) {
					setPenguinID(j);
					if (players[k].penguins != NULL && !checkMove(board, &players[k])) {
						deletePenguin(&players[k]);
						if (players[k].numberOfPenguins == 0) {
							playerCounter--;
							players[k].numberOfPenguins = MOVEMENT_IS_DONE;
						}
					}
				}
			}

			if (amountOfPenguins != 1 && current->numberOfPenguins != 1) {
				setGamePhase(CHOOSING_PENGUIN);
				displayBoard(board);
				choosePenguin(board);//lets player choose a penguin and sets penguinID
			}
			
			if (playerCounter != 0 && current->numberOfPenguins != 0) {
				setGamePhase(MOVEMENT);
				displayBoard(board);
				makeAMove(board);
				int pengID = getPenguinID();
				fprintf(log, "%s moves their penguin to %d %c\n", current->name, current->penguins[pengID].coordinateX, current->penguins[pengID].coordinateY);
			}
		}
	}
	setGamePhase(END_OF_GAME);
	
	displayBoard(board);
	logBoard(board, log);
	displayPoints();
	logPoints(log);
	printf("\n\nThank you for the game! ^_^");
};



void runAutonomous(FILE* log) {
	fprintf(log, "\nGamemode: Autonomous");
	clear();
	setAmountOfPlayers();
	fprintf(log, "\nAmount of players: %d\n", amountOfPlayers);
	players = malloc(sizeof(struct Player) * amountOfPlayers);

	players = getAllPlayers();


	for (int i = 0; i < amountOfPlayers; i++) {
		fprintf(log, "\n%d: %s", i + 1, players[i].name);
	}

	getFiles();
	printFiles();
	fprintf(log, "\n\nProgram files were scanned succesfully.\n\n");
	
	for (int i = 0; i < amountOfPlayers; i++) {
		setCurrentPlayer(getPlayer(i));
		getPlayerFile(amountOfFiles);
	}
	char buf[BUFSIZ];
	struct Player* current;
	for (int i = 0; i < amountOfPlayers; i++) {
		setCurrentPlayer(getPlayer(i));
		current = getPlayer(i);
		//_getcwd(buf, BUFSIZ); needs to be tested for linux
		snprintf(buf, sizeof(buf), "%s\\programs\\%s", getCWD(buf, BUFSIZ), dirList[current->fileID - 1] );
		clear();
		system(buf);
		fprintf(log, "%s is running %s\n", current->name, dirList[current->fileID - 1]);
	}
};

