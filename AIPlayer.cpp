#include "AIPlayer.h"

using namespace std;

AIPlayer::AIPlayer() {
	this->isAI = true;
	this->lastHitPoint = "";
}

void AIPlayer::setLastHitPoint(string lastHitPoint) {
	this->lastHitPoint = lastHitPoint;
}

bool AIPlayer::isAllDirectionZeros() {
	return !hitDirection[0] && !hitDirection[1] && !hitDirection[2] && !hitDirection[3];
}

void AIPlayer::zeroingDirections() {
	for (int i = 0; i < 4; i++)
		hitDirection[i] = 0;
}

string AIPlayer::getHitPoint() {
	//if (this->isAllDirectionZeros()) {
	//	if ()
	//}
	//else {
	//	
	//}
	return Utils::getRandomPoint();
}