#include "RuneShield.h"

RuneShield::RuneShield(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade, true, true)
{
	type = "PowerUp";
	name = "RuneShield"; // �� ����
}

RuneShield::~RuneShield()
{
}
