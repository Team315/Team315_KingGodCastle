#include "QuickHand.h"

QuickHand::QuickHand(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade, false, true)
{
	type = "PowerUp";
	name = "QuickHand"; // ����� �ճ
}

QuickHand::~QuickHand()
{
}
