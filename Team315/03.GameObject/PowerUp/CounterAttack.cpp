#include "CounterAttack.h"

CounterAttack::CounterAttack(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade, true, true)
{
	type = "PowerUp";
	name = "CounterAttack"; // �ݰ�
}

CounterAttack::~CounterAttack()
{
}