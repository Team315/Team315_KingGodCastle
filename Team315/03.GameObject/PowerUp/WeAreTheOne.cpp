#include "WeAreTheOne.h"

WeAreTheOne::WeAreTheOne(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade, false, true)
{
	type = "PowerUp";
	name = "WeAreTheOne"; // �츮�� �ϳ�
}

WeAreTheOne::~WeAreTheOne()
{
}