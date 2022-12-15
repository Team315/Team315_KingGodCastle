#pragma once
#include "PowerUp.h"

class Meditation : public PowerUp
{
protected:
	int grade;
	PowerUpTypes powerUpType;

public:
	Meditation(int grade = 0, PowerUpTypes puType = PowerUpTypes::Meditation);
	virtual ~Meditation();
};