#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "board.h"
#include "system.h"
#include "gamemode.h"
#include "player.h"
#include "textColor.h"
#include "gamePhase.h"


void placePenguin(struct Board* board, struct Player* player) {
	printf("\n%s's turn\n", player->name);
	printf("Choose your row (for example 1): ");
	int coordinateX;
	scanf("%d", &coordinateX);
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


	int x = coordinateX;
	int y = letterToInt(coordinateY);
	x--;
	y--;

	// check this placement is inside the board size
	if (y < 0 || y >= board->size || x < 0 || x >= board->size) {
		displayBoard(board);
		setColor(LIGHT_RED);
		printf("\nERROR: incorrect coordinate input, please, try again.\n");
		setColor(LIGHT_GRAY);
		placePenguin(board, player);
		return;
	}

	//check the designated cell only has 1 fish or not
	while (board->grid[x][y] != '1') { // I used != 1 to avoid X, 2, 3, P.
		setColor(LIGHT_RED);
		printf("\nERROR: You can't place here. Please, choose a cell with 1 fish: ");
		setColor(LIGHT_GRAY);
		printf("\nChoose your row (ex. 1): ");
		scanf("%d", &x);
		printf("Choose your column: (ex. A): ");
		scanf(" %c", &coordinateY);
		y = letterToInt(coordinateY);
		x--;
		y--;
	}
	player->penguinX = coordinateX;
	player->penguinY = coordinateY;
	player->points += 1;

	board->grid[player->penguinX - 1][letterToInt(player->penguinY) - 1] = 'P';

}



void placeFish(struct Board* board, int amount) {
	int availableCells = 0;

	srand((unsigned int)time(NULL));
	for (int i = 0; i < board->size; i++) {
		for (int j = 0; j < board->size; j++) {
			board->grid[i][j] = (rand() % 4) + '0';
			if (board->grid[i][j] == '1') {
				availableCells = availableCells + 1;
			}
			if (board->grid[i][j] == '0') {
				board->grid[i][j] = 'X';
			}

		}
	}

	if (availableCells < amount) {
		placeFish(board, amount);
	}
	displayBoard(board);

}


