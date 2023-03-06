#include <stdio.h>
#include "board.h"
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

	Y = letterToInt(buffer) - 1;

	while (board[X][Y] != possibleMoves[X][Y]) {
		setColor(4);
		printf("\nERROR: it is impossbile to move there.\n");
		setColor(7);
		printf("Input number of the row to move (ex. 1): ");
		scanf("%d", &X);
		X--;
		printf("Input number of the column to move (ex. A): ");
		scanf(" %c", &buffer);
		Y = letterToInt(buffer) - 1;
	}

	current->points += board[X][Y] - '0';
	board[currentX][currentY] = 'X';

	if (currentX == X){
		if (Y > currentY) { // to the right
			for (int i = currentY + 1; i < Y; i++) {
				current->points += (board[X][i] - '0');
				board[X][i] = 'X';
			}
		}
		else if (Y < currentY) { // to the left
			for (int i = currentY - 1; i > Y; i--) {
				current->points += (board[X][i] - '0');
				board[X][i] = 'X';
			}
		}
	}
	else if (currentY == Y) { 
		if (X > currentX) {
			printf("X > currentX");
			for (int i = currentX + 1; i < X; i++) {
				current->points += (board[i][Y] - '0');
				board[i][Y] = 'X';
			}
		}
		if (X < currentX) {
			for (int i = currentX - 1; i > X; i--) {
				current->points += (board[i][Y] - '0');
				board[i][Y] = 'X';
			}
		}
	}
	
	board[X][Y] = 'P';
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

