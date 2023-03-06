#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "board.h"
#include "penguin.h"
#include "system.h"
#include "gamemode.h"
#include "player.h"
#include "textColor.h"
#include "gamePhase.h"


void placePenguin(struct Board* board, struct Player* player) { //Roma's function
	int pengID = getPenguinID();

	setColor(player->color);
	printf("\n%s", player->name);
	setColor(LIGHT_GRAY);
	printf("'s turn\n");
	printf("Choose your row (for example 1): ");
	int coordinateX;
	coordinateX = fixscanf();
	char coordinateY;
	printf("Choose your column: (for example A): ");
	scanf(" %c", &coordinateY);
	coordinateY = (char)toupper(coordinateY);

	if (letterToInt(coordinateY) == 0 || coordinateX > board->size) {
		displayBoard(board);
		setColor(LIGHT_RED);
		printf("ERROR: incorrect coordinate input, please, try again.\n");
		setColor(LIGHT_GRAY);
		placePenguin(board, player);
		return;
	}


	int x = coordinateX - 1;
	int y = letterToInt(coordinateY) - 1;

	//Placement validation by Yuki
	// check this placement is inside the board size   
	while (y < 0 || y >= board->size || x < 0 || x >= board->size) {
		displayBoard(board);
		setColor(LIGHT_RED);
		printf("\nERROR: incorrect coordinate input, please, try again.\n");
		setColor(LIGHT_GRAY);
		printf("Choose your row (for example 1): ");
		coordinateX = fixscanf();
		printf("Choose your column: (for example A): ");
		scanf(" %c", &coordinateY);
		coordinateY = (char)toupper(coordinateY);
		x = coordinateX - 1;
		y = letterToInt(coordinateY) - 1;

	}

	//check the designated cell only has 1 fish or not
	while (board->grid[x][y] != '1') { // I used != 1 to avoid X, 2, 3, P.
		setColor(LIGHT_RED);
		printf("\nERROR: You can't place here. Please, choose a cell with 1 fish: ");
		setColor(LIGHT_GRAY);
		printf("\nChoose your row (ex. 1): ");
		coordinateX = fixscanf();
		printf("Choose your column: (ex. A): ");
		scanf(" %c", &coordinateY);
		coordinateY = (char)toupper(coordinateY);
		x = coordinateX - 1;
		y = letterToInt(coordinateY) - 1;
	}

	player->penguins[pengID].coordinateX = coordinateX;
	player->penguins[pengID].coordinateY = coordinateY;
	player->numberOfPenguins += 1;
	player->points += 1;

	board->grid[player->penguins[pengID].coordinateX - 1][letterToInt(player->penguins[pengID].coordinateY) - 1] = 'P';
}



void placeFish(struct Board* board, int amount) { //Michal's function
	int availableCells = 0;

	srand((unsigned int)time(NULL));
	for (int i = 0; i < board->size; i++) {
		for (int j = 0; j < board->size; j++) {
			board->grid[i][j] = (rand() % 4) + '0';
			if (board->grid[i][j] == '1') {
				availableCells = availableCells + 1;
			}
			if (board->grid[i][j] == '0') {
				board->grid[i][j] = '_';
			}

		}
	}

	if (availableCells < amount) {
		placeFish(board, amount);
	}
	displayBoard(board);

}


