#include <conio.h>
#include "Field.h"
#include "Utils.h"

class AbstractPlayer {
protected:
	int shipsRemain = 0;
	Field field;
	Field fogWarField;
	virtual int* getDirectionVector(int) = 0;
public:
	virtual int drawStars(const Ship& ship) = 0;
	virtual int addShip(int, std::string, std::string) = 0;
	virtual bool strike(int x, int y) = 0;
	virtual void printField(bool) = 0;
	virtual void replaceTempChars(bool) = 0;
	virtual int getShipsRemain() = 0;
};