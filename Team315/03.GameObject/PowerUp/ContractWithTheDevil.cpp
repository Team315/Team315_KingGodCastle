#include "ContractWithTheDevil.h"

ContractWithTheDevil::ContractWithTheDevil(int grade, PowerUpTypes puType)
	: PowerUp(grade, puType)
{
	type = "PowerUp";
	name = "ContractWithTheDevil"; // �Ǹ��� ���
}

ContractWithTheDevil::~ContractWithTheDevil()
{
}