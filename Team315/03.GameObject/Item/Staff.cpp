#include "Staff.h"

Staff::Staff(int grade, ItemType type)
	: Item(grade, type)
{
	SetName("Staff");
}

Staff::~Staff()
{
}