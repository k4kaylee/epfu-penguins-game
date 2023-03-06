struct Player {
	char* name;
	int id;
	int points;
	int penguinX;
	char penguinY;
};

extern struct Player* currentPlayer;
struct Player* getCurrentPlayer();
void setCurrentPlayer(struct Player* player);

int getAmountOfPlayers();
struct Player* getAllPlayers();
void displayPlayerBoard();
struct Player* getPlayer();
void checkPlayerData();