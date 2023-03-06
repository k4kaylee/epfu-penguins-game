#include <stdio.h>
#include <ctype.h>
#include "board.h"
#include "penguinID.h"
#include "system.h"
#include "player.h"
#include "textColor.h"



void choosePenguin(struct Board* board, struct Player* player) { //Michal's function

	int ID = 0;
	int xpen;
	char ypen;

	printf("\n%s's move\n", player->name);
	printf("choose penguin you want to move\n");
	printf("\nInput number of the row (for example, 1): ");
	scanf("%d", &xpen);
	printf("Input number of the row (for example, A): ");
	scanf(" %c", &ypen);

	if ((xpen == player->penguinX[0]) && (ypen == player->penguinY[0])) {
		ID = 0;
	}
	else if ((xpen == player->penguinX[1]) && (ypen == player->penguinY[1])) {
		ID = 1;
	}
	else if ((xpen == player->penguinX[2]) && (ypen == player->penguinY[2])) {
		ID = 2;
	}

	else {
		displayBoard(board);
		setColor(LIGHT_RED);
		printf("\nERROR: incorrect coordinate input, please, try again.\n");
		setColor(LIGHT_GRAY);
		choosePenguin(board, player);

	}
	setPenguinID(ID);
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
		scanf("%d", &X);
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


	printf("%d\n", current->points);
	getChar();
	current->points += board->grid[X][Y] - '0';
	printf("%d\n", current->points);
	getChar();
	board->grid[currentX][currentY] = 'X';


	board->grid[X][Y] = 'P';

	current->penguinX[ID] = X + 1;
	current->penguinY[ID] = (char)(Y + 1);

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

