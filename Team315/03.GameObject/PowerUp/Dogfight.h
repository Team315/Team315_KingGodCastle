#pragma once
#include "PowerUp.h"

class DogFight : public PowerUp
{
protected:
	int grade;
	PowerUpTypes powerUpType;

public:
	DogFight(int grade = 0, PowerUpTypes puType = PowerUpTypes::DogFight);
	virtual ~DogFight();
};