#include "WeAreTheOne.h"

WeAreTheOne::WeAreTheOne(int grade, PowerUpTypes puType)
	: PowerUp(grade, puType)
{
	type = "PowerUp";
	name = "WeAreTheOne"; // �츮�� �ϳ�
}

WeAreTheOne::~WeAreTheOne()
{
}