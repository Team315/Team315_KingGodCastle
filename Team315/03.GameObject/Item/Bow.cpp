#include "Bow.h"

Bow::Bow(int grade, ItemType type)
	: Item(grade, type)
{
	SetName("Bow");
}

Bow::~Bow()
{
}