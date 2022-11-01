#include "Player.h"
using namespace std;

void Player::strike(int x, int y) {
	char *cell = field.getCell(x, y);
	if (*cell == EMPTY_CHAR) *cell = MISS_SHIP_CHAR;
	else *cell = HIT_SHIP_CHAR;
}

/*
	function return -1 if input is incorrect
	function return -2 if function can't add a ship because of incorrect start point
*/
int Player::addShip(int shipSize, std::string startPoint, std::string direction) {

	Utils utils;

	if (direction.length() != 1) return -1;
	try {
		int t = stoi(direction); // try to convert str to int
	}
	catch (exception a) {
		return -1;
	}

	startPoint = utils.coordsFromInput(startPoint);
	if (startPoint == "-1") return -1;

	/*
		0 - left
		1 - up
		2 - right
		3 - down
	*/
	int directionVector[2];

	switch (direction[0] - '0' - 1) {
	case 0:
		directionVector[0] = -1;
		directionVector[1] = 0;
		break;
	case 1:
		directionVector[0] = 0;
		directionVector[1] = -1;
		break;
	case 2:
		directionVector[0] = 1;
		directionVector[1] = 0;
		break;
	case 3:
		directionVector[0] = 0;
		directionVector[1] = 1;
		break;
	default:
		return -1;
	}

	int xStartPoint = startPoint[0] - 'A';
	int yStartPoint = startPoint[1] - '0';

	for (int i = 0; i < shipSize; ++i) {
		int xCoord = xStartPoint + directionVector[0] * (i);
		int yCoord = yStartPoint + directionVector[1] * (i);

		if (xCoord < 0 || xCoord > 9 || yCoord < 0 || yCoord > 9)
			return -2;


		// reuse this algorithm to create a grey zon
		int k = (yCoord - 1 < 0) ? 0 : yCoord - 1;
		while (k <= yCoord + 1) {

			int j = (xCoord - 1 < 0) ? 0 : xCoord - 1;

			while (j <= xCoord + 1) {
				if (*field.getCell(j, k) == SHIP_CHAR) {
					return -2;
				}
				j++;
			}
			k++;
		}

		*field.getCell(xCoord, yCoord) = TEMP_SHIP_CHAR;
	}

	return 0;
}

void Player::printField() {
	cout << "   ";
	for (int i = 0; i < H_SIZE; ++i) {
		cout << char('A' + i) << " ";
	}
	cout << "\n";
	for (int i = 0; i < V_SIZE; ++i) {
		cout << (i == 9 ? "" : " ") << (i + 1) << " ";
		for (int j = 0; j < H_SIZE; ++j) {
			cout << *field.getCell(j, i) << " ";
		}
		cout << "\n";
	}
}

void Player::replaceTempChars(bool shipWasCreated) {
	for (int i = 0; i < V_SIZE; ++i) {
		for (int j = 0; j < H_SIZE; ++j) {
			char* cell = field.getCell(j, i);
			if (*cell == TEMP_SHIP_CHAR) {
				*cell = shipWasCreated ? SHIP_CHAR : EMPTY_CHAR;
			}
		}
	}
}