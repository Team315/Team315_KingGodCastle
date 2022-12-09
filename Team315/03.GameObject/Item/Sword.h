#pragma once
#include "Item.h"

class Sword : public Item
{
protected:

public:
	Sword(int grade = 0, bool useExtraChance = false, ItemType iType = ItemType::Sword);
	virtual ~Sword();
};