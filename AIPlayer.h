#include "AbstractPlayer.h"

class AI : public AbstractPlayer {
protected:
	virtual int* getDirectionVector(int);
public:
	virtual int drawStars(const Ship& ship);
	virtual int addShip(int, std::string, std::string);
	virtual bool strike(int x, int y);
	virtual void printField(bool);
	virtual void replaceTempChars(bool);
	virtual int getShipsRemain();
};