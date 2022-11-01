#include "Player.h"

class Controller {
private:
	Player *currentPlayer;
	Player player1;
	Player player2;
	void getInput(const int, std::string);
	void init();
public:
	void startGame();
	void createField();
};