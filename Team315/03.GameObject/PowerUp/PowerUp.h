#pragma once
#include "GameObj.h"
#include "Include.h"

class PowerUp : public GameObj
{
protected:
	int grade;
	PowerUpTypes powerUpType;
	bool unique;

public:
	PowerUp(PowerUpTypes puType = PowerUpTypes::None, int grade = 0, bool unique = true);
	virtual ~PowerUp();
	
	string MakePath();
	PowerUpTypes GetPowerUpType() { return powerUpType; }
	int GetGrade() { return grade; }
	bool isUnique() { return unique; }
};