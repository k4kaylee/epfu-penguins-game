#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "player.h"
#include "textColor.h"
#include "board.h"



struct Player* currentPlayer;

struct Player* getCurrentPlayer() {
	return currentPlayer;
}

void setCurrentPlayer(struct Player* player) {
	currentPlayer = player;
}

int getAmountOfPlayers() {
	int amount;
	system("cls");
	printf("Please, input the amount of players (at least 1, max 5): ");
	scanf("%d", &amount);
	while (amount < 1 || amount > 5) {
		system("cls");
		setColor(12);
		printf("ERROR: incorrect player amount. Please, type it again (at least 1, max 5): ");
		setColor(7);
		scanf("%d", &amount);
	}
	system("cls");
	return amount;
};

struct Player* getAllPlayers(int amount, struct Player* players) {
	for (int i = 0; i < amount; i++) {
		printf("%s%d out of %d\n", (i != 0) ? "\n" : "", i + 1, amount);
		printf("Hi Player %d! How should I call you?: ", i + 1);

		char* name = malloc(sizeof(char) * 20);
		scanf("%s", name);
		name[strcspn(name, "\r\n")] = 0; //to get rid of \0

		players[i].name = name;
		players[i].id = i+1;
		players[i].points = 0;
	}

	return players;
};

void checkPlayerData(int amount, struct Player* players) {
	int check;
	printf("Is data correct? (1 - accept, 0 - edit): ");
	scanf("%d", &check);
	if (!check) {
		int playerId;
		printf("\nInput id of a player you want to change: ");
		scanf("%d", &playerId);
		--playerId;
		while (playerId > amount || playerId < 0) {
			setColor(12);
			printf("\n\nERROR: no player with such an ID. Input again: ");
			setColor(7);
			scanf("%d", &playerId);
		}
		
		printf("\nChange %s's name to: ", players[playerId].name);
		char* name = malloc(sizeof(char) * 20);
		scanf("%s", name);
		name[strcspn(name, "\r\n")] = 0; //to get rid of \0

		players[playerId].name = name;
		displayPlayerBoard(amount, players);
	}
}

void displayPlayerBoard(int amount, struct Player* players) {
	system("cls");
	printf("List of Players: \n");
	for(int i = 0; i < amount; i++)
		printf("Name: %s\nID: %d\nPoints: %d\n\n", players[i].name, players[i].id, players[i].points);

	checkPlayerData(amount, players);

}

struct Player* getPlayer(struct Player* players, int i) {
	return &players[i];
}

char** getPossibleMoves(char** board, int size) {
	struct Player* current = getCurrentPlayer();

	char** possibleMoves = 0;
	possibleMoves = malloc(sizeof(*board) * size);
	for (int i = 0; i < size; i++)
		possibleMoves[i] = malloc(sizeof(**board) * size);

	for (int i = 0; i < size; i++) {

		for (int j = 0; j < size; j++)
			possibleMoves[i][j] = '0';
	}



	//How can i get information from structure in another function?
	int x = current->penguinX - 1;
	int y = letterToInt(current->penguinY) - 1;

	for (int i = x + 1; i < size; i++) {
		if (board[i][y] == 'X' || board[i][y] == 'P')
			break;
		possibleMoves[i][y] = board[i][y];
	}

	for (int i = x - 1; i >= 0; i--) {
		if (board[i][y] == 'X' || board[i][y] == 'P')
			break;
		possibleMoves[i][y] = board[i][y];
	}

	for (int j = y + 1; j < size; j++) {
		if (board[x][j] == 'X' || board[x][j] == 'P')
			break;
		possibleMoves[x][j] = board[x][j];
	}

	for (int j = y - 1; j >= 0; j--) {
		if (board[x][j] == 'X' || board[x][j] == 'P')
			break;
		possibleMoves[x][j] = board[x][j];
	}
	possibleMoves[x][y] = 'P';
	return possibleMoves;



}


