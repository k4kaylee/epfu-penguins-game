#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "player.h"
#include "textColor.h"

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

void displayPlayerBoard(int amount, struct Player* players) {
	system("cls");
	printf("List of Players: \n");
	for(int i = 0; i < amount; i++)
		printf("Name: %s\nID: %d\nPoints: %d\n\n", players[i].name, players[i].id, players[i].points);
	printf("Press any key to continue...");
	_getch();
}

struct Player getPlayer(struct Player* players, int i) {
	return players[i];
}