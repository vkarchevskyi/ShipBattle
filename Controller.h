#include "Player.h"

class Controller {
private:
	AbstractPlayer *currentPlayer;
	AbstractPlayer *currentEnemy;
	AbstractPlayer *player1;
	AbstractPlayer *player2;
	Utils utils;
	void getInput(const int, std::string);
	void init();
	void changePlayer();
	void pressAnyKey();
public:
	Controller();
	void startGame();
	void createField();
};