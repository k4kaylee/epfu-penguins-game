#include <stdio.h>
#include <ctype.h>
#include "board.h"
#include "penguinID.h"
#include "system.h"
#include "player.h"
#include "textColor.h"



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

	if ((xpen == current->penguinX[0]) && (ypen == current->penguinY[0])) {
		setPenguinID(0);
	}
	else if ((xpen == current->penguinX[1]) && (ypen == current->penguinY[1])) {
		setPenguinID(1);
	}
	else if ((xpen == current->penguinX[2]) && (ypen == current->penguinY[2])) {
		setPenguinID(2);
	}
	else {
		displayBoard(board);
		setColor(LIGHT_RED);
		printf("\nERROR: incorrect coordinate input, please, try again.\n");
		setColor(LIGHT_GRAY);
		choosePenguin(board);

	}
}



void makeAMove(struct Board* board) {
	//moves given player from its initial position to available place in the board

	struct Player* current = getCurrentPlayer();
	int ID = getPenguinID();

	int currentX = current->penguinX[ID] - 1;
	int currentY = letterToInt(current->penguinY[ID]) - 1;

	char** possibleMoves = getPossibleMoves(board);


	int X;
	int Y;
	char buffer;
	do {
		printf("\nInput number of the row to move (ex. 1): ");
		X = fixscanf();
		X--;
		printf("Input number of the column to move (ex. A): ");
		scanf(" %c", &buffer);
		Y = letterToInt(buffer) - 1;

		if (X >= board->size || X < 0 || Y < 0 || Y >= board->size) {
			displayBoard(board);
			setColor(LIGHT_RED);
			printf("\nERROR: incorrect coordinate input, please, try again.\n");
			setColor(LIGHT_GRAY);

		}

		if (board->grid[X][Y] != possibleMoves[X][Y] || board->grid[X][Y] == 'P') {
			displayBoard(board);
			setColor(LIGHT_RED);
			printf("\nERROR: it is impossbile to move there.\n");
			setColor(LIGHT_GRAY);

		}
	} while (board->grid[X][Y] != possibleMoves[X][Y]);
	board->grid[currentX][currentY] = 'X';


	board->grid[X][Y] = 'P';

	current->penguinX[ID] = X + 1;
	current->penguinY[ID] = (char)('A' + Y);

};





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

