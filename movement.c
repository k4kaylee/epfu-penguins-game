#include "player.h"
#include "textColor.h"


int checkMove() {
	//checks whether move was done correctly
	//returns '1' when all conditions are met, otherwisw returns '0'
	//CONDITIONS:
	//	!there is no '0' cell in the way of movement direction
	//	!the route to a given coordinate is a straight line
	//  !*there is no penguins on the way
	return 0;
}

void makeAMove(/*struct Player player, char** board, int size*/) {
	//moves given player from its initial position to available place in the board
	while (checkMove()) {
		//As far as move is compulsory, we ask the player for correct coordinates
	}
};