#include "CounterAttack.h"

CounterAttack::CounterAttack(int grade, PowerUpTypes puType)
	: PowerUp(grade, puType)
{
	type = "PowerUp";
	name = "CounterAttack"; // �ݰ�
}

CounterAttack::~CounterAttack()
{
}