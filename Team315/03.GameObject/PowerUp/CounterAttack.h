#pragma once
#include "PowerUp.h"

class CounterAttack : public PowerUp
{
protected:
	int grade;
	PowerUpTypes powerUpType;

public:
	CounterAttack(int grade = 0, PowerUpTypes puType = PowerUpTypes::CounterAttack);
	virtual ~CounterAttack();
};