#pragma once
#include "Item.h"

class Sword : public Item
{
protected:

public:
	Sword(int grade = 0, ItemType type = ItemType::Sword);
	virtual ~Sword();
};