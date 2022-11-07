#include "Player.h"

class Controller {
private:
	Player *currentPlayer;
	Player *currentEnemy;
	Player player1;
	Player player2;
	Utils utils;
	void getInput(const int, std::string);
	void init();
	void changePlayer();
	void pressAnyKey();
public:
	void startGame();
	void createField();
};