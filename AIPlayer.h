#include "AbstractPlayer.h"

using namespace std;

class AIPlayer : public AbstractPlayer {
private:
	string lastHitPoint;
	int hitDirection[4]{ 0, 0, 0, 0 };
public:
	AIPlayer();
	bool isAllDirectionZeros();
	void zeroingDirections();
	void setLastHitPoint(string);
	string getHitPoint() override;
};