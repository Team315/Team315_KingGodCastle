#include "Character.h"

Character::Character()
{
}

Character::~Character()
{
}

void Character::Init()
{
}

void Character::Update(float dt)
{
	SpriteObj::Update(dt);
}

void Character::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Character::SetTarget(Character* target)
{
	this->target = target;
}