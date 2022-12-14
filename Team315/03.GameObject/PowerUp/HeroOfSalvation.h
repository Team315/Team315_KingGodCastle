#pragma once
#include "PowerUp.h"

class HeroOfSalvation : public PowerUp
{
protected:
	int grade;
	PowerUpTypes powerUpType;

public:
	HeroOfSalvation(int grade = 0, PowerUpTypes puType = PowerUpTypes::None);
	virtual ~HeroOfSalvation();
};