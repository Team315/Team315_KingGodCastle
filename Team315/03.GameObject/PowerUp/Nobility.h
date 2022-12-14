#pragma once
#include "PowerUp.h"

class Nobility : public PowerUp
{
protected:
	int grade;
	PowerUpTypes powerUpType;

public:
	Nobility(int grade = 0, PowerUpTypes puType = PowerUpTypes::None);
	virtual ~Nobility();
};