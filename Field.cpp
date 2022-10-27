#include "Field.h"
#include <iostream>

using namespace std;

Field::Field() {
	clearField();
}

void Field::clearField() {
	for (int i = 0; i < H_SIZE; ++i) {
		for (int j = 0; j < V_SIZE; ++j) {
			field[i][j] = EMPTY_S;
		}
	}
}

void Field::printField() {
	cout << "   ";
	for (int i = 0; i < H_SIZE; ++i) {
		cout << char('A' + i) << " ";
	}
	cout << "\n";
	for (int i = 0; i < H_SIZE; ++i) {
		cout << (i == 9 ? "" : " ") << (i + 1) << " ";
		for (int j = 0; j < V_SIZE; ++j) {
			cout << field[i][j] << " ";
		}
		cout << "\n";
	}
}

char Field::getCell(int x, int y) {
	return field[x][y];
}

void Field::strike(int x, int y) {
	char *cell = &field[x][y];
	if (*cell == EMPTY_S) *cell = MISS_SHIP_S;
	else *cell = HIT_SHIP_S;
}

/*
	function return -1 if input is incorrect
	function return -2 if function can't add a ship because of incorrect start point
*/

int Field::addShip(int type, std::string startPoint, int direction) {

	if (startPoint.length() < 2 || startPoint.length() > 3 ||
		startPoint[0] < 'A' || startPoint[0] > 'Z' ||
		startPoint[1] < '0' || startPoint[1] > '9'
		) {
		return -1;
	}

	if (startPoint.length() == 3) {
		if (startPoint[1] == '1' && startPoint[2] == '0') {
			startPoint = startPoint[0];
			startPoint += "9";
		}
		else {
			return -1;
		}
	}
	else {
		--startPoint[1];
	}

	/*
		0 - left
		1 - up
		2 - right
		3 - down
	*/
	int directionVector[2];
	
	switch (direction) {
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

	int shipSize = 4 - type;
	for (int i = 0; i < shipSize; ++i) {
		int xCoord = xStartPoint + directionVector[0] * (i + 1);
		int yCoord = yStartPoint + directionVector[1] * (i + 1);
		
		if (xCoord < 0 || xCoord > 9 || yCoord < 0 || yCoord > 9)
			return -2;

		field[yCoord][xCoord] = TEMP_HIT_S;
	}

	return 0;
}
