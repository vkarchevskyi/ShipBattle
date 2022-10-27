#include <iostream>
#include "Controller.h"

using namespace std;

void Controller::startGame() {

	cout << field.addShip(1, "B10", 2) << std::endl;
	field.printField();

	system("pause");
}