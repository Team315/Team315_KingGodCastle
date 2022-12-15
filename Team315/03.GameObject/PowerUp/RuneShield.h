#pragma once
#include "PowerUp.h"

class RuneShield : public PowerUp
{
protected:
	int grade;
	PowerUpTypes powerUpType;

public:
	RuneShield(int grade = 0, PowerUpTypes puType = PowerUpTypes::RuneShield);
	virtual ~RuneShield();
};