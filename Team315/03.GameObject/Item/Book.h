#pragma once
#include "Item.h"

class Book : public Item
{
protected:

public:
	Book(int grade = 0, ItemType type = ItemType::Book);
	virtual ~Book();
};