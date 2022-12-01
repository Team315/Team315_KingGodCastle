#pragma once
#include "Item.h"

class Armor : public Item
{
protected:

public:
	Armor(int grade = 0, ItemType type = ItemType::Armor);
	virtual ~Armor();
};