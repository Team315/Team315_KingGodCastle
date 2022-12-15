#pragma once
#include "PowerUp.h"

class Comrade : public PowerUp
{
protected:
	int grade;
	PowerUpTypes powerUpType;

public:
	Comrade(int grade = 0, PowerUpTypes puType = PowerUpTypes::Comrade);
	virtual ~Comrade();
};