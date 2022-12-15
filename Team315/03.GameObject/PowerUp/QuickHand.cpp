#include "QuickHand.h"

QuickHand::QuickHand(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade, false, true)
{
	type = "PowerUp";
	name = "QuickHand"; // 재빠른 손놀림
}

QuickHand::~QuickHand()
{
}
