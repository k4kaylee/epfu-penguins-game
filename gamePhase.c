#define PLACEMENT 0
#define CHOOSING_PENGUIN 1
#define MOVEMENT 2
#define END_OF_GAME 3

int gamePhase;

void setGamePhase(int phase) {
	gamePhase = phase;
};

int getGamePhase() {
	return gamePhase;

}