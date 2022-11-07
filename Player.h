#include <conio.h>
#include "Field.h"
#include "Utils.h"

class Player {
private:
	int shipsRemain = 0;
	Field field;
	Field fogWarField;
	int* getDirectionVector(int);
public:
	int drawStars(const Ship& ship);
	int addShip(int, std::string, std::string);
	bool strike(int x, int y);
	void printField(bool);
	void replaceTempChars(bool);
	int getShipsRemain();
};