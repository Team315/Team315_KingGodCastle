#include "CounterAttack.h"

CounterAttack::CounterAttack(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade)
{
	type = "PowerUp";
	name = "CounterAttack"; // ¹Ý°Ý
}

CounterAttack::~CounterAttack()
{
}