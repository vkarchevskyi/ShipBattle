#include "AbstractPlayer.h"

class Player : public AbstractPlayer {
private:
	Utils utils;
public:
	Player();
	std::string getHitPoint() override;
};