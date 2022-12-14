#include "ContractWithTheDevil.h"

ContractWithTheDevil::ContractWithTheDevil(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade, false, true)
{
	type = "PowerUp";
	name = "ContractWithTheDevil"; // ¾Ç¸¶ÀÇ °è¾à
}

ContractWithTheDevil::~ContractWithTheDevil()
{
}