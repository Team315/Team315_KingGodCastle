#pragma once
#include "Item.h"

class Bow : public Item
{
protected:

public:
	Bow(int grade = 1, ItemType type = ItemType::Bow);
	virtual ~Bow();
};