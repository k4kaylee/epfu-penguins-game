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




void placeFish(int size, char** board, int amount) {
	int ones = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[i][j] = (rand() % 4) + '0';
			if (board[i][j] == '1') {
				ones = ones + 1;
			}
		}
	}
	
	if (ones < amount) {
		placeFish(size, board, amount);
	}
	displayBoard(size, board);
	
}

