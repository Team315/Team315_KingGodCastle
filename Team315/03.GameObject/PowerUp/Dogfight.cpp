#include "DogFight.h"

DogFight::DogFight(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade, true, true)
{
	type = "PowerUp";
	name = "DogFight"; // ���ο�
}

DogFight::~DogFight()
{
}