#include "PowerUp.h"

PowerUp::PowerUp(PowerUpTypes puType, int grade, bool unique)
	: powerUpType(puType), grade(grade), unique(unique)
{
}

PowerUp::~PowerUp()
{
}

string PowerUp::MakePath()
{
	string path = "graphics/battleScene/PowerUp/";

	switch (powerUpType)
	{
	case PowerUpTypes::Comrade:
		path += "comrade.png";
		break;
	case PowerUpTypes::ContractWithTheDevil:
		path += "contract_with_the_devil.png";
		break;
	case PowerUpTypes::CounterAttack:
		path += "counter_attack.png";
		break;
	case PowerUpTypes::DogFight:
		path += "dogfight.png";
		break;
	case PowerUpTypes::ExecutionerSoul:
		path += "executioner_soul.png";
		break;
	case PowerUpTypes::HeroOfSalvation:
		path += "hero_of_salvation.png";
		break;
	case PowerUpTypes::Meditation:
		path += "meditation.png";
		break;
	case PowerUpTypes::Nobility:
		path += "nobility.png";
		break;
	case PowerUpTypes::QuickHand:
		path += "quick_hand.png";
		break;
	case PowerUpTypes::RuneShield:
		path += "rune_shield.png";
		break;
	case PowerUpTypes::Vampire:
		path += "vampire.png";
		break;
	case PowerUpTypes::WarriorsHeart:
		path += "warriors_heart.png";
		break;
	case PowerUpTypes::WeAreTheOne:
		path += "we_are_the_one.png";
		break;
	default:
		break;
	}

	return path;
}