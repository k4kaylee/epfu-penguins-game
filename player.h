#pragma once
#include "board.h"
struct Player { 
	char* name;
	int id;
	int points;
	int penguinX[3];
	char penguinY[3];
	int color;
	int fileID;
};

extern struct Player* players;
int amountOfPlayers;
int amountOfPenguins;

extern struct Player* currentPlayer; //used in movement
struct Player* getCurrentPlayer(void); //getting current player
void setCurrentPlayer(struct Player* player); //setting current player

struct Player* getPlayer(int playerID);
struct Player* getAllPlayers(void); //gets players array
void setAmountOfPlayers(void); //getting amount of players (1 < amount < 5)
void setAmountOfPenguins(void); //function for getting ammount of penguins per player
void displayPlayerBoard(void); //displays all players with their names, IDs and points
void checkPlayerData(void); //allows to change players name by ID if there is a mistake
char** getPossibleMoves(struct Board* board); //analyses all possible moves for a given player and returns the array that contains them
void displayPoints(void);
void getPlayerFile(int amountOfFiles);