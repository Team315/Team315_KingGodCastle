#include "Armor.h"

Armor::Armor(int grade, ItemType type)
	: Item(grade, type)
{
	SetName("Armor");
}

Armor::~Armor()
{
}