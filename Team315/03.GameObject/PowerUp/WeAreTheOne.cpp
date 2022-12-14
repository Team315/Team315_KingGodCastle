#include "WeAreTheOne.h"

WeAreTheOne::WeAreTheOne(int grade, PowerUpTypes puType)
	: PowerUp(grade, puType)
{
	type = "PowerUp";
	name = "We_are_the_one"; // 우리는 하나
}

WeAreTheOne::~WeAreTheOne()
{
}