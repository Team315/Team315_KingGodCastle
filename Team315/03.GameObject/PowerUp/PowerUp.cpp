#include "PowerUp.h"

PowerUp::PowerUp(int grade, PowerUpTypes puType)
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
	case PowerUpTypes::None:
		return nullptr;
	case PowerUpTypes::comrade:
		path += "comrade.png";
		break;
	case PowerUpTypes::contract_with_the_devil:
		path += "contract_with_the_devil.png";
		break;
	case PowerUpTypes::counter_attack:
		path += "counter_attack.png";
		break;
	case PowerUpTypes::dogfight:
		path += "dogfight.png";
		break;
	case PowerUpTypes::executioner_soul:
		path += "executioner_soul.png";
		break;
	case PowerUpTypes::hero_of_salvation:
		path += "hero_of_salvation.png";
		break;
	case PowerUpTypes::meditation:
		path += "meditation.png";
		break;
	case PowerUpTypes::nobility:
		path += "nobility.png";
		break;
	case PowerUpTypes::quick_hand:
		path += "quick_hand.png";
		break;
	case PowerUpTypes::rune_shield:
		path += "rune_shield.png";
		break;
	case PowerUpTypes::vampire:
		path += "vampire.png";
		break;
	case PowerUpTypes::warriors_heart:
		path += "warriors_heart.png";
		break;
	case PowerUpTypes::we_are_the_one:
		path += "we_are_the_one.png";
		break;
	default:
		break;
	}

	return path;
}