#include "QuickHand.h"

QuickHand::QuickHand(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade)
{
	type = "PowerUp";
	name = "QuickHand"; // ����� �ճ
}

QuickHand::~QuickHand()
{
}
