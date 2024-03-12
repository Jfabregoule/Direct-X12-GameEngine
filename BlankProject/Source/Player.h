#pragma once 
#include "Ship.h"

class Player : public Ship {
private:

	int m_score;

public:

	Player();
	~Player();

};