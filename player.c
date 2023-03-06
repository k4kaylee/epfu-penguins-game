#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "player.h"
#include "textColor.h"
#include "board.h"
#include "system.h"
#include <assert.h>



struct Player* currentPlayer;
struct Player* players = 0;
int amountOfPlayers;
int amountOfPenguins;

struct Player* getCurrentPlayer() {
	return currentPlayer;
}

void setCurrentPlayer(struct Player* player) {
	currentPlayer = player;
}

void setAmountOfPlayers() {
	int amount;
	clear();
	printf("Please, input the amount of players (at least 1, max 5): ");
	amount = fixscanf();
	while (amount < 1 || amount > 5) {
		clear();
		setColor(LIGHT_RED);
		printf("ERROR: incorrect player amount. Please, type it again (at least 1, max 5): ");
		setColor(LIGHT_GRAY);
		amount = fixscanf();
	}
	clear();
	amountOfPlayers = amount;
};

struct Player* getAllPlayers() {
	for (int i = 0; i < amountOfPlayers; i++) {
		printf("%s%d out of %d\n", (i != 0) ? "\n" : "", i + 1, amountOfPlayers);
		printf("Hi Player %d! How should I call you?: ", i + 1);

		char* name = malloc(sizeof(char) * 20);
		scanf("%s", name);
		name[strcspn(name, "\r\n")] = 0; //to get rid of \0

		int color = getPlayerColor();
		while(color == NO_COLOR)
		{    
			setColor(12);
			printf("ERROR: color was not found.\n");
			setColor(7);
			color = getPlayerColor();
		}
		players[i].color = color;
		players[i].name = name;
		players[i].id = i+1;
		players[i].points = 0;
		players[i].numberOfPenguins = 0;
		players[i].movementStatus = MOVEMENT_IS_NOT_DONE;
	}

	return players;
};



void checkPlayerData() {
	int check;
	printf("Is data correct? (1 - accept, 0 - edit): ");
	check = fixscanf();
	if (!check) {
		int playerId;
		printf("\nInput id of a player you want to change: ");
		playerId = fixscanf();
		--playerId;
		while (playerId > amountOfPlayers || playerId < 0) {
			setColor(LIGHT_RED);
			printf("\n\nERROR: no player with such an ID. Input again: ");
			setColor(LIGHT_GRAY);
			playerId = fixscanf();
		}
		
		printf("\nChange %s's name to: ", players[playerId].name);
		char* name = malloc(sizeof(char) * 20);
		assert(name);
		scanf("%s", name);
		name[strcspn(name, "\r\n")] = 0; //to get rid of \0

		players[playerId].name = name;
		displayPlayerBoard();
	}
}

void displayPlayerBoard() {
	clear();
	printf("List of Players: \n");
	for (int i = 0; i < amountOfPlayers; i++) {
		printf("Name: %s\nID: %d\nPoints: %d\nColor: ", players[i].name, players[i].id, players[i].points);
		switch (players[i].color) {
			case BLUE: 
				setColor(BLUE);
				printf("Blue\n\n");
				break;
			case RED: 
				setColor(RED);
				printf("Red\n\n");
				break;;
			case CYAN: 
				setColor(CYAN);
				printf("Cyan\n\n");
				break;
			case MAGENTA: 
				setColor(MAGENTA);
				printf("Magenta\n\n");
				break;
			case YELLOW: 
				setColor(YELLOW);
				printf("Yellow\n\n");
				break;
		}
		setColor(LIGHT_GRAY);
	}
	checkPlayerData();

}

struct Player* getPlayer(int playerID) {
	return &players[playerID];
}

struct Board getPossibleMoves(struct Board* board, struct Player* current) {

	struct Board possibleMoves;
	possibleMoves.grid = malloc(sizeof(*board->grid) * board->size);
	for (int i = 0; i < board->size; i++)
		possibleMoves.grid[i] = malloc(sizeof(**board->grid) * board->size);

	for (int i = 0; i < board->size; i++) {
		for (int j = 0; j < board->size; j++)
			possibleMoves.grid[i][j] = '0';
	}

	if (current->numberOfPenguins == 0) {
		return possibleMoves;
	}

	int pengID = getPenguinID();

	int x = current->penguins[pengID].coordinateX - 1;
	int y = letterToInt(current->penguins[pengID].coordinateY) - 1;

	for (int i = x + 1; i < board->size; i++) {
		if (board->grid[i][y] == '_' || board->grid[i][y] == 'P')
			break;
		possibleMoves.grid[i][y] = board->grid[i][y];
	}

	for (int i = x - 1; i >= 0; i--) {
		if (board->grid[i][y] == '_' || board->grid[i][y] == 'P')
			break;
		possibleMoves.grid[i][y] = board->grid[i][y];
	}

	for (int j = y + 1; j < board->size; j++) {
		if (board->grid[x][j] == '_' || board->grid[x][j] == 'P')
			break;
		possibleMoves.grid[x][j] = board->grid[x][j];
	}

	for (int j = y - 1; j >= 0; j--) {
		if (board->grid[x][j] == '_' || board->grid[x][j] == 'P')
			break;
		possibleMoves.grid[x][j] = board->grid[x][j];
	}

	possibleMoves.grid[x][y] = '_';
	return possibleMoves;
}


void displayPoints() {
	printf("SCORE:");
	struct Player* current;
	int max = 0;
	for (int i = 0; i < amountOfPlayers; i++) {
		setCurrentPlayer(getPlayer(i));
		current = getCurrentPlayer();
		if (current->points > max)
			max = current->points;
	}

	for (int i = 0; i < amountOfPlayers; i++) {
		setCurrentPlayer(getPlayer(i));
		current = getCurrentPlayer();
		setColor(current->color);
		printf("\n%s", current->name);
		setColor(LIGHT_GRAY);
		printf(": %d", current->points);
		if (current->points == max) {
			setColor(LIGHT_RED);
			printf(" - WINNER!");
			setColor(LIGHT_GRAY);
		}
	}
}

void getPlayerFile(int amountOfFiles) {
	int fileID;
	struct Player* current = getCurrentPlayer();
	do {
		printf("%s, choose the number of your program: ", current->name);
		scanf("%d", &fileID);
	} while (fileID <= 0 || fileID > amountOfFiles);
	current->fileID = fileID;
}

