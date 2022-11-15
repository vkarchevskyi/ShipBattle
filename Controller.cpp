#include <iostream>
#include "Controller.h"
#include "Utils.h"

#define LINKOR_AMOUNT 1
#define CRUISERS_AMOUNT 2
#define DESTROYERS_AMOUNT 3
#define BOATS_AMOUNT 4

using namespace std;

Controller::Controller(bool firstPlayerAI, bool secondPlayerAI) {
	if (firstPlayerAI) {
		this->player1 = new AIPlayer();
	}
	else {
		this->player1 = new Player();
	}
	
	if (secondPlayerAI) {
		this->player2 = new AIPlayer();
	}
	else {
		this->player2 = new Player();
	}

	this->currentPlayer = player1;
	this->currentEnemy = player2;
}

void Controller::pressAnyKey() {
	cout << "\nPress any key to continue\n";
	_getch();
	system("cls");
}

void Controller::init() {
	cout << "PLAYER 1: \n\n";
	createField();
	currentPlayer->printField(false);
	pressAnyKey();

	changePlayer();

	if (!currentPlayer->getIsAI()) {
		cout << "PLAYER 2: \n\n";
	}
	createField();
	if (!currentPlayer->getIsAI()) {
		currentPlayer->printField(false);
		pressAnyKey();
	}
	changePlayer();
	
}

void Controller::getInput(const int amount, std::string shipType) {

	if (!currentPlayer->getIsAI()) {
		string shipCoords[] = { "A1", "C1", "E1" };
		string directions[] = { "4", "4", "4" };
		currentPlayer->addShip(4, shipCoords[0], directions[0]);
		currentPlayer->addShip(3, shipCoords[1], directions[1]);
		currentPlayer->addShip(3, shipCoords[2], directions[2]);
		currentPlayer->replaceTempChars(true);
	}
	else {
		int i = 0;
		while (i < amount) {
			std::string startPoint;
			std::string direction = "";

			if (!currentPlayer->getIsAI()) {
				currentPlayer->printField(false);
				cout << "Enter the " << shipType << " start point (example: B7): ";
				cin >> startPoint;
				if (amount != BOATS_AMOUNT) {
					cout << "Enter the direction of " << shipType << ": \n";
					cout << "(1 - left, 2 - up, 3 - right, 4 - down)\n";
					cin >> direction;
				}
				else {
					direction = "1";
					// any possible direction, because the direction doesn't matter to boats
				}
			}
			else {
				startPoint = Utils::getRandomPoint();
				direction += ((rand() % 4) + '1');
			}
			

			int returnValue = currentPlayer->addShip(4 + 1 - amount, startPoint, direction);
			if (returnValue) {
				if (!currentPlayer->getIsAI())
					cout << "\nINCORRECT INPUT!\n\n";

				currentPlayer->replaceTempChars(false);
			}
			else {
				i++;
				currentPlayer->replaceTempChars(true);
			}
		}
	}
}

void Controller::changePlayer() {
	if (currentPlayer == player1) {
		currentPlayer = player2;
		currentEnemy = player1;
	}
	else {
		currentPlayer = player1;
		currentEnemy = player2;
	}
}

void Controller::createField() {
	getInput(LINKOR_AMOUNT, "linkor");
	getInput(CRUISERS_AMOUNT, "cruiser");
	getInput(DESTROYERS_AMOUNT, "destroyer");
	getInput(BOATS_AMOUNT, "boat");
}

void Controller::startGame() {
	srand(time(0));
	init();
	
	int currentPlayerNum = 1;
	int shipsBeforeStrike;
	do {
		system("cls");
		
		cout << "Player " << currentPlayerNum << " move\n\n";
		currentEnemy->printField(true);
		std::string hitPoint = currentPlayer->getHitPoint();

		shipsBeforeStrike = currentEnemy->getShipsRemain();
		bool hit = currentEnemy->strike(hitPoint[0] - 'A', hitPoint[1] - '0');
		currentEnemy->printField(true);
		
		if (hit) {

			if (currentEnemy->getShipsRemain() == 0) {
				cout << "\nPlayer " << currentPlayerNum << " wins\n\n";
				return;
			}
			
			if (currentEnemy->getIsAI()) {
				//AIPlayer* enemy = (AIPlayer*)&currentEnemy;
				//if (enemy->isAllDirectionZeros()) {
				//	enemy->setLastHitPoint(hitPoint);
				//}
				//if (enemy->getIsAI() && shipsBeforeStrike != enemy->getShipsRemain()) {
				//	enemy->zeroingDirections();
				//}
			}
			
			continue;
		}
		
		pressAnyKey();
		currentPlayerNum == 1 ? ++currentPlayerNum : --currentPlayerNum;
		changePlayer();
	} while (true);
}
