struct Player {
	char* name;
	int id;
	int points;
	int penguinX;
	char penguinY;
};
int getAmountOfPlayers();
struct Player* getAllPlayers();
void displayPlayerBoard();
struct Player getPlayer();
void checkPlayerData();