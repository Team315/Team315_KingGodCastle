#include "Bow.h"

Bow::Bow(int grade, bool useExtraChance, ItemType iType)
	: Item(grade, useExtraChance, iType)
{
	SetName("Bow");
	itemType = ItemType::Bow;
}

Bow::~Bow()
{
}