#include <stdio.h>
#include <ctype.h>
#include "board.h"
#include "system.h"
#include "player.h"
#include "textColor.h"



void makeAMove(char** board, int size) {
	//moves given player from its initial position to available place in the board
	struct Player* current = getCurrentPlayer();

	printf("\n%s's move\n", current->name);
	int currentX = current->penguinX - 1;
	int currentY = letterToInt(current->penguinY) - 1;

	char** possibleMoves = getPossibleMoves(board, size);

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

	if (X >= size || X < 0 || Y < 0 || Y >= size) {
		displayBoard(size, board);
		setColor(LIGHT_RED);
		printf("\nERROR: incorrect coordinate input, please, try again.\n");
		setColor(LIGHT_GRAY);
		makeAMove(board, size);
		return;
	}
	
	while (board[X][Y] != possibleMoves[X][Y] || board[X][Y] == 'P') {
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

	current->points += board[X][Y] - '0';
	board[currentX][currentY] = 'X';
	board[X][Y] = 'P';
	
	Y += 'A' - 1;
	current->penguinX = X + 1;
	current->penguinY = (char)Y;
	displayBoard(size, board);
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

