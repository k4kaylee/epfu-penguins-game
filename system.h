#include "player.h"
#ifdef _WIN32
#define NULL_FILE "NUL"
#else
#define NULL_FILE "/dev/null"
#endif

void clear(void); //clear console in any system
void getChar(void); //get symbol in any system
FILE* createlog(void); //initialise log file
void logBoard(struct Board* board, FILE* log); //print board in log file
void logPoints(FILE* log); //print scoreboard in log
void clearLogDir(void); //deletes the oldest file in 'gamelogs' directory if the amount of log files is >5
char* getCWD(char* buf, int byteSize); //gets current file directory and puts it in 'buf'
int letterToInt(char coordinate);//custom function used to translate coordinates on x-axis from symbols to numbers