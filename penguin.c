#include "penguin.h"
#include "textColor.h"
#include "system.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void choosePenguin(struct Board* board) { //Michal's function

	int xpen;
	char ypen;

	struct Player* current = getCurrentPlayer();
	setColor(current->color);
	printf("\n%s", current->name);
	setColor(LIGHT_GRAY);
	printf("'s move\n");
	printf("choose penguin you want to move\n");
	printf("\nInput number of the row (for example, 1): ");
	xpen = fixscanf();
	printf("Input number of the row (for example, A): ");
	scanf(" %c", &ypen);
	ypen = (char)toupper(ypen);

	if ((xpen == current->penguins[0].coordinateX) && (ypen == current->penguins[0].coordinateY)) {
		setPenguinID(0);
	}
	else if ((xpen == current->penguins[1].coordinateX) && (ypen == current->penguins[1].coordinateY)) {
		setPenguinID(1);
	}
	else if ((xpen == current->penguins[2].coordinateX) && (ypen == current->penguins[2].coordinateY)) {
		setPenguinID(2);
	}
	else {
		displayBoard(board);
		setColor(LIGHT_RED);
		printf("\nERROR: incorrect coordinate input, please, try again.\n");
		setColor(LIGHT_GRAY);
		choosePenguin(board);

	}
};

void setAmountOfPenguins() { //Michal's function
	int pengus;
	clear();
	printf("Please, input the amount of penguins (at least 1, max 3): ");
	pengus = fixscanf();
	while (pengus < 1 || pengus > 3) {
		clear();
		setColor(LIGHT_RED);
		printf("ERROR: incorrect penguins amount. Please, type it again (at least 1, max 3): ");
		setColor(LIGHT_GRAY);
		pengus = fixscanf();
	}
	clear();
	amountOfPenguins = pengus;
};

int getPenguinID() {
	return penguinID;
};

void setPenguinID(int ID) {
	penguinID = ID;
};

void deletePenguin(struct Player* player) {
	int id = getPenguinID();
	for (int i = id; i < player->numberOfPenguins - 1; i++) {
		player->penguins[i] = player->penguins[i + 1];
	}
	player->numberOfPenguins -= 1;
	player->penguins = realloc(player->penguins, player->numberOfPenguins * sizeof(struct Penguin));
};

