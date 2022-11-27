#include "Skill.h"

Skill::Skill(int starNumber)
	: damage(0.f)
{
}

Skill::~Skill()
{
}

void Skill::Init()
{
}

void Skill::Update(float dt)
{
}

void Skill::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Skill::SetPos(const Vector2f& pos)
{
	SpriteObj::SetPos(pos);
}

void Skill::SetState(AnimStates newState)
{
	if (currState == newState)
	{
		return;
	}
	currState = newState;
}

void Skill::SetTarget(Character* target)
{
	this->target = target;
}