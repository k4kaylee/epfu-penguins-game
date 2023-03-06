#pragma once
#include "board.h"
struct Player { 
	char* name;
	int id;
	int points;
	int penguinX[3];
	char penguinY[3];
	//int color;
	int fileID;
};

extern struct Player* currentPlayer; //used in movement
struct Player* getCurrentPlayer(void); //getting current player
void setCurrentPlayer(struct Player* player); //setting current player

struct Player* getAllPlayers(int amount, struct Player* players); //gets players array
int getAmountOfPlayers(void); //getting amount of players (1 < amount < 5)
int getAmountOfPenguins(void); //function for getting ammount of penguins per player
void displayPlayerBoard(int amount, struct Player* players); //displays all players with their names, IDs and points
struct Player* getPlayer(struct Player* players, int i); //gets player from 'players' by a given ID
void checkPlayerData(int amount, struct Player* players); //allows to change players name by ID if there is a mistake
char** getPossibleMoves(struct Board* board); //analyses all possible moves for a given player and returns the array that contains them
void displayPoints(struct Player* players, int amount);
void getPlayerFile(int amountOfFiles);