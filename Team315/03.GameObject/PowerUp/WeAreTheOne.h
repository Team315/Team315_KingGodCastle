#pragma once
#include "PowerUp.h"

class WeAreTheOne : public PowerUp
{
protected:
	int grade;
	PowerUpTypes powerUpType;

public:
	WeAreTheOne(int grade = 0, PowerUpTypes puType = PowerUpTypes::None);
	virtual ~WeAreTheOne();
};