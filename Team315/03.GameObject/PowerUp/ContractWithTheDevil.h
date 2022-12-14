#pragma once
#include "PowerUp.h"

class ContractWithTheDevil : public PowerUp
{
protected:
	int grade;
	PowerUpTypes powerUpType;

public:
	ContractWithTheDevil(int grade = 0, PowerUpTypes puType = PowerUpTypes::None);
	virtual ~ContractWithTheDevil();
};