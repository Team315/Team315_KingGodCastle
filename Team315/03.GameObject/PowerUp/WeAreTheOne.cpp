#include "WeAreTheOne.h"

WeAreTheOne::WeAreTheOne(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade)
{
	type = "PowerUp";
	name = "WeAreTheOne"; // �츮�� �ϳ�
}

WeAreTheOne::~WeAreTheOne()
{
}