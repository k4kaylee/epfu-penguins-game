#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "gamemode.h"
#include "player.h"
#include "textColor.h"
#include "gamePhase.h"

#include <conio.h>
#include <ctype.h>


void placePenguin(int size, char** board, struct Player* player) {
	printf("\n%s's turn\n", player->name);
	printf("Choose your row (ex. 1): ");
	int coordinateX;
	scanf("%d", &coordinateX);
	char coordinateY;
	printf("Choose your column: (ex. A): ");
	scanf(" %c", &coordinateY);

	if (letterToInt(coordinateY) == 0 || coordinateX > size) {
		displayBoard(size, board);
		setColor(12);
		printf("ERROR: incorrect coordinate input, please, try again.\n");
		setColor(7);
		placePenguin(size, board, player);
		return;
	}


	int x = coordinateX;
	int y = letterToInt(coordinateY);
	x--;
	y--;

	// check this placement is inside the board size
	if (y < 0 || y >= size || x < 0 || x >= size) {
		displayBoard(size, board);
		setColor(12);
		printf("\nERROR: incorrect coordinate input, please, try again.\n");
		setColor(7);
		placePenguin(size, board, player);
		return;
	}

	//check the designated cell only has 1 fish or not
	while (board[x][y] != '1') { // I used != 1 to avoid X, 2, 3, P.
		setColor(12);
		printf("\nERROR: You can't place here. Please, choose a cell with 1 fish: ");
		setColor(7);
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

	board[player->penguinX - 1][letterToInt(player->penguinY) - 1] = 'P';

}





void placeFish(int size, char** board, int amount) {
	int availableCells = 0;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[i][j] = (rand() % 4) + '0';
			if (board[i][j] == '1') {
				availableCells = availableCells + 1;
			}
			if (board[i][j] == '0') {
				board[i][j] = 'X';
			}

		}
	}

	if (availableCells < amount) {
		placeFish(size, board, amount);
	}
	displayBoard(size, board);

}


