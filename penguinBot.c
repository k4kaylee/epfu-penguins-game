#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "system.h"
#include "player.h"

int runPenguinBot(int argumentAmount, char** arguments) {
	printf("Penguin bot is working\nArguments:\n");
	for (int i = 1; i < argumentAmount; i++)
		printf("%d: %s\n", i, arguments[i]);
	//char* phase = malloc(sizeof(arguments[1]));
	if (argumentAmount == 2) {
		printf("ERROR: invalid amount of arguments.");
		getChar();
		return 1;
	}

	char* phase = arguments[1];

	if (strcmp(phase, "placement") == 0) {
		if (argumentAmount < 5) {
			printf("ERROR: invalid amount of arguments. Program expects 5 arguments for placement mode.");
			getChar();
			return 1;
		}
	}
	else if (strcmp(phase, "movement") == 0) {
		if (argumentAmount < 4) {
			printf("ERROR: invalid amount of arguments. Program expects 4 arguments for movement mode.");
			getChar();
			return 1;
		}
	}
	else {
		printf("ERROR: invalid phase value '%s'. Consider either 'placement' or 'movement'.", arguments[1]);
		getChar();
		return 1;
	}


	amountOfPenguins = atoi(arguments[2]);
	FILE* boardFile = fopen(arguments[3], "r");
	if (!boardFile) {
		printf("ERROR: failed opening '%s' file.", arguments[3]);
		getChar();
		return 1;
	}
	
	int boardWidth;
	int boardHeight;
	fscanf(boardFile, "%d", &boardHeight);
	printf("\n%d", boardHeight);
	fscanf(boardFile, "%d", &boardWidth);
	printf("\n%d\n", boardWidth);

	int** board = 0;
	board = malloc(sizeof(*board) * boardHeight);
	for (int i = 0; i < boardHeight; i++)
		board[i] = malloc(sizeof(**board) * boardWidth);
	
	int scanBuf;
	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++) { 
			fscanf(boardFile, "%d", &scanBuf);
			board[i][j] = scanBuf;
		}
	}

	for (int i = 0; i < boardHeight; i++) {
		printf("%d%s", i + 1, (i < 9) ? "  " : " ");
		for (int j = 0; j < boardWidth; j++) {
			printf("%d%s %s", board[i][j], (board[i][j] == 0) ? "0" : "", (j == boardWidth - 1) ? "\n" : "");
		}
	}
	
	if (amountOfPenguins <= 0) {
		printf("ERROR: invalid amount of penguins. It should be greater than 0.");
		getChar();
		return 1;
	}


	if (strcmp(phase, "placement") == 0){
		printf("\nPlacement");
	}
	else if (strcmp(phase, "movement") == 0) {
		printf("\nMovement");
	}


	getChar();
	return 0;
}