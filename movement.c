#include <stdio.h>
#include <ctype.h>
#include "board.h"
#include "penguin.h"
#include "system.h"
#include "player.h"
#include "textColor.h"

#define MOVE_IS_NOT_POSSIBLE 0
#define MOVE_IS_POSSIBLE 1



void makeAMove(struct Board* board) { //Roma's function
	//moves given player from its initial position to available place in the board

	struct Player* current = getCurrentPlayer();
	int ID = getPenguinID();

	int currentX = current->penguins[ID].coordinateX - 1;
	int currentY = letterToInt(current->penguins[ID].coordinateY) - 1;

	struct Board possibleMoves = getPossibleMoves(board, current);


	int X;
	int Y;
	char buffer;
	do {
		printf("\nInput number of the row to move (ex. 1): ");
		X = fixscanf();
		X--;
		printf("Input number of the column to move (ex. A): ");
		scanf(" %c", &buffer);
		Y = letterToInt((char)toupper(buffer)) - 1;

		if (X >= board->size || X < 0 || Y < 0 || Y >= board->size) {
			displayBoard(board);
			setColor(LIGHT_RED);
			printf("\nERROR: incorrect coordinate input, please, try again.\n");
			setColor(LIGHT_GRAY);

		}


		if (board->grid[X][Y] != possibleMoves.grid[X][Y] || board->grid[X][Y] == 'P') {
			displayBoard(board);
			setColor(LIGHT_RED);
			printf("\nERROR: it is impossbile to move there.\n");
			setColor(LIGHT_GRAY);

		}
	} while (board->grid[X][Y] != possibleMoves.grid[X][Y]);
	board->grid[currentX][currentY] = '_';


	board->grid[X][Y] = 'P';

	current->penguins[ID].coordinateX = X + 1;
	current->penguins[ID].coordinateY = (char)('A' + Y);

	// Score counting by Yuki
	if ('1' == possibleMoves.grid[X][Y]) {
		current->points += 1;
	}

	if ('2' == possibleMoves.grid[X][Y]) {
		current->points += 2;
	}

	if ('3' == possibleMoves.grid[X][Y]) {
		current->points += 3;
	}

};

int checkMove(struct Board* board, struct Player* current) { //Roma's function
	struct Board possibleMoves = getPossibleMoves(board, current);
	for (int i = 0; i < board->size; i++) {
		for (int j = 0; j < board->size; j++) {
			if (board->grid[i][j] == possibleMoves.grid[i][j]) {
				return MOVE_IS_POSSIBLE;
			}
		}
	}
	return MOVE_IS_NOT_POSSIBLE;
}



//To demonstrate possibleMoves

/*
	possibleMoves[currentX][currentY] = 'X';
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (j == 0)
				printf("%d%s", i + 1, (i < 9) ? " " : "");

			printf(" %c", possibleMoves[i][j]);
			setColor(7);
		}
		printf("\n");
	}
	printf("\n\n");
*/

