int gamePhase = 0;
/*
	0 - placement
	1 - movement
	2 - end of game (displaying results)
*/
void setGamePhase(int phase) {
	gamePhase = phase;
};

int getGamePhase() {
	return gamePhase;
}