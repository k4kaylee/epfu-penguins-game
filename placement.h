#include "player.h"
void placeFish(struct Board* board, int amount); // randomly fills board with fish from 1 to 3 or adds empty 'X' spaces. If tha amount of cells with 1 fish is less than amount of players, it refills the board again
void placePenguin(struct Board* board, struct Player* player); // places players penguin as 'P' to a given coordinate if the conditions are met
