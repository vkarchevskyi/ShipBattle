#include <iostream>
#include "Controller.h"
#include "Utils.h"

#define LINKOR_AMOUNT 1
#define CRUISERS_AMOUNT 2
#define DESTROYERS_AMOUNT 3
#define BOATS_AMOUNT 4

//#define DEBUG 0

using namespace std;

void Controller::pressAnyKey() {
	cout << "\nPress any key to continue\n";
	_getch();
	system("cls");
}

void Controller::init() {
	cout << "PLAYER 1: \n\n";
	changePlayer(); // test
	createField();
	currentPlayer->printField(false);
	pressAnyKey();

	cout << "PLAYER 2: \n\n";
	changePlayer(); // test
	createField();
	currentPlayer->printField(false);
	changePlayer(); // test
	pressAnyKey();
}

#ifdef DEBUG
string shipCoords[] = { "A1", "C1", "E1" };
string directions[] = { "4", "4", "4" };
#endif
void Controller::getInput(const int amount, std::string shipType) {
#ifdef DEBUG
	currentPlayer->addShip(4 + 1 - amount, shipCoords[0], directions[0]);
	currentPlayer->addShip(4 + 1 - amount, shipCoords[1], directions[1]);
	currentPlayer->addShip(4 + 1 - amount, shipCoords[2], directions[2]);
	currentPlayer->replaceTempChars(true);
#endif
#ifndef DEBUG// DEBUG
	for (int i = 0; i < amount; i++) {
		std::string startPoint;
		std::string direction;

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

		int returnValue = currentPlayer->addShip(4 + 1 - amount, startPoint, direction);
		if (returnValue) {
			--i;
			cout << "\nINCORRECT INPUT!\n\n";

			currentPlayer->replaceTempChars(false);
		}
		else {
			currentPlayer->replaceTempChars(true);
		}
	}
#endif
}

void Controller::changePlayer() {
	if (currentPlayer == &player1) {
		currentPlayer = &player2;
		currentEnemy = &player1;
	}
	else {
		currentPlayer = &player1;
		currentEnemy = &player2;
	}
}

void Controller::createField() {
	getInput(LINKOR_AMOUNT, "linkor");
	getInput(CRUISERS_AMOUNT, "cruiser");
	getInput(DESTROYERS_AMOUNT, "destroyer");
	getInput(BOATS_AMOUNT, "boat");
}

void Controller::startGame() {
	init();
	
	int currentPlayerNum = 1;
	do {
		system("cls");
		cout << "Player " << currentPlayerNum << " move\n\n";
		currentEnemy->printField(true);
		cout << "Enter the enemy's ship point (example: B7):";
		std::string hitPoint;
		cin >> hitPoint;
		std::string coords = utils.coordsFromInput(hitPoint);
		if (coords == "-1") {
			cout << "\n\nINCORRECT INPUT!\n\n";
			continue;
		}

		bool hit = currentEnemy->strike(coords[0] - 'A', coords[1] - '0');
		currentEnemy->printField(true);
		
		if (hit) {
			if (currentEnemy->getShipsRemain() == 0) {
				cout << "\nPlayer " << currentPlayerNum << " wins\n\n";
				return;
			}
			continue;
		}

		
		pressAnyKey();
		currentPlayerNum == 1 ? ++currentPlayerNum : --currentPlayerNum;
		changePlayer();
	} while (true);
}
