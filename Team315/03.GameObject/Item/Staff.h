#pragma once
#include "Item.h"

class Staff : public Item
{
protected:

public:
	Staff(int grade = 1, ItemType type = ItemType::Staff);
	virtual ~Staff();
};