#include "RuneShield.h"

RuneShield::RuneShield(int grade, PowerUpTypes puType)
	: PowerUp(grade, puType)
{
	type = "PowerUp";
	name = "RuneShield"; // �� ����
}

RuneShield::~RuneShield()
{
}
