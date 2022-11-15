#include "Player.h"
#include "AIPlayer.h"

class Controller {
private:
	AbstractPlayer *currentPlayer;
	AbstractPlayer *currentEnemy;
	AbstractPlayer *player1;
	AbstractPlayer *player2;
	void getInput(const int, std::string);
	void init();
	void changePlayer();
	void pressAnyKey();
public:
	Controller(bool, bool);
	void startGame();
	void createField();
};