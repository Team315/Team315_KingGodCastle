#pragma once
#include "PowerUp.h"

class Warriors_heart : public PowerUp
{
protected:
	int grade;
	PowerUpTypes powerUpType;

public:
	Warriors_heart(int grade = 0, PowerUpTypes puType = PowerUpTypes::None);
	virtual ~Warriors_heart();
};