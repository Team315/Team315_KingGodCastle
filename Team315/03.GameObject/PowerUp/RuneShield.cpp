#include "RuneShield.h"

RuneShield::RuneShield(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade)
{
	type = "PowerUp";
	name = "RuneShield"; // �� ����
}

RuneShield::~RuneShield()
{
}
