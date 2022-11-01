#include "Field.h"
#include "Utils.h"

class Player {
private:
	Field field;
	Field fogWarField;
public:
	int addShip(int, std::string, std::string);
	void strike(int x, int y);
	void printField();
	void replaceTempChars(bool);
};