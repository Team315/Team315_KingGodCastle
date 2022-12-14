#pragma once
#include "PowerUp.h"

class Dogfight : public PowerUp
{
protected:
	int grade;
	PowerUpTypes powerUpType;

public:
	Dogfight(int grade = 0, PowerUpTypes puType = PowerUpTypes::None);
	virtual ~Dogfight();
};