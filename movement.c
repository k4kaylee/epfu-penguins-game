#include <stdio.h>
#include <ctype.h>
#include "board.h"
#include "system.h"
#include "player.h"
#include "textColor.h"



void makeAMove(struct Board* board) {
	//moves given player from its initial position to available place in the board
	struct Player* current = getCurrentPlayer();

	printf("\n%s's move\n", current->name);
	int currentX = current->penguinX - 1;
	int currentY = letterToInt(current->penguinY) - 1;

	char** possibleMoves = getPossibleMoves(board);

	int X;
	int Y;
	char buffer;


	printf("\nInput number of the row to move (ex. 1): ");
	scanf("%d", &X);
	X--;
	printf("Input number of the column to move (ex. A): ");
	scanf(" %c", &buffer);
	buffer = (char)toupper(buffer);
	Y = letterToInt(buffer) - 1;

	if (X >= board->size || X < 0 || Y < 0 || Y >= board->size) {
		displayBoard(board);
		setColor(LIGHT_RED);
		printf("\nERROR: incorrect coordinate input, please, try again.\n");
		setColor(LIGHT_GRAY);
		makeAMove(board);
		return;
	}
	
	while (board->grid[X][Y] != possibleMoves[X][Y] || board->grid[X][Y] == 'P') {
		setColor(LIGHT_RED);
		printf("\nERROR: it is impossbile to move there.\n");
		setColor(LIGHT_GRAY);
		printf("Input number of the row to move (ex. 1): ");
		scanf("%d", &X);
		X--;
		printf("Input number of the column to move (ex. A): ");
		scanf(" %c", &buffer);
		Y = letterToInt(buffer) - 1;
	}

	current->points += board->grid[X][Y] - '0';
	board->grid[currentX][currentY] = 'X';
	board->grid[X][Y] = 'P';
	
	Y += 'A' - 1;
	current->penguinX = X + 1;
	current->penguinY = (char)Y;
	displayBoard(board);
};



//In case we will have several penguins for 1 player

/*
void choose_penguin(int d, char ID, char board[][d], int* A, int* B)
{
  printf("\nEnter the cordinate of the penguin you want to move: ");
  do
  {
	scanf("%d %d", &A, &B);
	if (board[*A][*B] != ID)
	{
	  printf("\nThe coordinate you wany to move does not contain one of your penguins, try again.");
	}
  } while (board[*A][*B] != ID);
}
*/



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

