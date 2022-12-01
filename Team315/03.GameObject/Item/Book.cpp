#include "Book.h"

Book::Book(int grade, ItemType type)
	: Item(grade, type)
{
	SetName("Book");
}

Book::~Book()
{
}