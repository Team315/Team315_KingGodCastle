#include "Book.h"

Book::Book(int grade, bool useExtraChance, ItemType type)
	: Item(grade, useExtraChance, type)
{
	SetName("Book");
}

Book::~Book()
{
}