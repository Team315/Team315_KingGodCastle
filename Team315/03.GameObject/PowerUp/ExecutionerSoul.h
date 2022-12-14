#pragma once
#include "PowerUp.h"

class ExecutionerSoul : public PowerUp
{
protected:
	int grade;
	PowerUpTypes powerUpType;

public:
	ExecutionerSoul(int grade = 0, PowerUpTypes puType = PowerUpTypes::None);
	virtual ~ExecutionerSoul();
};