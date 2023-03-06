#include <stdlib.h>
#include <stdio.h>
#include "player.h"



int getSize() {
	system("cls");
	int size;
	printf("Input board size: ");
	scanf("%d", &size);
	while(size <= 3 || size > 21) {
		system("cls");
		printf("ERROR: board size is incorrect. Consider a number at least >3 and <21.\n");
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
	system("cls");
	char symbol = 'A';
	for (int i = 0; i < size; i++)
		printf(" %s%c%s", (i == 0) ? "  " : "", symbol + i, (i == size - 1) ? "\n" : "");
	printf("\n");


	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (j == 0)
				printf("%d%s", i + 1, (i < 9) ? " " : "");
			printf(" %c", board[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

int letterToInt(char coordinate, int size) {
	char symbol = 'A';
	for (int i = 1; i < size+1; i++) {
		if (symbol == coordinate)
			return i;
		symbol += 1;
	}
	return 0;
}