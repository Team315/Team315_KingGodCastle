#include "QuickHand.h"

QuickHand::QuickHand(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade, true, true)
{
	type = "PowerUp";
	name = "QuickHand"; // ����� �ճ
}

QuickHand::~QuickHand()
{
}
