#pragma once
#include "GameObj.h"
#include "Include.h"

class PowerUp : public GameObj
{
protected:
	int grade;
	PowerUpTypes powerUpType;

public:
	PowerUp(int grade = 0, PowerUpTypes puType = PowerUpTypes::None);
	virtual ~PowerUp();
	
	string MakePath();
	PowerUpTypes GetPowerUpType() { return powerUpType; }
	int GetGrade() { return grade; }
};