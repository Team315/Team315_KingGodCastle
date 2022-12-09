#include "Sword.h"

Sword::Sword(int grade, bool useExtraChance, ItemType iType)
	: Item(grade, useExtraChance, iType)
{
	SetName("Sword");
	itemType = ItemType::Sword;
}

Sword::~Sword()
{
}