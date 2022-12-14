#include "Quick_hand.h"

QuickHand::QuickHand(int grade, PowerUpTypes puType)
	: PowerUp(grade, puType)
{
	type = "PowerUp";
	name = "Quick_hand"; // 재빠른 손놀림
}

QuickHand::~QuickHand()
{
}
