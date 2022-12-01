#pragma once
#include "Item.h"

class Staff : public Item
{
protected:

public:
	Staff(int grade = 0, ItemType type = ItemType::Staff);
	virtual ~Staff();
};