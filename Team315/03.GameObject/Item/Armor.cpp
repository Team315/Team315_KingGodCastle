#include "Armor.h"

Armor::Armor(int grade, bool useExtraChance, ItemType iType)
	: Item(grade, useExtraChance, iType)
{
	SetName("Armor");
	itemType = ItemType::Armor;
}

Armor::~Armor()
{
}