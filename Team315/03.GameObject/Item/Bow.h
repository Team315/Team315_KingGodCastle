#pragma once
#include "Item.h"

class Bow : public Item
{
protected:

public:
	Bow(int grade = 0, bool useExtraChance = false, ItemType iType = ItemType::Bow);
	virtual ~Bow();
};