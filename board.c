#include <stdlib.h>
#include <stdio.h>
#include "player.h"
#include "textColor.h"
#include "gamePhase.h"
#include "system.h"



int getSize() {
	clear();
	int size;
	printf("Input board size: ");
	scanf("%d", &size);
	while(size <= 3 || size > 21) {
		clear();
		setColor(LIGHT_RED);
		printf("ERROR: board size is incorrect. Consider a number at least >3 and <21.\n");
		setColor(LIGHT_GRAY);
		printf("Input board size: ");
		scanf("%d", &size);
	}	
	return size;
}

char** getBoard(int size, char** board) {
	board = malloc(sizeof(*board) * size);
	for (int i = 0; i < size; i++)
		board[i] = malloc(sizeof(**board) * size);

	for (int i = 0; i < size; i++) {

		for (int j = 0; j < size; j++)
			board[i][j] = 'X';
	}
	return board;
}

void displayBoard(int size, char** board) {
	clear();
	char symbol = 'A';
	for (int i = 0; i < size; i++)
		printf(" %s%c%s", (i == 0) ? "  " : "", symbol + i, (i == size - 1) ? "\n" : "");
	printf("\n");

	int phase = getGamePhase();

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (j == 0)
				printf("%d%s", i + 1, (i < 9) ? " " : "");
			
			
			if (board[i][j] == '1' && !phase)
				setColor(LIGHT_GREEN);

			char** possibleMoves;
			if (phase == 1) {
				possibleMoves = getPossibleMoves(board, size);
				if (board[i][j] == possibleMoves[i][j])
					setColor(LIGHT_GREEN);
			}

			if (board[i][j] == 'P'){
				setColor(BLUE);
			}


			printf(" %c", board[i][j]);
			setColor(LIGHT_GRAY);
		}
		printf("\n");
	}
	printf("\n\n");
}
