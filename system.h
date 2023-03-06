#include "player.h"

void clear(void); //clear console in any system
void getChar(void); //get symbol in any system
FILE* createlog(void); //initialise log file
void logBoard(int size, char** board, FILE* log); //print board in log file
void logPoints(struct Player* players, int amountOfPlayers, FILE* log); //print scoreboard in log
void clearLogDir(void);