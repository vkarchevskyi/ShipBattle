#include "Utils.h"

std::string Utils::coordsFromInput(std::string strCoords) {
	if (strCoords.length() < 2 || strCoords.length() > 3 ||
		strCoords[0] < 'A' || strCoords[0] > 'J' ||
		strCoords[1] < '0' || strCoords[1] > '9'
		) {
		return "-1";
	}

	if (strCoords.length() == 3) {
		if (strCoords[1] == '1' && strCoords[2] == '0') {
			strCoords = strCoords[0];
			strCoords += "9"; // turn 10 into 9, because arrays start with 0
		}
		else {
			return "-1";
		}
	}
	else {
		--strCoords[1]; // arrays start with 0
	}

	return strCoords;
}

std::string Utils::getRandomPoint() {
	char line = rand() % 10 + '0';
	char column = rand() % 10 + 'A';
	return std::string() + column + line;
}

void Utils::clearInputBuffer() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}