#pragma once
#include "Item.h"

class Staff : public Item
{
protected:

public:
	Staff(int grade = 0, bool useExtraChance = false, ItemType iType = ItemType::Staff);
	virtual ~Staff();
};