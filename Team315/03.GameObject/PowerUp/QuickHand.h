#pragma once
#include "PowerUp.h"

class QuickHand : public PowerUp
{
protected:
	int grade;
	PowerUpTypes powerUpType;

public:
	QuickHand(int grade = 0, PowerUpTypes puType = PowerUpTypes::None);
	virtual ~QuickHand();
};