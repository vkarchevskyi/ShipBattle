#include <iostream>
#include "Controller.h"
#include "Utils.h"

#define LINKOR_AMOUNT 1
#define CRUISERS_AMOUNT 2
#define DESTROYERS_AMOUNT 3
#define BOATS_AMOUNT 4

using namespace std;

void Controller::init() {
	cout << "\nPLAYER 1: \n\n";
	currentPlayer = &player1;
	createField();
	currentPlayer->printField();
	cout << "\n\nPLAYER 2: \n\n";
	currentPlayer = &player2;
	createField();
	currentPlayer->printField();
}

void Controller::getInput(const int amount, std::string shipType) {
	for (int i = 0; i < amount; i++) {
		std::string startPoint;
		std::string direction;

		currentPlayer->printField();
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
}

void Controller::createField() {
	getInput(LINKOR_AMOUNT, "linkor");
	getInput(CRUISERS_AMOUNT, "cruiser");
	getInput(DESTROYERS_AMOUNT, "destroyer");
	getInput(BOATS_AMOUNT, "boat");
}

void Controller::startGame() {
	init();

	Utils utils;

	do {
		std::string hitPoint;
		currentPlayer = &player1;
		cout << "Player 1 move\n";
		cout << "Enter the enemy's ship point (example: B7): ";
		cin >> hitPoint;
		std::string coords = utils.coordsFromInput(hitPoint);
		currentPlayer->strike(coords[0] - 'A', coords[1] - '0');
		//currentPlayer = &player2;
		currentPlayer->printField();
	} while (true);
}