#pragma once
#include "PowerUp.h"

class WarriorsHeart : public PowerUp
{
protected:
	int grade;
	PowerUpTypes powerUpType;

public:
	WarriorsHeart(int grade = 0, PowerUpTypes puType = PowerUpTypes::None);
	virtual ~WarriorsHeart();
};