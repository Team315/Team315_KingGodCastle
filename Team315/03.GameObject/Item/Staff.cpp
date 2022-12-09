#include "Staff.h"

Staff::Staff(int grade, bool useExtraChance, ItemType type)
	: Item(grade, useExtraChance, type)
{
	SetName("Staff");
}

Staff::~Staff()
{
}