#include "ContractWithTheDevil.h"

ContractWithTheDevil::ContractWithTheDevil(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade, false, true)
{
	type = "PowerUp";
	name = "ContractWithTheDevil"; // �Ǹ��� ���
}

ContractWithTheDevil::~ContractWithTheDevil()
{
}