#pragma once

#include <iostream>
#include <string>

class Utils {
public:
	static std::string coordsFromInput(std::string);
	static std::string getRandomPoint();
	static void clearInputBuffer();
};