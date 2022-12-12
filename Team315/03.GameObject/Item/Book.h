#pragma once
#include "Item.h"

class Book : public Item
{
protected:

public:
	Book(int grade = 0, bool useExtraChance = false, ItemType type = ItemType::Book);
	virtual ~Book();
};