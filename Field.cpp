#include "Field.h"

using namespace std;

Field::Field() {
	clearField();
}

void Field::clearField() {
	for (int i = 0; i < H_SIZE; ++i) {
		for (int j = 0; j < V_SIZE; ++j) {
			field[i][j] = EMPTY_CHAR;
		}
	}
}

char* Field::getCell(int x, int y) {
	return &field[y][x];
}
