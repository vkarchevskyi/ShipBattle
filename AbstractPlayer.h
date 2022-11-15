#pragma once

#include <conio.h>
#include "Field.h"
#include "Utils.h"

class AbstractPlayer {
protected:
	bool isAI = false;
	int shipsRemain = 0;
	Field field;
	Field fogWarField;
	int* getDirectionVector(int);
public:
	virtual std::string getHitPoint() = 0;

	int drawStars(const Ship& ship);
	int addShip(int, std::string, std::string);
	bool strike(int, int);
	void printField(bool);
	void replaceTempChars(bool);
	int getShipsRemain();
	bool getIsAI() { return this->isAI; }
};