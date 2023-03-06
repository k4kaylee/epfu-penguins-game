#pragma once
struct Player;
#include "player.h"

struct Penguin {
	int coordinateX;
	char coordinateY;
};

int penguinID;
int amountOfPenguins;

int getPenguinID();
void setPenguinID(int ID);
void deletePenguin(struct Player* player);
