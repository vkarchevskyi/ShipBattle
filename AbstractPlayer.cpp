#include "AbstractPlayer.h"

using namespace std;

int* AbstractPlayer::getDirectionVector(int direction) {
	int directionVector[2];
	switch (direction) {
	case LEFT:
		directionVector[0] = -1;
		directionVector[1] = 0;
		break;
	case UP:
		directionVector[0] = 0;
		directionVector[1] = -1;
		break;
	case RIGHT:
		directionVector[0] = 1;
		directionVector[1] = 0;
		break;
	case DOWN:
		directionVector[0] = 0;
		directionVector[1] = 1;
		break;
	default:
		directionVector[0] = 0;
		directionVector[1] = 0;
	}
	return directionVector;
}

int AbstractPlayer::drawStars(const Ship& ship) {
	const int* dirVector = this->getDirectionVector(ship.direction);

	for (int i = 0; i < ship.size; ++i) {
		int xCoord = ship.startX + dirVector[0] * i;
		int yCoord = ship.startY + dirVector[1] * i;

		if (xCoord < 0 || xCoord > 9 || yCoord < 0 || yCoord > 9)
			return -2;

		int k = (yCoord - 1 < 0) ? 0 : yCoord - 1;
		while (k <= yCoord + 1 && k < 10) {

			int j = (xCoord - 1 < 0) ? 0 : xCoord - 1;

			while (j <= xCoord + 1 && j < 10) {
				char* cell = this->field.getCell(j, k);
				if (*cell == EMPTY_CHAR) {
					*this->field.getCell(j, k) = MISS_SHIP_CHAR;
					*this->fogWarField.getCell(j, k) = MISS_SHIP_CHAR;
				}
				j++;
			}
			k++;
		}
	}
	return 0;
}

int AbstractPlayer::getShipsRemain() {
	return this->shipsRemain;
}

void AbstractPlayer::replaceTempChars(bool shipWasCreated) {
	for (int i = 0; i < V_SIZE; ++i) {
		for (int j = 0; j < H_SIZE; ++j) {
			char* cell = this->field.getCell(j, i);
			if (*cell == TEMP_SHIP_CHAR) {
				*cell = shipWasCreated ? SHIP_CHAR : EMPTY_CHAR;
			}
		}
	}
}

void AbstractPlayer::printField(bool isFog) {
	cout << "   ";
	for (int i = 0; i < H_SIZE; ++i) {
		cout << char('A' + i) << " ";
	}
	cout << "\n";
	for (int i = 0; i < V_SIZE; ++i) {
		cout << (i == 9 ? "" : " ") << (i + 1) << " ";
		for (int j = 0; j < H_SIZE; ++j) {
			if (isFog) {
				cout << *this->fogWarField.getCell(j, i) << " ";
			}
			else {
				cout << *this->field.getCell(j, i) << " ";
			}
		}
		cout << "\n";
	}
}

bool AbstractPlayer::strike(int x, int y) {
	char* cell = this->field.getCell(x, y);

	if (*cell == EMPTY_CHAR) {
		*cell = MISS_SHIP_CHAR;
		*fogWarField.getCell(x, y) = MISS_SHIP_CHAR;
		return false;
	}
	else if (*cell == SHIP_CHAR) {
		vector<Ship>* ships = this->field.getAllShips();
		const int shipsAmount = ships->size();
		bool isWorking = true;
		for (int j = 0; j < shipsAmount && isWorking; j++) {
			Ship& ship = ships->at(j);
			const int* dirVector = this->getDirectionVector(ship.direction);
			for (int i = 0; i < ship.size; ++i) {
				if (ship.startX + dirVector[0] * i == x && ship.startY + dirVector[1] * i == y) {
					ship.hittedTimes++;
					if (ship.hittedTimes == ship.size) {
						this->drawStars(ship);
						ships->erase(ships->begin() + j);
						shipsRemain--;
					}
					isWorking = false;
					break;
				}
			}
		}

		*cell = HIT_SHIP_CHAR;
		*this->fogWarField.getCell(x, y) = HIT_SHIP_CHAR;
		return true;
	}
	else {
		if (!this->isAI) {
			cout << "\nINCORRECT INPUT! PRESS ANY KEY TO TRY AGAIN\n";
			_getch();
		}
		return true;
	}
}

/*
	function return -1 if input is incorrect
	function return -2 if function can't add a ship because of incorrect start point
*/
int AbstractPlayer::addShip(int shipSize, std::string startPoint, std::string directionStr) {

	Utils utils;

	int direction;
	if (directionStr.length() != 1) return -1;
	try {
		direction = stoi(directionStr) - 1; // try to convert str to int
	}
	catch (exception a) {
		return -1;
	}

	startPoint = utils.coordsFromInput(startPoint);
	if (startPoint == "-1") return -1;

	int* directionVector = getDirectionVector(direction);
	if (directionVector[0] == NULL && directionVector[1] == NULL) return -1; // error


	int xStartPoint = startPoint[0] - 'A';
	int yStartPoint = startPoint[1] - '0';

	for (int i = 0; i < shipSize; ++i) {
		int xCoord = xStartPoint + directionVector[0] * i;
		int yCoord = yStartPoint + directionVector[1] * i;

		if (xCoord < 0 || xCoord > 9 || yCoord < 0 || yCoord > 9)
			return -2;

		int k = (yCoord - 1 < 0) ? 0 : yCoord - 1;
		const int maxY = (yCoord + 1) >= 9 ? 9 : (yCoord + 1);
		while (k <= maxY) {

			int j = (xCoord - 1 < 0) ? 0 : xCoord - 1;
			const int maxX = (xCoord + 1) >= 9 ? 9 : (xCoord + 1);
			while (j <= maxX) {
				if (*this->field.getCell(j, k) == SHIP_CHAR) {
					return -2;
				}
				j++;
			}
			k++;
		}

		*this->field.getCell(xCoord, yCoord) = TEMP_SHIP_CHAR;
	}

	Ship ship = {
		xStartPoint,
		yStartPoint,
		shipSize,
		(DIRECTIONS)direction
	};

	this->field.addShip(ship);
	this->shipsRemain++;

	return 0;
}