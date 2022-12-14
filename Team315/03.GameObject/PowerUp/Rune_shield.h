#pragma once
#include "PowerUp.h"

class Rune_shield : public PowerUp
{
protected:
	int grade;
	PowerUpTypes powerUpType;

public:
	Rune_shield(int grade = 0, PowerUpTypes puType = PowerUpTypes::None);
	virtual ~Rune_shield();
};