#include "Quick_hand.h"

QuickHand::QuickHand(int grade, PowerUpTypes puType)
	: PowerUp(grade, puType)
{
	type = "PowerUp";
	name = "Quick_hand"; // ����� �ճ
}

QuickHand::~QuickHand()
{
}
