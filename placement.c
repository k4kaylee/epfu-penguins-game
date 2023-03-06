#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "gamemode.h"
#include "player.h"



void placePenguin(int size, char** board, struct Player player) {
	printf("\n%s's turn\n", player.name);
	printf("Choose your row (ex. 1): ");
	int coordinateX;
	scanf("%d", &coordinateX);
	char coordinateY;
	printf("Choose your column: (ex. A): ");
	scanf(" %c", &coordinateY);

	if (letterToInt(coordinateY, size) == 0 || coordinateX > size) {
		displayBoard(size, board);

		printf("\n%d\n%c\n", letterToInt(coordinateY, size), coordinateY);
		printf("Something went wrong, please, try again.\n");
		placePenguin(size, board, player);
	}
	board[coordinateX - 1][letterToInt(coordinateY, size) - 1] = 'P';
	displayBoard(size, board);
	printf("\n%c\n%d\n", coordinateY, letterToInt(coordinateY, size));
}




void placeFish(int size, char** board) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[i][j] = (rand() % 4) + '0';
		}
	}
	displayBoard(size, board);
}
