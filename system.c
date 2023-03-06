#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#ifdef _WIN32
	#include <conio.h>
	#include <direct.h>
	#include "dirent.h"
#else
	#include <dirent.h>
	#include <unistd.h>
	#include <errno.h>
#endif
#include "player.h"
#include "system.h"
#include "board.h"
#include "textColor.h"


//Roma's intersystem adaptation
void clear() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void getChar() {
#ifdef _WIN32
	_getch();
#else
	getchar();
#endif
}

char* getCWD(char* buf, int bufsize) {
#ifdef _WIN32
	return _getcwd(buf, bufsize);
#else
	return getcwd(buf, bufsize);
#endif
}


int letterToInt(char coordinate) {
	return coordinate - 'A' + 1;
}

void clearLogDir() {//Roma's function
	int amountOfFiles = 0;
	DIR* directory;
	struct dirent* dir;
	directory = opendir("gamelogs");
	dir = 0;
	if (directory)
	{
		while ((dir = readdir(directory)) != NULL)
		{
			if (strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..")) {
				amountOfFiles++;
			}
		}
	}
	else {
		return;
	}
	rewinddir(directory);
	char buf[BUFSIZ];
	while (amountOfFiles > 5) {
		dir = readdir(directory);
		if (strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..")) {
			snprintf(buf, sizeof(buf), "gamelogs/%s", dir->d_name);
			remove(buf);
			amountOfFiles--;
		}
	}
	closedir(directory);
}

FILE* createlog() { //Roma's function
	FILE* log = NULL;
	char buf[BUFSIZ];
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	DIR* gamelogs = opendir("gamelogs");
	if (gamelogs) {
		/* Directory exists. */
		closedir(gamelogs);
	}
	else if (ENOENT == errno) {
		/* Directory does not exist. */
		system("mkdir gamelogs");
	}

	sprintf(buf, "gamelogs/%d-%02d-%02d %02d-%02d-%02d.txt", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	log = fopen(buf, "w");
	if (log == NULL)
	{
		/* File not created hence exit */
		printf("Unable to create log file. Press any key to continue.\n");
		getChar();
		return fopen(NULL_FILE, "w");
	}

	fprintf(log, "'Hey! That's my fish' log #X\n");
	return log;
}

void logBoard(struct Board* board, FILE* log) { //Roma's function
	fprintf(log, "\n");
	char symbol = 'A';
	for (int i = 0; i < board->size; i++)
		fprintf(log, " %s%c%s", (i == 0) ? "  " : "", symbol + i, (i == board->size - 1) ? "\n\n" : "");

	for (int i = 0; i < board->size; i++) {
		for (int j = 0; j < board->size; j++) {
			if (j == 0)
				fprintf(log, "%d%s", i + 1, (i < 9) ? " " : "");
			fprintf(log, " %c", board->grid[i][j]);
		}
		fprintf(log, "\n");
	}
	fprintf(log, "\n\n");
}

void logPoints(FILE* log) { //Roma's function
	fprintf(log, "SCORE:");
	struct Player* current;
	int max = 0;
	for (int i = 0; i < amountOfPlayers; i++) {
		setCurrentPlayer(getPlayer(i));
		current = getCurrentPlayer();
		if (current->points > max)
			max = current->points;
	}

	for (int i = 0; i < amountOfPlayers; i++) {
		setCurrentPlayer(getPlayer(i));
		current = getCurrentPlayer();
		fprintf(log, "\n%s: %d", current->name, current->points);
		if (current->points == max) {
			fprintf(log, " - WINNER!");

		}
	}
}

int fixscanf() { //Michal's function
	int variable;
	int readNr = 0;
	while (readNr != 1) {

		readNr = scanf("%d", &variable);
		if (readNr != 1) {
			setColor(LIGHT_RED);
			printf("ERROR: please input a number: \n");
			setColor(LIGHT_GRAY);
		}
		scanf("%*[^\n]");
	}
	return variable;
}