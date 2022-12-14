#include "WeAreTheOne.h"

WeAreTheOne::WeAreTheOne(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade)
{
	type = "PowerUp";
	name = "WeAreTheOne"; // 우리는 하나
}

WeAreTheOne::~WeAreTheOne()
{
}