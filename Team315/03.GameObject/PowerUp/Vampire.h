#pragma once
#include "PowerUp.h"

class Vampire : public PowerUp
{
protected:
	int grade;
	PowerUpTypes powerUpType;

public:
	Vampire(int grade = 0, PowerUpTypes puType = PowerUpTypes::Vampire);
	virtual ~Vampire();
};