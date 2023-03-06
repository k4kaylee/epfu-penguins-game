#include <stdlib.h>
#include <stdio.h>
#include "textColor.h"
#include "gamePhase.h"
#include "system.h"
#include "penguin.h"



int getSize() { //Roma's function
	clear();
	int size;
	printf("Input board size: ");
	size = fixscanf();
	while(size <= 3 || size > 21) {
		clear();
		setColor(LIGHT_RED);
		printf("ERROR: board size is incorrect. Consider a number at least >3 and <21.\n");
		setColor(LIGHT_GRAY);
		printf("Input board size: ");
		size = fixscanf();
	}	
	return size;
}

char** getBoard(int size) { //Roma's function
	char** board = malloc(sizeof(*board) * size);
	for (int i = 0; i < size; i++)
		board[i] = malloc(sizeof(**board) * size);
	return board;
}

void displayBoard(struct Board* board) { //Roma's function
	clear();
	char symbol = 'A';
	for (int i = 0; i < board->size; i++)
		printf(" %s%c%s", (i == 0) ? "  " : "", symbol + i, (i == board->size - 1) ? "\n" : "");
	printf("\n");

	int phase = getGamePhase();

	for (int i = 0; i < board->size; i++) {
		for (int j = 0; j < board->size; j++) {
			if (j == 0)
				printf("%d%s", i + 1, (i < 9) ? " " : "");
			
			
			if (board->grid[i][j] == '1' && phase == PLACEMENT)
				setColor(LIGHT_GREEN);

			struct Board possibleMoves;
			if (phase == MOVEMENT) {
				struct Player* current = getCurrentPlayer();
				possibleMoves = getPossibleMoves(board, current);
				if (board->grid[i][j] == possibleMoves.grid[i][j])
					setColor(LIGHT_GREEN);
			}

			//Colorising players penguins (Yuki Kawasaki)
			if (board->grid[i][j] == 'P') {
				for (int id = 0; id < amountOfPlayers; id++) {
					for (int pengID = 0; pengID < players[id].numberOfPenguins; pengID++) {
						if (players[id].penguins != NULL && (i + 1 == players[id].penguins[pengID].coordinateX && ('A' + j) == players[id].penguins[pengID].coordinateY)) {
							setColor(players[id].color);
							break;
						}
					}
				}
			}


			printf(" %c", board->grid[i][j]);
			setColor(LIGHT_GRAY);
		}
		printf("\n");
	}
	printf("\n\n");
}
