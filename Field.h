#include <string>

#define H_SIZE 10 // horizontal size
#define V_SIZE 10 // vertical size

#define EMPTY_S ' ' // empty symbol
#define SHIP_S 'S' // ship symbol
#define HIT_SHIP_S 'X' // hitted ship symbol
#define MISS_SHIP_S '*' // missed ship symbol

#define LINKOR_SIZE 4
#define CRUISER_SIZE 3
#define DESTROYER_SIZE 2
#define BOAT_SIZE 1

#define TEMP_HIT_S 'T'

class Field {
private:
	char field[H_SIZE][V_SIZE];
public:
	Field();
	void clearField();
	void printField();
	void strike(int x, int y);
	int addShip(int, std::string, int);
	char getCell(int x, int y);
};