#include "QuickHand.h"

QuickHand::QuickHand(int grade, PowerUpTypes puType)
	: PowerUp(grade, puType)
{
	type = "PowerUp";
	name = "QuickHand"; // ����� �ճ
}

QuickHand::~QuickHand()
{
}
