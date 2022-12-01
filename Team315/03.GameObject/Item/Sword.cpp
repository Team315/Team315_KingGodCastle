#include "Sword.h"

Sword::Sword(int grade, ItemType type)
	: Item(grade, type)
{
	SetName("Sword");
}

Sword::~Sword()
{
}