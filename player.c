#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct Player {
	char* name;
	int id;
	int points;
};

int getAmountOfPlayers() {
	int amount;
	system("cls");
	printf("Please, input the amount of players (at least 1, max 5): ");
	scanf("%d", &amount);
	while (amount < 1 || amount > 5) {
		system("cls");
		printf("ERROR: incorrect player amount. Please, type it again (at least 1, max 5): ");
		scanf("%d", &amount);
	}
	return amount;
};

struct Player* getPlayers(int amount, struct Player* players) {
	players = malloc(sizeof(*players) * amount);
	for (int i = 0; i < amount; i++) {
		printf("\n%d out of %d\n", i, amount);
		//system("cls");
		printf("Hi Player %d! How should I call you?(no more than 20 symbols): ", i);

		char* name = malloc(sizeof(char) * 20);
		scanf("%s", name);
		name[strcspn(name, "\r\n")] = 0; //to get rid of \0

		players[i].name = name;
		players[i].id = i;
		players[i].points = 0;
	}

	return players;
};

void displayPlayerBoard(int amount, struct Player* players) {
	system("cls");
	for(int i = 0; i < amount; i++)
		printf("Name: %s\nID: %d\nPoints: %d\n\n", players[i].name, players[i].id, players[i].points);
	int check;
	printf("\nCheck.");
	scanf("%d", &check);
}