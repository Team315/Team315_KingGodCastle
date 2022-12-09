#pragma once
#include "Item.h"

class Armor : public Item
{
protected:

public:
	Armor(int grade = 0, bool useExtraChance = false, ItemType iType = ItemType::Armor);
	virtual ~Armor();
};