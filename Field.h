#include <iostream>
#include <string>
#include <vector>

#define H_SIZE 10 // horizontal size
#define V_SIZE 10 // vertical size

#define EMPTY_CHAR ' ' // empty character
#define SHIP_CHAR 'S' // ship character
#define HIT_SHIP_CHAR 'X' // hitted ship character
#define MISS_SHIP_CHAR '*' // missed ship character

#define LINKOR_SIZE 4
#define CRUISER_SIZE 3
#define DESTROYER_SIZE 2
#define BOAT_SIZE 1

#define TEMP_SHIP_CHAR 'T'

#define PLAYER1 1
#define PLAYER2 2

using namespace std;

enum DIRECTIONS {
	LEFT,
	UP,
	RIGHT,
	DOWN,
};

struct Ship {
	int startX;
	int startY;
	int size;
	DIRECTIONS direction;
	int hittedTimes = 0;
};

class Field {
private:
	char field[V_SIZE][H_SIZE];
	void clearField();
	vector<Ship> ships;
public:
	Field();
	char* getCell(int, int);
	void addShip(Ship);
	vector<Ship>* getAllShips();
};