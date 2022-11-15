#include "Player.h"
using namespace std;

Player::Player() {
	this->isAI = false;
}

string Player::getHitPoint() {
	string hitPoint;
	do {
		cout << "Enter the enemy's ship point (example: B7):";
		std::string coords;
		cin >> coords;
		hitPoint = Utils::coordsFromInput(coords);
		if (hitPoint == "-1") {
			cout << "\n\nINCORRECT INPUT!\n\n";
		}
		else {
			return hitPoint;
		}
	} while (true);
}