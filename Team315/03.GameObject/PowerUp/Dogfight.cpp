#include "DogFight.h"

DogFight::DogFight(int grade, PowerUpTypes puType)
	: PowerUp(puType, grade)
{
	type = "PowerUp";
	name = "DogFight"; // ���ο�
}

DogFight::~DogFight()
{
}